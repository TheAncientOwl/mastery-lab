if [ ! $# -eq 1  ]; then
    echo ">> Missing leetcode problem name"
    exit 1
fi

problem_name=$1
problem_path="./leetcode/$1"

# Make dir + add to CMakeLists.txt
mkdir -p $problem_path
grep -qxF "add_subdirectory($problem_name)" ./leetcode/CMakeLists.txt || echo "add_subdirectory($problem_name)" >> ./leetcode/CMakeLists.txt

# CMakeLists.txt
cd $problem_path
echo "file(GLOB SOURCE_FILES "*.cpp")
add_executable(Leetcode_${problem_name} \${SOURCE_FILES})

target_link_libraries(Leetcode_${problem_name} PRIVATE
    gtest
    gtest_main
)

target_include_directories(Leetcode_${problem_name} PRIVATE \${CMAKE_CURRENT_SOURCE_DIR}/../common)

include(GoogleTest)
gtest_discover_tests(Leetcode_${problem_name})" > CMakeLists.txt

# Solution.cpp
echo "#include <gtest/gtest.h>

TEST(Leetcode_${problem_name}, test01)
{

}
" > Solution.cpp

# README.md
echo "## {Title}
#### {problem link}

{Content}

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
