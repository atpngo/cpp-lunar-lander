import socket
import time
import random

PORT = 3490
ADDRESS = "127.0.0.1"

TELEGRAF_ADDRESS = ("127.0.0.1", 4000)

telegraf_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
columns = ["time", "px", "py", "vx", "vy", "ax", "ay", "rotation", "fuel"]

def sensor_to_influx(sensor_data: str, fields):
    data = sensor_data.split(',')
    measurements = ''
    for key,val in zip(fields,data):
        measurements += f'{key}={val},'
    measurements = measurements[:-1]
    return f'lander {measurements} {time.time_ns()}'

class Log:
    def __init__(self, filename):
        self.file = open(filename, 'w+')
        self.open = True
    
    def __del__(self):
        if (self.open):
            self.close()
    
    def write(self, message):
        self.file.write(str(message) + '\n')

    def close(self):
        self.file.close()
        self.open = False


logger = Log("log.csv")
logger.write(",".join(columns))

# rn the purpose is to log in python otherwise we could just stream data from the cpp sim to telegraf directly..
with socket.socket(socket.AF_INET, socket.SOCK_STREAM, 0) as s:
    s.bind((ADDRESS, PORT))
    s.listen()
    print('Listening for connections :)')
    conn, addr = s.accept()
    with conn:
        print(f"Connected: {addr}")
        while True:
            time.sleep(0.001)
            data = conn.recv(1024)
            if not data:
                break
            decoded_data = data.decode()
            pog_my_dog = sensor_to_influx(decoded_data, columns[1:])
            telegraf_socket.sendto(pog_my_dog.encode(), TELEGRAF_ADDRESS)
            logger.write(str(time.time_ns()) + "," + decoded_data)
            # print(decoded_data)


logger.close()