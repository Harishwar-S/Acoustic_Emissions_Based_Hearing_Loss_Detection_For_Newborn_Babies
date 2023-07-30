# Importing Libraries
import serial
import time
import csv
import time
import datetime
import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import numpy as np

plt.style.use('seaborn-poster')

name='PROJECT'

#Python sending data over the serial port.

arduino = serial.Serial(port='COM3', baudrate=9600, timeout=.1)

def write_A(x):
    arduino.write("A".encode())
    time.sleep(0.1)
    data = arduino.readline()
    return data
def write_B(x):
    arduino.write("B".encode())
    time.sleep(0.1)
    data = arduino.readline()
    return data
def write_C(x):
    arduino.write("C".encode())
    time.sleep(0.1)
    data = arduino.readline()
    return data

def READ_SENSOR(x):
    #arduino.write("FS##".encode())
    #time.sleep(1)
    data = arduino.readline().decode()
    return data


#Char to integer convertion for LCD display

def split(x):
    data=[]
    SV=str(x)
    SVV = SV.split("'b'Message: A:")
    data =SVV


    return data

print(" READY")
while True:

    #print("DEVICE READY")
    num = 1
    nus=5
    time.sleep(1)
    data=READ_SENSOR(num)
    print(data)
    #Temp1=data.split(",")

    Temp1=data.split(",")
    print(len (Temp1))
    

    if(len (Temp1) > 1):      
        print('DSP 1')
        print(Temp1[0])
        print('DSP 2')
        print(int(Temp1[1]))
        freq = 1.
        x = 3*np.sin(2*np.pi*freq*int(Temp1[1]))
        print('FFT VALUE')
        print(x)
        if int(Temp1[1]) > 20:
            print('SOUND OK')
            write_A(num)
        else:
            print('SOUND NOT OK')
            write_B(num)
        #print(Temp1[5])
        ts = time.time()
        date = datetime.datetime.fromtimestamp(ts).strftime('%Y-%m-%d')
        timeStamp = datetime.datetime.fromtimestamp(ts).strftime('%H:%M:%S')
        #attendance = [name, date, timeStamp,sensor1,sensor2,sensor3]
        #sensor1=Temp1[1]
        #sensor2=Temp1[0]
        #sensor3=int(Temp1[5])
        #print(sensor1)
        #data = {'Date' :date,'Time':timeStamp,'sens-1':[sensor1],'sens-2':[sensor2],}
        #print(data)
#        df = pd.DataFrame(data)
#        df.to_csv('sound.csv', mode='a', index=False, header=False)


    #df = pd.DataFrame(data)
    #df.to_csv('sound.csv', mode='a', index=False, header=False)
    # sampling rate
##    sr = 2000
##    # sampling interval
##    ts = 1.0/sr
##    t = np.arange(0,1,ts)
##
##    freq = 1.
##    x = 3*np.sin(2*np.pi*freq*t)
##
##    freq = 4
##    x += np.sin(2*np.pi*freq*t)
##
##    freq = 7   
##    x += 0.5* np.sin(2*np.pi*freq*t)
##
##    plt.figure(figsize = (8, 6))
##    plt.plot(t, x, 'r')
##    plt.ylabel('Amplitude')
##
##    plt.show()
