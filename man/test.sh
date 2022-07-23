#!/bin/bash
#: Title       : build-release.sh
#: Date        : 2022-07-23
#: Author      : Kjetil Kristoffer Solberg <post@ikjetil.no>
#: Version     : 1.0
#: Description : Test its-skip man page.
pandoc its-skip.1.md -s -t man | /usr/bin/man -l -
