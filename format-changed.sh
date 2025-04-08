#!/ bin / bash

git diff-- name - only | xargs - P 8 clang - format - style = file - i
