#!/bin/bash

# Usage: ./fetch.sh https://leetcode.com/problems/two-sum/description/ [--force]

if [ "$#" -lt 1 ] || [ "$#" -gt 2 ]; then
    echo "Usage: $0 <leetcode-problem-link> [--force]"
    exit 1
fi

.venv/bin/python3 scripts/leetcode/logic_fetch.py "$@"
