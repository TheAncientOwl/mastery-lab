# /bin/bash
if [ ! $# -eq 2  ]; then
    echo ">> Missing leetcode problem number nor problem url"
    echo ">> Usage: ./setup_problem 1 https://leetcode.com/problems/two-sum/"
    exit 1
fi

problem_number=$(printf "%04d" "$1")
problem_url=$2

raw_problem_name=$(echo "$problem_url" | grep -oP "https://leetcode.com/problems/\K[^/]+")
if [ -z "$raw_problem_name" ]; then
    echo "Invalid problem name '$raw_problem_name'"
fi

raw_problem_name=$(echo "$raw_problem_name" | tr '[:upper:]' '[:lower:]')
raw_problem_name=$(echo "$raw_problem_name" | tr '-' '_')

problem_name=$(echo "$raw_problem_name" | tr '_' ' ')
problem_title=$(echo "$problem_name" | awk '{for(i=1;i<=NF;i++) $i=toupper(substr($i,1,1)) tolower(substr($i,2));}1')
problem_id="${problem_number}_${raw_problem_name}"
problem_path="./leetcode/$problem_id"

# Make dir + add to CMakeLists.txt
mkdir -p $problem_path
grep -qxF "add_subdirectory($problem_id)" ./leetcode/CMakeLists.txt || echo "add_subdirectory($problem_id)" >> ./leetcode/CMakeLists.txt

# CMakeLists.txt
cd $problem_path
echo "file(GLOB SOURCE_FILES "*.cpp")
add_executable(Leetcode_${problem_id} \${SOURCE_FILES})

target_link_libraries(Leetcode_${problem_id} PRIVATE
    gtest
    gtest_main
    Leetcode_Common
)

target_include_directories(Leetcode_${problem_id} PRIVATE \${CMAKE_CURRENT_SOURCE_DIR}/../common)

include(GoogleTest)
gtest_discover_tests(Leetcode_${problem_id})" > CMakeLists.txt

# Solution.cpp
echo "#include <gtest/gtest.h>



TEST(Leetcode_${problem_id}, test01)
{

}" > Solution.cpp

# README.md
echo "## $1. ${problem_title}
#### ${problem_url}



### Example 1:
\`\`\`
Input: 
Output: 
Explanation: 
\`\`\`

### Example 2:
\`\`\`
Input: 
Output: 
Explanation: 
\`\`\`

### Constaints:
*
*
*" > README.md

# Go back
cd ../..
