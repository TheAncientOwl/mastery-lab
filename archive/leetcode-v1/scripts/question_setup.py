import sys

from QuestionParser import QuestionParser

if len(sys.argv) != 2:
    sys.exit("Missing question web url")

parser = QuestionParser(sys.argv[1])
parser.fetch_data()
parser.parse_data()
parser.setup_directory()
parser.complete_leetcode_cmake()
parser.make_cmake_lists()
parser.make_cpp_file()
parser.make_readme_file()
