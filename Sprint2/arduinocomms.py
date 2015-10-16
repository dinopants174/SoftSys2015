import serial
import cv2
import numpy as np

PORT = '/dev/ttyACM0'
SPEED = 9600
def send_command(val):
    connection = serial.Serial( PORT, 
                                SPEED,
                                timeout=0,
                                stopbits=serial.STOPBITS_TWO
                                )
    connection.write(val)
    connection.close()
def button(x):
    s = cv2.getTrackbarPos(switch,'video')
    if(s==0):
        send_command('2')
    if(s==1):
        send_command('1131111111111131111111111111113')

cv2.namedWindow('video')
#switch = '0 : OFF \n1 : ON'
#cv2.createTrackbar(switch, 'video',0,1,button)
img = cv2.imread('44088_tauba_large_oval_copper_watering_can.jpg')
cv2.imshow('video',img)
while(True):
    # Capture frame-by-frame
    
    
    # Our operations on the frame come here
    # Display the resulting frame
    
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break
    k = cv2.waitKey(1) & 0xFF
    if k == ord('w'):
        send_command('1')
    elif k == ord('a'):
        send_command('2')
    elif k == ord('s'):
        send_command('3')
    elif k == ord('d'):
        send_command('4')
    elif k == ord('t'):
        send_command('5')
# When everything done, release the capture
cap.release()
cv2.destroyAllWindows()