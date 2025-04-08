#!/bin/bash

git diff --name-only | xargs clang-format -style=file -i
