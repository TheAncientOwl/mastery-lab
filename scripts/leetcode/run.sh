#!/usr/bin/env bash

# Usage:
# ./run.sh <path-to-problem-folder>
# Example:
# ./run.sh leetcode/0001-two-sum

set -euo pipefail

if [ "$#" -ne 1 ]; then
  echo ">> Usage: ./run.sh <problem-folder>"
  exit 1
fi

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_ROOT="$(cd "$SCRIPT_DIR/../.." && pwd)"
PROBLEM_DIR="$1"

if [[ "$PROBLEM_DIR" != /* ]]; then
  PROBLEM_DIR="$PWD/$PROBLEM_DIR"
fi

if [ ! -f "$PROBLEM_DIR/CMakeLists.txt" ]; then
  echo ">> Error: CMakeLists.txt not found in $PROBLEM_DIR"
  exit 1
fi

PROBLEM_DIR="$(cd "$PROBLEM_DIR" && pwd)"
case "$PROBLEM_DIR/" in
  "$PROJECT_ROOT"/*)
    PROBLEM_RELATIVE_DIR="${PROBLEM_DIR#"$PROJECT_ROOT"/}"
    ;;
  *)
    echo ">> Error: Problem directory must be inside $PROJECT_ROOT"
    exit 1
    ;;
esac

BUILD_DIR="$PROJECT_ROOT/build"
# Infer the CMake target name from the problem folder (e.g. two-sum -> two_sum).
TARGET_NAME=$(basename "$PROBLEM_DIR" | tr '-' '_')
BINARY="$BUILD_DIR/$PROBLEM_RELATIVE_DIR/$TARGET_NAME"

echo "---------------------------------"
echo ">> Configuring with CMake..."
echo "---------------------------------"
cmake -S "$PROJECT_ROOT" -B "$BUILD_DIR" || {
  echo ">> CMake configuration failed."
  exit 1
}

echo "---------------------------------"
echo ">> Building..."
echo "---------------------------------"
cmake --build "$BUILD_DIR" --target "$TARGET_NAME" || {
  echo ">> Build failed."
  exit 1
}

echo "---------------------------------"
echo ">> Running..."
echo "---------------------------------"
echo ""

if [ ! -f "$BINARY" ]; then
  echo ">> Error: Built binary $BINARY not found."
  exit 1
fi

"$BINARY" || {
  echo ">> Program exited with failure."
  exit 1
}

echo "---------------------------------"
echo ">> Done."
echo "---------------------------------"
