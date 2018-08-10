#!/bin/bash

#This script will install bbbphyfix on a machine that is isolated from the internet
#you will need a git server that is accessable that has bbbphyfix, bbbrtc, and phyreg. To start the git server use...
# git config --global alias.serve "daemon --verbose --export-all --base-path=.git --reuseaddr --strict-paths .git/"
# git server &
# then do...
# set GITSERVER=192.168.174.1
# ...where that is the IP address of the git server, followed by...
# ssh -o StrictHostKeyChecking=no root@192.168.1.168 "rm -r bbbphyfix/; git clone git://$GITSERVER/; cd bbbphyfix/; ./install.sh; sync"


if [ -n "$GITSERVER" ]; then 
    echo you must set the variable GITSERVER
    exit 1
fi

#first install the bbbrtc command that we will need
DIR=$(mktemp -d -t bbbrtc.XXXXXX) || exit 1
echo "tmpdir = $DIR"
pushd "$DIR"
git clone git://$GITSERVER/ bbbrtc
cd bbbrtc
make
popd
rm -r $DIR

#next install the bbbphyreg command that we will need
DIR=$(mktemp -d -t bbbrtc.XXXXXX) || exit 1
echo "tmpdir = $DIR"
pushd "$DIR"
git clone git://$GITSERVER/ phyreg
cd phyreg
make clean
make
make install
popd
rm -r $DIR

#remove an existing init.rc if present
update-rc.d -f chkphy remove
#install our script to run every boot
cp chkphy /etc/init.d
chmod +x /etc/init.d/chkphy
sudo update-rc.d chkphy defaults
