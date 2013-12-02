import sys
import time
import serial

SERIAL_PORT = 'com4'
NUM_LEDS = 120

def setLED(index,r,g,b):
    print("%03d%03d%03d%03d#" % (index,r,g,b))
    comm.write(bytes("%03d%03d%03d%03d#" % (index,r,g,b),"ascii"))
    

comm = serial.Serial(SERIAL_PORT)
for i in range(0, NUM_LEDS):
    setLED(i,0,255,0)
    time.sleep(0.05)


comm.close()
