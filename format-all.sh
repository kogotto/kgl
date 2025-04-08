#!/bin/bash

find. -regex '.*\.cpp' | xargs -P8 clang-format -style=file -i {}
