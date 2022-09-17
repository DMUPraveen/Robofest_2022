BAUD_RATE = 9600
import serial 
import struct
import sys
import json
from time import sleep,time

def main():

    COM_PORT = "COM4"
    if(len(sys.argv)>1):
        COM_PORT = sys.argv[1]
        datafile = sys.argv[2]
    else:
        datafile = "data.json"
    
    data = {} 
    with open(datafile,"r") as f:
        data = json.loads(f.read())

    data_list = [val for _,val in data.items()] 
    output = b"".join(struct.pack('f',data) for data in data_list)
        
    arduino = serial.Serial(port=COM_PORT, baudrate=BAUD_RATE, timeout=.1)
    sleep(2)
    arduino.write(output);
    arduino.flush()
    sleep(0.5)
    r = arduino.readline().decode('utf-8')
    print(r)

if __name__ == "__main__":
    main()