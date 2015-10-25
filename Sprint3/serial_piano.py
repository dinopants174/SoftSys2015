"""
This file used for serial communication with the Arduino Synthesizer.
"""

from time import sleep
import serial
ser = serial.Serial('/dev/tty.usbmodem1421', 4800)
while True:
	x = raw_input('Enter note: ') #User inputs a note
	ser.write(x) #Send that note over serial monitor
	sleep(1)
