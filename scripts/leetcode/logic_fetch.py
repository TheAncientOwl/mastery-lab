import html.parser
import json
import os
import re

import requests


def extract_problem_name(url: str) -> str:
    """
    Extracts the LeetCode problem slug from the given URL.
    Example: https://leetcode.com/problems/two-sum/description/ -> two-sum
    """
    try:
        # Remove trailing slash and split URL
        parts = url.strip("/").split("/")
        index = parts.index("problems")
        slug = parts[index + 1]
        return slug
    except (ValueError, IndexError):
        raise ValueError("Invalid LeetCode problem URL")


class Problem:
    def __init__(
        self, id: str, readme: str, code_snippet: str, unit_tests: str
    ):
        self.readme = readme
        self.code_snippet = code_snippet
        self.unit_tests = unit_tests
        self.id = id


class _ExampleHTMLParser(html.parser.HTMLParser):
    def __init__(self):
        super().__init__(convert_charrefs=True)
        self.text = []

    def handle_starttag(self, tag, attrs):
        if tag in {"br", "p", "div", "li", "pre"}:
            self.text.append("\n")
        elif tag in {"strong", "b"}:
            self.text.append(" ")

    def handle_endtag(self, tag):
        if tag in {"p", "div", "li", "pre"}:
            self.text.append("\n")
        elif tag in {"strong", "b"}:
            self.text.append(" ")

    def handle_data(self, data):
        self.text.append(data)


def _extract_expected_outputs(content: str) -> list[str]:
    parser = _ExampleHTMLParser()
    parser.feed(content)

    outputs = []
    sections = re.split(
        r"Example\s+\d+\s*:", "".join(parser.text), flags=re.IGNORECASE
    )
    for section in sections[1:]:
        match = re.search(
            r"Output\s*:\s*(.*?)(?=\s*(?:Explanation|Constraints)\s*:|$)",
            section,
            flags=re.IGNORECASE | re.DOTALL,
        )
        if match:
            outputs.append(match.group(1).strip())

    if not outputs:
        raise ValueError("Could not find expected outputs in the problem examples")
    return outputs


def _find_method_signature(code_snippet: str) -> tuple[str, str, list[tuple[str, str]]]:
    solution_class = re.search(r"\b(?:class|struct)\s+Solution\b", code_snippet)
    if not solution_class:
        raise ValueError("Could not identify a C++ solution class")

    match = re.search(
        r"(?m)(?:^[ \t]*|(?:public|private|protected):[ \t]*)"
        r"([\w:<>*& \t]+?)\s+([A-Za-z_]\w*)\s*"
        r"\(([^{};]*)\)\s*(?:const\s*)?\{",
        code_snippet[solution_class.start() :],
    )
    if not match:
        raise ValueError("Could not identify a C++ solution method")

    return_type, method_name, parameter_text = match.groups()
    parameters = []
    for parameter in _split_cpp_parameters(parameter_text):
        parameter_match = re.fullmatch(r"(.+?)\s+([A-Za-z_]\w*)", parameter.strip())
        if not parameter_match:
            raise ValueError(f"Unsupported C++ method parameter: {parameter.strip()}")
        parameter_type, parameter_name = parameter_match.groups()
        parameters.append((parameter_type.strip(), parameter_name))
    return return_type.strip(), method_name, parameters


def _split_cpp_parameters(parameters: str) -> list[str]:
    if not parameters.strip() or parameters.strip() == "void":
        return []

    result = []
    depth = 0
    start = 0
    for index, character in enumerate(parameters):
        if character == "<":
            depth += 1
        elif character == ">":
            depth -= 1
        elif character == "," and depth == 0:
            result.append(parameters[start:index].strip())
            start = index + 1
    result.append(parameters[start:].strip())
    return result


def _clean_cpp_type(cpp_type: str) -> str:
    return (
        cpp_type.replace("const ", "")
        .replace("volatile ", "")
        .replace("&", "")
        .strip()
    )


def _is_list_node_pointer(cpp_type: str) -> bool:
    return re.fullmatch(
        r"(?:struct\s+)?ListNode\s*\*", _clean_cpp_type(cpp_type)
    ) is not None


