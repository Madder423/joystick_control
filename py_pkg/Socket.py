import socket

class Socket:
    def __init__(self, host, port):
        self.tcpClient = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.host = host
        self.port = port
        self.addr = (self.host, self.port)

    def connect(self):
        try:
            self.tcpClient.connect(self.addr)
        except Exception as e:
            print(f'connect failed: {e}')
        else:
            print('connect success')

    def send(self, data):
        try:
            self.tcpClient.sendall(data)
        except Exception as e:
            print(f'send failed: {e}')

    def recv(self, length):
        try:
            data = self.tcpClient.recv(length)
            return data
        except Exception as e:
            print(f'recv failed: {e}')


