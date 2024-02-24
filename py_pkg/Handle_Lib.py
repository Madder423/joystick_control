from py_pkg.Uart import Serial
from py_pkg.Socket import socket
from py_pkg.crc8 import calculate_crc8
from time import sleep

class HandleDataProcessor:
    def __init__(self, uart_port, uart_baudrate, socket_host, socket_port):
        try:
            self.my_uart = Serial(uart_port, uart_baudrate)
        except:
            print(f'Cannot open serial port {uart_port}')
        self.addr = (socket_host, socket_port)
        self.my_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.my_socket.setsockopt(socket.SOL_SOCKET, socket.SO_KEEPALIVE, True)
        #self.my_socket.ioctl(socket.SIO_KEEPALIVE_VALS, (1, 60 * 1000, 30 * 1000))
        #TODO:这块是照着网上乱改的
        self.my_socket.setsockopt(socket.IPPROTO_TCP,socket.TCP_KEEPIDLE,10)
        self.my_socket.setsockopt(socket.IPPROTO_TCP,socket.TCP_KEEPINTVL,3)
        self.my_socket.setsockopt(socket.IPPROTO_TCP,socket.TCP_KEEPCNT,5)
        try:
            self.my_socket.connect(self.addr)
        except:
            print(f'Cannot connect socket {socket_host}:{socket_port}')
            exit()

    def get_data_lists(self):
        try:
            uart_data = self.my_uart.CRC8_Check(self.my_uart.recv(9))
        except:
            print('Cannot receive UART data')
            return False

        # TCP's quirk: client needs to send first to get feedback
        try:
            self.my_socket.send(bytes('1'.encode()))
        except Exception as e:
            print(f'Error sending socket data: {e}')
            return False

        try:
            socket_bytes_data = self.my_socket.recv(9)
            socket_data = [int(byte) for byte in socket_bytes_data[2:7]]
        except Exception as e:
            print(f'Error receiving socket data: {e}')
            return False

        # 通常情况下，TCP的消息更新的比UART的快，在连续改变msg的时候，TCP的的消息更及时
        if uart_data != socket_data:
            for i in range(5):
                #TODO: 在目标值快速改变的时候会出毛病
                if uart_data==False or abs(socket_data[i] - uart_data[i]) > 3:
                    return False
        return socket_data

# Direct execution of the script
if __name__ == "__main__":
    data_processor = HandleDataProcessor("COM13", 115200, '192.168.4.1', 3456)

    while True:
        data = data_processor.get_data_lists()
        if data is not False:
            print(data)
            sleep(0.01)

