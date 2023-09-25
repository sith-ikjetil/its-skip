#!/bin/bash
#: Title       : install.sh
#: Date        : 2022-07-23
#: Author      : Kjetil Kristoffer Solberg <post@ikjetil.no>
#: Version     : 1.0
#: Description : Installs its-skip man pages.

function InstallUbuntu()
{
    if [ ! -d "/usr/local/man/man1" ]
    then
        sudo mkdir /usr/local/man/man1
    fi

    sudo cp its-skip.1 /usr/local/man/man1
    sudo chmod go+r /usr/local/man/man1/its-skip.1
    printf "Install Ubuntu Complete\n"
}

function InstallFedora()
{
    # fedora
    if [ ! -d "/usr/local/share/man/man1" ]
    then
        sudo mkdir "/usr/local/share/man/man1"
    fi        
    sudo cp its-skip.1 /usr/local/share/man/man1
    sudo chmod go+r /usr/local/share/man/man1/its-skip.1
    printf "Install Fedora Complete\n"
}


printf "Installing man page\n"

./render.sh

if [ -d "/usr/local/man" ]
then
    InstallUbuntu
fi

if [ -d "/usr/local/share/man" ]
then
    InstallFedora
fi

