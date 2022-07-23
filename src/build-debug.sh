#!/bin/bash
echo "Building its-skip ..."
echo "> Using debug build < "

g++ its-skip.cpp -o its-skip -ggdb
if [[ $? -eq 0 ]]
then
    echo "> its-skip build Ok"
else
    echo "> its-skip build Error"
fi

echo "> Build Process Complete <"