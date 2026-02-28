#!/bin/bash

# Usage: ./fetch.sh https://leetcode.com/problems/two-sum/description/

if [ -z "$1" ]; then
    echo "Usage: $0 <leetcode-problem-link>"
    exit 1
fi

.venv/bin/python3 scripts/logic_fetch_leetcode.py "$1"