def _parse_list_node_value(raw_value: str, cpp_type: str) -> list:
    value = _parse_case_value(raw_value, cpp_type)
    if value is None:
        return []
    if not isinstance(value, list):
        raise ValueError(f"Expected an array for C++ type {cpp_type}")
    return value


def _template_argument(cpp_type: str, container: str) -> str | None:
    normalized_type = _clean_cpp_type(cpp_type)
    prefixes = (f"{container}<", f"std::{container}<")
    prefix = next(
        (candidate for candidate in prefixes if normalized_type.startswith(candidate)),
        None,
    )
    if prefix is None or not normalized_type.endswith(">"):
        return None

    return normalized_type[len(prefix) : -1].strip()


def _cpp_value(value, cpp_type: str) -> str:
    normalized_type = _clean_cpp_type(cpp_type)
    unqualified_type = normalized_type.removeprefix("std::")

    element_type = _template_argument(cpp_type, "vector")
    if element_type is not None:
        if not isinstance(value, list):
            raise ValueError(f"Expected an array for C++ type {cpp_type}")
        elements = ", ".join(_cpp_value(item, element_type) for item in value)
        return f"std::vector<{element_type}>{{{elements}}}"

    if unqualified_type in {"string", "string_view"}:
        if not isinstance(value, str):
            raise ValueError(f"Expected a string for C++ type {cpp_type}")
        return f"std::{unqualified_type}{{{json.dumps(value, ensure_ascii=True)}}}"

    if unqualified_type == "bool":
        if not isinstance(value, bool):
            raise ValueError(f"Expected a boolean for C++ type {cpp_type}")
        return "true" if value else "false"

    if unqualified_type in {
        "int", "long", "long long", "short", "unsigned", "unsigned int",
        "unsigned long", "unsigned long long", "size_t", "float", "double",
    }:
        if isinstance(value, bool) or not isinstance(value, (int, float)):
            raise ValueError(f"Expected a number for C++ type {cpp_type}")
        return repr(value)

    raise ValueError(f"Unsupported C++ test value type: {cpp_type}")


def _parse_case_value(raw_value: str, cpp_type: str):
    try:
        return json.loads(raw_value)
    except json.JSONDecodeError:
        if _clean_cpp_type(cpp_type).removeprefix("std::") in {
            "string",
            "string_view",
        }:
            return raw_value
        raise ValueError(f"Could not parse LeetCode case value: {raw_value!r}")


def _split_mutated_output(
    raw_output: str, parameters: list[tuple[str, str]]
) -> tuple[str, tuple[int, str] | None]:
    for parameter_index, (_, parameter_name) in enumerate(parameters):
        match = re.search(
            rf",\s*{re.escape(parameter_name)}\s*=", raw_output
        )
        if match:
            return (
                raw_output[: match.start()].strip(),
                (parameter_index, raw_output[match.end() :].strip()),
            )
    return raw_output, None


def _parse_mutated_case_value(raw_value: str, cpp_type: str) -> tuple[list, bool]:
    wildcard_pattern = re.compile(r"(?<=[,\[])\s*_\s*(?=[,\]])")
    if _template_argument(cpp_type, "vector") is None or not wildcard_pattern.search(
        raw_value
    ):
        value = _parse_case_value(raw_value, cpp_type)
        if not isinstance(value, list):
            raise ValueError(f"Expected an array for C++ type {cpp_type}")
        return value, False

    value = _parse_case_value(
        wildcard_pattern.sub("null", raw_value), cpp_type
    )
    if not isinstance(value, list):
        raise ValueError(f"Expected an array for C++ type {cpp_type}")
    wildcard_index = value.index(None)
    if any(item is not None for item in value[wildcard_index:]):
        raise ValueError("LeetCode wildcard values must be at the end of an array")
    return value[:wildcard_index], True


def _test_suite_name(problem_title: str) -> str:
    words = re.findall(r"[A-Za-z0-9]+", problem_title)
    suite_name = "".join(word[0].upper() + word[1:] for word in words)
    if not suite_name:
        return "GeneratedExamples"
    if suite_name[0].isdigit():
        return f"Problem{suite_name}"
    return suite_name


