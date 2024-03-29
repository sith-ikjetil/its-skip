#!/bin/bash
#: Title       : build-debug.sh
#: Date        : 2022-07-23
#: Author      : Kjetil Kristoffer Solberg <post@ikjetil.no>
#: Version     : 1.0
#: Description : Builds ccat.
echo "Building its-skip ..."
echo "> using debug build < "

g++ its-skip.cpp -o its-skip -ggdb
if [[ $? -eq 0 ]]
then
    echo "> its-skip build ok"
else
    echo "> its-skip build error"
fi

echo "> build process complete <"