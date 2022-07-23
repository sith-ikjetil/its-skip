#!/bin/bash
#: Title       : render.sh
#: Date        : 2022-07-23
#: Author      : Kjetil Kristoffer Solberg <post@ikjetil.no>
#: Version     : 1.0
#: Description : Renders its-skip man page.
pandoc its-skip.1.md -s -t man -o its-skip.1