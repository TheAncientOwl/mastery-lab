#!/usr/bin/env bash

# Usage:
# ./run.sh <path-to-problem-folder>
# Example:
# ./run.sh leetcode-v2/two-sum

set -euo pipefail

if [ -z "$1" ]; then
  echo "Usage: ./run.sh <problem-folder>"
  exit 1
fi

PROBLEM_DIR="$1"
CPP_FILE="$PROBLEM_DIR/Solution.cpp"
BUILD_DIR="./build"
BINARY="$BUILD_DIR/solution.out"
rm -f "$BINARY"

if [ ! -f "$CPP_FILE" ]; then
  echo "Error: $CPP_FILE not found."
  exit 1
fi

mkdir -p "$BUILD_DIR"

echo "Building $CPP_FILE ..."
g++ -std=c++20 -Wall -Wextra -O2 "$CPP_FILE" -o "$BINARY" || {
  echo "Build failed."
  exit 1
}

echo "Running..."
echo "---------------------------------"
echo ""
"$BINARY" || {
  echo "Program exited with failure."
  exit 1
}
echo ""
echo "---------------------------------"
echo "Done."
