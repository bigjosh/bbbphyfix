# bbbphyfix
A software only workaround for the Beagle Bone Black PHY bug 

### Install

    rm -r bbbphyfix/
    git clone https://github.com/bigjosh/bbbphyfix
    cd bbbphyfix/
    ./install.sh
    sync
    
### Install on a remote machine

    ssh -o StrictHostKeyChecking=no root@192.168.1.168 "rm -r bbbphyfix/; git clone https://github.com/bigjosh/bbbphyfix; cd bbbphyfix/; ./install.sh; sync"
