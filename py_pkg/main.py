from Uart import Serial
from Socket import socket
from crc8 import calculate_crc8
from time import sleep

port = 'COM13'  
baudrate = 115200
try:
    my_uart = Serial(port, baudrate)
except:
    print('cannot open serial port', port)
    # exit()

host = '192.168.4.1'
port = 3456
addr = (host, port)
socket.setdefaulttimeout(500)
my_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
my_socket.setsockopt(socket.SOL_SOCKET, socket.SO_KEEPALIVE, True)
my_socket.ioctl(socket.SIO_KEEPALIVE_VALS, (1, 60 * 1000, 30 * 1000))


try:
    my_socket.connect(addr)
except:
    print('cannot connect socket', host, port)
    exit()

uart_valid = True
socket_valid = True
while True:
    try:
        uart_data = my_uart.CRC8_Check(my_uart.recv(9))
    except:
        print('cannot recv uart data')
        uart_vaild = False
        continue

    #TCP的毛病，client要先发送才能得到反馈
    try:
        my_socket.send(bytes('1'.encode()))
    except Exception as e:
        print(f'Error sending socket data: {e}')
        sleep(1)
        continue

    try:
        socket_bytes_data = my_socket.recv(9)
        socket_data = [int(byte) for byte in socket_bytes_data[2:7]]
    except Exception as e:
        print(f'Error receiving socket data: {e}')
        socket_valid = False
        continue

    if uart_data != socket_data:
        print("uart_data != socket_data")
        print('uart_data: ', uart_data, '\nsocket_data: ', socket_data)
        continue

    print('running',end='\n')
    # sleep(0.1)
