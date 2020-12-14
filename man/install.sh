printf "Installing man page\n"
if [ ! -d "/usr/local/man/man1" ]
then
    sudo mkdir /usr/local/man/man1
fi
sudo cp its-skip.1 /usr/local/man/man1
printf "...install complete\n"
