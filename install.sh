#!/bin/bash

#install the startup script that checks if phy problem is present
#and reboots if it is

#assumes bbbphy & phyreg are installed

#remove an existing init.rc if present
update-rc.d -f chkphy remove
#install our script to run every boot
cp chkphy /etc/init.d
chmod +x /etc/init.d/chkphy
sudo update-rc.d chkphy defaults
