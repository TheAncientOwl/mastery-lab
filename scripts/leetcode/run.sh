#!/usr/bin/env bash

# Usage:
# ./run.sh <path-to-problem-folder>
# Example:
# ./run.sh leetcode-v2/two-sum

set -euo pipefail

if [ -z "$1" ]; then
  echo ">> Usage: ./run.sh <problem-folder>"
  exit 1
fi

PROBLEM_DIR="$1"

BUILD_DIR="$PROBLEM_DIR/build"

if [ ! -f "$PROBLEM_DIR/CMakeLists.txt" ]; then
  echo ">> Error: CMakeLists.txt not found in $PROBLEM_DIR"
  exit 1
fi

mkdir -p "$BUILD_DIR"

echo "---------------------------------"
echo ">> Configuring with CMake..."
echo "---------------------------------"
cmake -S "$PROBLEM_DIR" -B "$BUILD_DIR" || {
  echo ">> CMake configuration failed."
  exit 1
}

echo "---------------------------------"
echo ">> Building..."
echo "---------------------------------"
cmake --build "$BUILD_DIR" || {
  echo ">> Build failed."
  exit 1
}

echo "---------------------------------"
echo ">> Running..."
echo "---------------------------------"
echo ""

# Infer binary name from folder (e.g., two-sum -> two_sum)
TARGET_NAME=$(basename "$PROBLEM_DIR" | tr '-' '_')
BINARY="$BUILD_DIR/$TARGET_NAME"

if [ ! -f "$BINARY" ]; then
  echo ">> Error: Built binary $BINARY not found."
  exit 1
fi

"$BINARY" || {
  echo ">> Program exited with failure."
  exit 1
}

rm -rf $BUILD_DIR

echo "---------------------------------"
echo ">> Done."
echo "---------------------------------"
