% its-skip(1) its-skip 1.0.0
% Written by Kjetil Kristoffer Solberg
% December 2020

# NAME
its-skip - skip first n lines of file output

# SYNOPSIS
**its-skip** [*OPTION*] [*FILE*]

# DESCRIPTION
**its-skip** skips first n number of lines of file output

# OPTIONS
**-?**, **--help**
: Shows the default help screen

**-n**, **--count**
: The number of lines to skip

# EXAMPLES
ls -al | **its-skip** -n 10
: Skips the first 10 lines from the **ls** command.

**its-skip** -n 10 < test.txt
: Skips the first 10 lines from test.txt

# BUGS
All software have bugs :)

# COPYRIGHT
License GPL-3.0-or-later. This is free software: you are free to change and redistribute it. There is NO WARRENTY, to the extent permitted by law.
