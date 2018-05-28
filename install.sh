#! /bin/sh
update-rc.d -f chkphy remove
DIR=$(mktemp bbbrtcXXXX)
pushd $DIR
git clone https://github.com/bigjosh/bbbrtc
make
popd
rm -r $DIR
cp checkphy /etc/init.d
chmod +x /etc/init.d/checkphy
sudo update-rc.d chkphy defaults
