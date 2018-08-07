# bbbphyfix
A software only workaround for the Beagle Bone Black PHY bug 

More info here...

https://wp.josh.com/2018/06/04/a-software-only-solution-to-the-vexing-beagle-bone-black-phy-issue/

### Install


```
rm -r bbbphyfix/
git clone https://github.com/bigjosh/bbbphyfix
cd bbbphyfix/
./install
sync

```


### Install on a remote machine

    ssh -o StrictHostKeyChecking=no root@192.168.1.168 "rm -r bbbphyfix/; git clone https://github.com/bigjosh/bbbphyfix; cd bbbphyfix/; ./install.sh; sync"
    
### Disable
    
    update-rc.d -f chkphy remove

## Pushing to remote mahcines with no internet connection

Check out...
https://github.com/bigjosh/pushphyfix
