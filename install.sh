#!/bin/bash

#remove an existing init.rc if present
update-rc.d -f chkphy remove
#install our script to run every boot
cp chkphy /etc/init.d
chmod +x /etc/init.d/chkphy
sudo update-rc.d chkphy defaults
