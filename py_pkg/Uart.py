import serial
from py_pkg.crc8 import calculate_crc8
from time import sleep

class Serial:
    def __init__(self, port, baudrate):
        self.port = port
        self.index = 0
        self.baudrate = baudrate
        self.ser = serial.Serial(self.port, self.baudrate)
        self.target_speed = 0
        self.target_direction = 0
        self.reserve0 = 0
        self.reserve1 = 0
        self.reserve2 = 0

    def send(self, data):
        self.ser.write(data)

    def recv(self, length):
        data = self.ser.read(length)
        return data

    def CRC8_Check(self,uart_data):
        if uart_data[self.index] != ord('+'):
            while self.index < 9:
                if uart_data[self.index] == ord('+'):
                    break
                else:
                    self.index += 1

        if uart_data[(self.index+8)%9] != ord('*'):
            self.index = 0
            print('wrong end')
            return False
        # print(uart_data)
        if calculate_crc8(uart_data[(self.index+2)%9:(self.index+8)%9]) != b'\x00':
            print('wrong crc')
            print(uart_data[(self.index+2)%9:(self.index+8)%9],'\n',calculate_crc8(uart_data[(self.index+2)%9:(self.index+8)%9] ))
            return self.target_speed, self.target_direction, self.reserve0, self.reserve1, self.reserve2

        #这里算出来最高位全都是符号位，由于缺少对int8的原生支持，在这里实现数据转换比较麻烦，意义也不是很大，建议在使用c的地方再转换
        self.target_speed = int(uart_data[(self.index+2)%9])
        self.target_direction = int(uart_data[(self.index+3)%9])
        self.reserve0 = int(uart_data[(self.index+4)%9])
        self.reserve1 = int(uart_data[(self.index+5)%9])
        self.reserve2 = int(uart_data[(self.index+6)%9])

        return [self.target_speed, self.target_direction, self.reserve0, self.reserve1, self.reserve2]
