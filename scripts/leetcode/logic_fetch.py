import requests
import os
import re
import pprint


def extract_problem_name(url: str) -> str:
    """
    Extracts and formats the LeetCode problem name from the given URL.
    Example: https://leetcode.com/problems/two-sum/description/ -> Two Sum
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
    def __init__(self, id: str, readme: str, code_snippet: str):
        self.readme = readme
        self.code_snippet = code_snippet
        self.id = id


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
    pprint.pprint(question)

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

    includes = []
    containers = [
        "vector",
        "list",
        "deque",
        "map",
        "set",
        "unordered_map",
        "unordered_set",
    ]
    for container in containers:
        if container in snippet:
            includes.append(f"#include <{container}>\n")
            snippet = snippet.replace(container, f"std::{container}")
    snippet = "\n".join(includes) + snippet

    return Problem(question["questionId"], "\n".join(markdown), snippet[:-1])


if __name__ == "__main__":
    import sys

    if len(sys.argv) != 2:
        print("Usage: python fetch_leetcode.py <leetcode_problem_url>")
        sys.exit(1)

    url = sys.argv[1]
    problem_name = extract_problem_name(url)
    slug = url.strip("/").split("/")[4]
    problem = get_problem(slug)

    folder_name = f"leetcode/{problem.id}-{slug}"
    os.mkdir(folder_name)

    with open(f"{folder_name}/README.md", "w", encoding="utf-8") as f:
        f.write(problem.readme)

    with open(f"{folder_name}/Solution.cpp", "w", encoding="utf-8") as f:

        f.write('#include "testing.hpp"\n')
        f.write(problem.code_snippet)
        f.write(
            """
int main()
{
    // TODO: tests
    return 0;
}
"""
        )

    # Replace dashes with underscores for CMake project and executable names
    cmake_slug = slug.replace("-", "_")
    with open(f"{folder_name}/CMakeLists.txt", "w", encoding="utf-8") as f:
        f.write(
            f"""cmake_minimum_required(VERSION 3.20)

project({cmake_slug} LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable({cmake_slug}
    Solution.cpp
)

# Include shared testing utilities
target_include_directories({cmake_slug}
    PRIVATE
        ${{CMAKE_CURRENT_SOURCE_DIR}}/../common
)
"""
        )

    print(f"✅ {problem_name} saved to {folder_name}")