def _prepare_cpp_snippet(snippet: str) -> str:
    containers = [
        "string",
        "vector",
        "list",
        "deque",
        "map",
        "set",
        "unordered_map",
        "unordered_set",
    ]
    includes = []
    non_code_pattern = re.compile(
        r'//[^\n]*|/\*.*?\*/|"(?:\\.|[^"\\])*"|\'(?:\\.|[^\'\\])*\'|'
        r"^[ \t]*\#[^\n]*",
        flags=re.DOTALL | re.MULTILINE,
    )

    def qualify_types(code: str) -> str:
        for container in containers:
            token_pattern = re.compile(rf"(?<!\w){container}(?!\w)")
            if not token_pattern.search(code):
                continue
            include = f"#include <{container}>\n"
            if include not in includes:
                includes.append(include)
            unqualified_pattern = re.compile(rf"(?<![\w:]){container}(?!\w)")
            code = unqualified_pattern.sub(f"std::{container}", code)
        return code

    parts = []
    position = 0
    for match in non_code_pattern.finditer(snippet):
        parts.append(qualify_types(snippet[position : match.start()]))
        parts.append(match.group())
        position = match.end()
    parts.append(qualify_types(snippet[position:]))

    code_only = non_code_pattern.sub("", snippet)
    if (
        re.search(r"\bListNode\s*\*", code_only)
        and not re.search(
            r"\b(?:struct|class)\s+ListNode\b|\busing\s+ListNode\s*=",
            code_only,
        )
    ):
        includes.append('#include "ListNode.hpp"\n')

    return "".join(includes) + "".join(parts)


def _ensure_output_directory(folder_name: str, force: bool) -> None:
    if os.path.exists(folder_name) and not force:
        raise FileExistsError(
            f"Problem directory already exists: {folder_name}. "
            "Pass --force to overwrite generated files."
        )
    os.makedirs(folder_name, exist_ok=True)


