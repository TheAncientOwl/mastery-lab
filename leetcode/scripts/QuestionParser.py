import os
import bs4
import json
import requests


class QuestionParser:
    def __init__(self, url) -> None:
        self.data = {}

        self.data["url"] = url
        self.queries = []

        pass

    def fetch_data(self) -> None:
        print(">> Parsing html...")

        html = open(os.path.join(
            os.getcwd(), ".tmp", "index.html"), "r").read()
        content = bs4.BeautifulSoup(html, "lxml").find_all(
            "script", id="__NEXT_DATA__")[0].text
        json_data = json.loads(str(content))

        self.queries = json_data["props"]["pageProps"]["dehydratedState"]["queries"]

    def __make_file_path(self, file_name):
        return os.path.join(self.data["paths"]["directory"], file_name)

    def parse_data(self) -> None:
        print(">> Parsing data...")

        for query in self.queries:
            key = query["queryKey"][0]
            data = query["state"]["data"]

            if key == "questionTitle":
                self.data["number"] = data["question"]["questionFrontendId"]
                self.data["title"] = data["question"]["title"]
                self.data["difficulty"] = data["question"]["difficulty"]

                question_id_num = int(self.data["number"])
                name = data["question"]["titleSlug"].replace("-", "_")
                self.data["directory_identifier"] = f"{question_id_num:04d}_{name}"
                self.data["leetcode_identifier"] = f"Leetcode_{self.data['directory_identifier']}"
            elif key == "questionContent":
                old_to_new = [
                    ["&quot;", ""],
                    ["</pre>", "</code></pre>"],
                    ["<strong>Input:</strong>", "<code>Input:"],
                    ["<strong>Output:</strong>", "Output:"],
                    ["<strong>Explanation:</strong>", "Explanation"],
                    ["<p><strong>", "<h3>"],
                    ['<p><strong class="example">', "<h3>"],
                    ["</strong></p>", "</h3>"],
                    ["<p>&nbsp;</p>", ""],
                ]

                self.data["content"] = data["question"]["content"]
                for [old, new] in old_to_new:
                    self.data["content"] = self.data["content"].replace(
                        old, new)

            elif key == "questionEditorData":
                snippets = data["question"]["codeSnippets"]
                self.data["snippet"] = "EMPTY"
                for snippet in snippets:
                    if snippet["lang"] == "C++":
                        self.data["snippet"] = snippet["code"]
                        break

                stl_identifiers = ["vector", "string"]
                self.data["includes"] = "\n"
                for stl in stl_identifiers:
                    if stl in self.data["snippet"]:
                        self.data["snippet"] = self.data["snippet"].replace(
                            stl, f"std::{stl}")
                        self.data["includes"] += f"#include <{stl}>\n"

        self.data["paths"] = {}
        self.data["paths"]["directory"] = os.path.join(
            os.getcwd(), "leetcode", self.data["directory_identifier"])
        self.data["paths"]["main_cmake"] = os.path.join(
            os.getcwd(), "leetcode", "CMakeLists.txt")

        self.data["paths"]["cmake"] = self.__make_file_path("CMakeLists.txt")
        self.data["paths"]["cpp"] = self.__make_file_path("Solution.cpp")
        self.data["paths"]["readme"] = self.__make_file_path("README.md")

    def setup_directory(self) -> None:
        os.makedirs(self.data["paths"]["directory"], exist_ok=True)

    def complete_leetcode_cmake(self) -> None:
        print(">> Completing leetcode/CMakeLists.txt...")
        first_line = ""
        lines = []
        with open(self.data["paths"]["main_cmake"], "r") as leetcode_cmake_file:
            subdirectory = f'add_subdirectory({self.data["directory_identifier"]})\n'
            lines = leetcode_cmake_file.readlines()
            first_line = lines[0]
            lines = lines[1:]
            lines.append(subdirectory)
            lines = list(set(lines))
            lines.sort()

        with open(self.data["paths"]["main_cmake"], "w") as leetcode_cmake_file:
            leetcode_cmake_file.write(first_line)
            leetcode_cmake_file.writelines(lines)

    def make_cmake_lists(self) -> None:
        print(">> Creating CMakeLists.txt...")
        with open(self.data["paths"]["cmake"], "w") as cmake_file:
            cmake_file.writelines(line + '\n' for line in [
                'file(GLOB SOURCE_FILES "*.cpp")',
                f'add_executable({self.data["leetcode_identifier"]} ${{SOURCE_FILES}})'
                '\n',
                f'target_include_directories({self.data["leetcode_identifier"]} PRIVATE ${{CMAKE_CURRENT_SOURCE_DIR}}/../common)',
                '\n'
                f'target_link_libraries({self.data["leetcode_identifier"]} PRIVATE',
                '    gtest',
                '    gtest_main',
                '    Leetcode_Common',
                ')',
                '\n'
                'include(GoogleTest)',
                f'gtest_discover_tests({self.data["leetcode_identifier"]})'
            ])

    def make_cpp_file(self) -> None:
        print(">> Creating Solution.cpp...")
        with open(self.data["paths"]["cpp"], "w") as cpp_file:
            cpp_file.writelines(line + '\n' for line in [
                '#include <gtest/gtest.h>',
                self.data["includes"],
                self.data["snippet"],
                f'\nTEST({self.data["leetcode_identifier"]}, test01)',
                '{',
                f'    // Test it on {self.data["url"]}... :)',
                '}'
            ])

    def make_readme_file(self) -> None:
        print(">> Creating README.md...")
        with open(self.data["paths"]["readme"], "w") as readme_file:
            readme_file.writelines(line + '\n' for line in [
                f"<h2>{self.data['number']}. {self.data['title']} ~ {self.data['difficulty']}</h2>\n",
                f"#### {self.data['url']}\n",
                self.data["content"]
            ])
