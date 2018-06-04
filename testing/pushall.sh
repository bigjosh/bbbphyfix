echo hello.

exit

# run the specified command on all client machines in clientlist.txt

while read ip; do
  echo $ip
  
  ssh -o StrictHostKeyChecking=no root@$ip "rm -r bbbphyfix/; git clone https://github.com/bigjosh/bbbphyfix; cd bbbphyfix/; ./install.sh; sync"
  
done <clientlist.txt
