# /bin/bash
if [ ! $# -eq 1  ]; then
    echo ">> Missing leetcode question url"
    echo ">> Usage: ./setup_question https://leetcode.com/problems/two-sum/"
    exit 1
fi

echo ">> Fetching url..."
wget -q -P .tmp $1

python3 "leetcode/scripts/question_setup.py" $1

rm -rf .tmp
