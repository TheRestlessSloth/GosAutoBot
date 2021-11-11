import RPi.GPIO as IO
import time

IO.setwarnings(False)
IO.setup(GPIO2,IO.IN)
IO.setup(GPIO3,IO.OUT)

while 1:
	IO.output(GPIO3,IO.HIGH)
	sleep(1)
	if(IO.input(14)=True):
		print("obj is far")
	else
		print("obj is near")

