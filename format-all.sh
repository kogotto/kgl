#!/bin/bash

find . -regex '.*\.cpp' -exec clang-format -style=file -i {} \;
