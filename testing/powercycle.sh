# Repeatedly cycle and the test with pingb


#init power
sudo echo "18" > /sys/class/gpio/export
sudo echo "out" > /sys/class/gpio/gpio18/direction


while true; do 

	echo power off
	sudo echo "0" > /sys/class/gpio/gpio18/value
	
	sleep 5
	
	echo power on
	sudo echo "1" > /sys/class/gpio/gpio18/value
	
	sleep  45
	
	./pingb >>pingb.log	
	
done
