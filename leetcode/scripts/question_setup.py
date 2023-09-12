import os
import sys

import requests
import bs4
import json

if len(sys.argv) != 2:
    sys.exit("Missing question web url")

question = {}
question["url"] = sys.argv[1]

# get html & parse
print(">> Parsing html...")
question_html = open(os.path.join(
    os.getcwd(), ".tmp", "index.html"), "r").read()
script_content = bs4.BeautifulSoup(question_html, "lxml").find_all(
    "script", id="__NEXT_DATA__")[0].text
json_content = json.loads(str(script_content))
queries = json_content["props"]["pageProps"]["dehydratedState"]["queries"]

# get needed data
print(">> Parsing question data...")
for query in queries:
    key = query["queryKey"][0]
    data = query["state"]["data"]

    if key == "questionTitle":
        question["number"] = data["question"]["questionFrontendId"]
        question["title"] = data["question"]["title"]
        question["difficulty"] = data["question"]["difficulty"]

        question_id_num = int(question["number"])
        name = data["question"]["titleSlug"].replace("-", "_")
        question["directory_identifier"] = f"{question_id_num:04d}_{name}"
        question["leetcode_identifier"] = f"Leetcode_{question['directory_identifier']}"
    elif key == "questionContent":
        old_to_new = [
            ["<pre>", "```"],
            ["```", "\n```"],
            ["</pre>", "```"],
            ["<strong>Input:</strong>", "Input:"],
            ["<strong>Output:</strong>", "Output:"],
            ["<strong>Explanation:</strong>", "Explanation"],
            ["<p><strong>", "<h3>"],
            ['<p><strong class="example">', "<h3>"],
            ["</strong></p>", "</h3>"],
            ["\n\n\n", "\n\n"],
            ["<p>&nbsp;</p>", ""]
        ]

        question["content"] = data["question"]["content"]
        for [old, new] in old_to_new:
            question["content"] = question["content"].replace(old, new)

# complete paths
question["paths"] = {}

question["paths"]["directory"] = os.path.join(
    os.getcwd(), "leetcode", question["directory_identifier"])

question["paths"]["main_cmake"] = os.path.join(
    os.getcwd(), "leetcode", "CMakeLists.txt")


def make_file_path(file_name):
    return os.path.join(question["paths"]["directory"], file_name)


question["paths"]["cmake"] = make_file_path("CMakeLists.txt")
question["paths"]["cpp"] = make_file_path("Solution.cpp")
question["paths"]["readme"] = make_file_path("README.md")

print(">> Creating question directory...")
os.makedirs(question["paths"]["directory"], exist_ok=True)

# complete files
print(">> Completing leetcode/CMakeLists.txt")
with open(question["paths"]["main_cmake"], "a+") as cmake_file:
    found = False

    subdirectory = f'add_subdirectory({question["directory_identifier"]})\n'

    with open(question["paths"]["main_cmake"], "r") as dummy:
        lines = dummy.readlines()
        for line in lines:
            if line == subdirectory:
                found = True
                break

    if not found:
        cmake_file.write(subdirectory)

print(">> Creating CMakeLists.txt...")
with open(question["paths"]["cmake"], "w") as cmake_file:
    cmake_file.writelines(line + '\n' for line in [
        'file(GLOB SOURCE_FILES "*.cpp")',
        f'add_executable({question["leetcode_identifier"]} ${{SOURCE_FILES}})'
        '\n',
        f'target_include_directories({question["leetcode_identifier"]} PRIVATE ${{CMAKE_CURRENT_SOURCE_DIR}}/../common)',
        '\n'
        f'target_link_libraries({question["leetcode_identifier"]} PRIVATE',
        '    gtest',
        '    gtest_main',
        '    Leetcode_Common',
        ')',
        '\n'
        'include(GoogleTest)',
        f'gtest_discover_tests({question["leetcode_identifier"]})'
    ])

print(">> Creating Solution.cpp...")
with open(question["paths"]["cpp"], "w") as cpp_file:
    cpp_file.writelines(line + '\n' for line in [
        '#include <gtest/gtest.h>',
        '\n\n',
        f'TEST({question["leetcode_identifier"]}, test01)',
        '{',
        f'    // Test it on {question["url"]}... :)',
        '}'
    ])

print(">> Creating README.md...")
with open(question["paths"]["readme"], "w") as readme_file:
    readme_file.writelines(line + '\n' for line in [
        f"<h2>{question['number']}. {question['title']} ~ {question['difficulty']}</h2>\n",
        f"#### {question['url']}\n",
        question["content"]
    ])