def generate_unit_tests(
    code_snippet: str,
    example_testcases: str,
    content: str,
    problem_title: str = "Generated Examples",
) -> str:
    return_type, method_name, parameters = _find_method_signature(code_snippet)
    expected_outputs = _extract_expected_outputs(content)
    suite_name = _test_suite_name(problem_title)
    input_lines = [
        line.strip() for line in example_testcases.splitlines() if line.strip()
    ]

    expected_input_count = len(expected_outputs) * len(parameters)
    if len(input_lines) != expected_input_count:
        raise ValueError(
            "Could not match LeetCode example inputs to outputs: "
            f"found {len(input_lines)} input values for "
            f"{len(expected_outputs)} examples with {len(parameters)} parameters"
        )

    tests = []
    for case_index, raw_output in enumerate(expected_outputs):
        case_inputs = input_lines[
            case_index * len(parameters) : (case_index + 1) * len(parameters)
        ]
        variables = []
        test = [f"TEST({suite_name}, Example{case_index + 1})\n{{\n"]
        has_list_node = _is_list_node_pointer(return_type) or any(
            _is_list_node_pointer(parameter_type)
            for parameter_type, _ in parameters
        )
        if has_list_node:
            test.append("    ListNodeTestUtils::Arena<ListNode> list_nodes;\n")
        for parameter_index, (parameter_type, parameter_name) in enumerate(parameters):
            if _is_list_node_pointer(parameter_type):
                input_value = _parse_list_node_value(
                    case_inputs[parameter_index], parameter_type
                )
                list_values = ", ".join(
                    _cpp_value(value, "int") for value in input_value
                )
                input_expression = f"list_nodes.make_list({{{list_values}}})"
            else:
                input_value = _parse_case_value(
                    case_inputs[parameter_index], parameter_type
                )
                input_expression = _cpp_value(input_value, parameter_type)
            variable_name = f"input_{parameter_name}"
            variables.append(variable_name)
            test.append(
                f"    auto {variable_name} = {input_expression};\n"
            )

        test.append("\n")
        if _clean_cpp_type(return_type) == "void":
            output_match = re.fullmatch(
                r"([A-Za-z_]\w*)\s*=\s*(.*)", raw_output, flags=re.DOTALL
            )
            if not output_match:
                raise ValueError(
                    "Void-returning solutions need an example output in "
                    "'parameter = value' form"
                )
            output_parameter, raw_expected = output_match.groups()
            parameter_index = next(
                (
                    index
                    for index, (_, name) in enumerate(parameters)
                    if name == output_parameter
                ),
                None,
            )
            if parameter_index is None:
                raise ValueError(
                    f"Example output refers to unknown parameter {output_parameter!r}"
                )
            parameter_type = parameters[parameter_index][0]
            if _is_list_node_pointer(parameter_type):
                expected_value = _parse_list_node_value(
                    raw_expected.strip(), parameter_type
                )
                expected_expression = _cpp_value(
                    expected_value, "std::vector<int>"
                )
                test.append(
                    f"    auto expected = {expected_expression};\n"
                    f"    Solution{{}}.{method_name}({', '.join(variables)});\n"
                    f"    EXPECT_EQ(list_nodes.values("
                    f"{variables[parameter_index]}), expected);\n"
                )
            else:
                expected_value = _parse_case_value(
                    raw_expected.strip(), parameter_type
                )
                expected_expression = _cpp_value(expected_value, parameter_type)
                test.append(
                    f"    auto expected = {expected_expression};\n"
                    f"    Solution{{}}.{method_name}({', '.join(variables)});\n"
                    f"    EXPECT_EQ({variables[parameter_index]}, expected);\n"
                )
        else:
            raw_return_output, mutated_output = _split_mutated_output(
                raw_output, parameters
            )
            if _is_list_node_pointer(return_type):
                expected_value = _parse_list_node_value(
                    raw_return_output, return_type
                )
                expected_expression = _cpp_value(
                    expected_value, "std::vector<int>"
                )
                test.append(
                    f"    auto expected = {expected_expression};\n"
                    f"    auto actual = Solution{{}}.{method_name}"
                    f"({', '.join(variables)});\n"
                    f"    list_nodes.track(actual);\n"
                    f"    EXPECT_EQ(list_nodes.values(actual), expected);\n"
                )
            else:
                expected_value = _parse_case_value(
                    raw_return_output, return_type
                )
                expected_expression = _cpp_value(expected_value, return_type)
                test.append(
                    f"    auto expected = {expected_expression};\n"
                    f"    auto actual = Solution{{}}.{method_name}"
                    f"({', '.join(variables)});\n"
                    f"    EXPECT_EQ(actual, expected);\n"
                )
            if mutated_output is not None:
                parameter_index, raw_expected = mutated_output
                parameter_type, parameter_name = parameters[parameter_index]
                input_variable = variables[parameter_index]
                expected_name = f"expected_{parameter_name}"
                if _is_list_node_pointer(parameter_type):
                    expected_value = _parse_list_node_value(
                        raw_expected, parameter_type
                    )
                    expected_expression = _cpp_value(
                        expected_value, "std::vector<int>"
                    )
                    test.append(
                        f"    auto {expected_name} = {expected_expression};\n"
                        f"    EXPECT_EQ(list_nodes.values({input_variable}), "
                        f"{expected_name});\n"
                    )
                else:
                    expected_value, is_prefix = _parse_mutated_case_value(
                        raw_expected, parameter_type
                    )
                    expected_expression = _cpp_value(
                        expected_value, parameter_type
                    )
                    test.append(
                        f"    auto {expected_name} = {expected_expression};\n"
                    )
                    if is_prefix:
                        element_type = _template_argument(parameter_type, "vector")
                        if element_type is None:
                            raise ValueError(
                                "LeetCode wildcard outputs require a vector parameter"
                            )
                        actual_prefix_name = f"actual_{parameter_name}_prefix"
                        test.append(
                            f"    ASSERT_GE({input_variable}.size(), "
                            f"{expected_name}.size());\n"
                            f"    auto {actual_prefix_name} = "
                            f"std::vector<{element_type}>("
                            f"{input_variable}.begin(), {input_variable}.begin() + "
                            f"{expected_name}.size());\n"
                            f"    EXPECT_EQ({actual_prefix_name}, {expected_name});\n"
                        )
                    else:
                        test.append(
                            f"    EXPECT_EQ({input_variable}, {expected_name});\n"
                        )
        test.append("}\n")
        tests.extend(test)
        tests.append("\n")

    return "".join(tests)


