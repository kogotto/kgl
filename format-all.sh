#!/ bin / bash

find.- regex '.*\.cpp' | xargs - P 8 clang - format - style = file - i {}
