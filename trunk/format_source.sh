#!/bin/sh
#style code using KDE conventions
astyle --indent=spaces=4 --brackets=linux \
       --indent-labels --pad=oper --unpad=paren \
       --one-line=keep-statements --convert-tabs \
       --indent-preprocessor \
       `find -type f -name '*.cpp'` `find -type f -name '*.cc'` `find -type f -name '*.h'`