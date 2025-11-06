#!/bin/bash

find . -regex '.*\.\(cpp\|hpp\)' | xargs -P8 clang-format -style=file -i {}
