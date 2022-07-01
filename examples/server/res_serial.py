import serial
import time
arduino = serial.Serial(port='COM5', baudrate=115200, timeout=1)
def write_read():
    time.sleep(0.05)
    data = arduino.read()
    return data
while True:
    value = write_read()
    print(value) # printing the value