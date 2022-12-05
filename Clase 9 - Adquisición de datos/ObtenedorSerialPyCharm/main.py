import serial
import time
from datetime import datetime


wemos = serial.Serial('/dev/cu.usbserial-120', 115200)
Name_File = 'log-tempinicial.csv'
file = open(Name_File, 'w')

time.sleep(2)
wemos.flushInput()
wemos.flushOutput()

cantidad = int(input('Ingrese la cantidad de datos: '))
loop = 0

while loop < cantidad:
    dato = wemos.readline()
    time = datetime.now()
    linea = str(dato.strip()) + ';' + str(time) + ';' + '\n'
    file.write(linea)
    print(linea)
    loop +=1

wemos.close()
file.close()