#!/bin/bash
#: Title       : build-release.sh
#: Date        : 2022-07-23
#: Author      : Kjetil Kristoffer Solberg <post@ikjetil.no>
#: Version     : 1.0
#: Description : Builds its-skip.
echo "Building its-skip ..."
echo "> using release build < "

g++ its-skip.cpp -o its-skip
if [[ $? -eq 0 ]]
then
    echo "> its-skip build ok"
else
    echo "> its-skip build error"
fi

echo "> build process complete <"