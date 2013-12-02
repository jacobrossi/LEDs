import sys
import time
import serial

SERIAL_PORT = 'com4'
BAUD = 9600 
NUM_LEDS = 120

def setRGB(index,r,g,b):
    comm.write(bytes("%03d%03d%03d%03d#" % (index,r,g,b),"ascii"))

comm = serial.Serial(SERIAL_PORT,BAUD)
for i in range(0, NUM_LEDS):
    setRGB(i,128,128,128)
    time.sleep(0.050) #some time for Arduino to process, avoiding overflowing serial buffer

comm.close()