def get_problem(title_slug) -> Problem:
    url = "https://leetcode.com/graphql"
    headers = {
        "Content-Type": "application/json",
        "Referer": f"https://leetcode.com/problems/{title_slug}/",
        "User-Agent": "Mozilla/5.0",
    }
    query = """
    query getQuestionDetail($titleSlug: String!) {
      question(titleSlug: $titleSlug) {
        questionId
        title
        content
        difficulty
        codeSnippets {
          lang
          langSlug
          code
        }
        exampleTestcases
      }
    }
    """
    response = requests.post(
        url,
        json={"query": query, "variables": {"titleSlug": title_slug}},
        headers=headers,
    )

    question = response.json()["data"]["question"]

    markdown = []
    markdown.append(
        f"# {question['questionId']}. {question['title']} ({question['difficulty']})\n"
    )
    markdown.append("## Description\n")
    markdown.append(question["content"])
    markdown.append("\n## Example Testcases\n")
    markdown.append(f"```\n{question['exampleTestcases']}\n```")

    snippet = ""
    for code_snippet in question["codeSnippets"]:
        if code_snippet["lang"] == "C++":
            snippet = f"```{code_snippet['langSlug']}\n{code_snippet['code']}\n```\n"
            break
    replacements = [
        ("```cpp", ""),
        ("```", ""),
    ]
    for repl in replacements:
        snippet = snippet.replace(repl[0], repl[1])

    snippet = _prepare_cpp_snippet(snippet)

    unit_tests = generate_unit_tests(
        snippet,
        question["exampleTestcases"],
        question["content"],
        question["title"],
    )
    return Problem(question["questionId"], "\n".join(markdown), snippet[:-1], unit_tests)


if __name__ == "__main__":
    import sys

    if len(sys.argv) not in (2, 3) or (
        len(sys.argv) == 3 and sys.argv[2] != "--force"
    ):
        print("Usage: python fetch_leetcode.py <leetcode_problem_url> [--force]")
        sys.exit(1)

    url = sys.argv[1]
    force = len(sys.argv) == 3
    slug = extract_problem_name(url)
    problem_name = slug.replace("-", " ").title()
    problem = get_problem(slug)

    padded_id = str(problem.id).zfill(4)
    folder_name = f"leetcode/{padded_id}-{slug}"
    _ensure_output_directory(folder_name, force)

    with open(f"{folder_name}/README.md", "w", encoding="utf-8") as f:
        f.write(problem.readme)

    with open(f"{folder_name}/Solution.cpp", "w", encoding="utf-8") as f:
        f.write('#include "testing.hpp" // IWYU pragma: keep\n\n')
        f.write(problem.code_snippet)
        f.write("\n\n")
        f.write(problem.unit_tests)

    # Replace dashes with underscores for CMake project and executable names, prefix with problem id
    cmake_slug = f"{padded_id}_{slug.replace('-', '_')}"
    with open(f"{folder_name}/CMakeLists.txt", "w", encoding="utf-8") as f:
        f.write(
            f"""cmake_minimum_required(VERSION 3.20)

project({cmake_slug} LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(CTest)
include(${{CMAKE_CURRENT_SOURCE_DIR}}/../../cmake/GoogleTest.cmake)

add_executable({cmake_slug}
    Solution.cpp
)

target_link_libraries({cmake_slug} PRIVATE GTest::gtest_main leetcode_common)

include(GoogleTest)
gtest_discover_tests({cmake_slug})
"""
        )

    subdirectory = f"add_subdirectory({padded_id}-{slug})"
    leetcode_cmake = "leetcode/CMakeLists.txt"
    with open(leetcode_cmake, "r", encoding="utf-8") as f:
        cmake_entries = f.read().splitlines()
    if subdirectory not in cmake_entries:
        with open(leetcode_cmake, "a", encoding="utf-8") as f:
            if cmake_entries and cmake_entries[-1]:
                f.write("\n")
            f.write(f"{subdirectory}\n")

    print(f"✅ {problem_name} saved to {folder_name}")
