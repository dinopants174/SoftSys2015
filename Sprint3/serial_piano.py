from time import sleep
import serial
ser = serial.Serial('/dev/tty.usbmodem1421', 4800)
while True:
	x = raw_input('Enter note: ')
	ser.write(x)
	sleep(1)