import rclpy
from rclpy.node import Node
#from std_msgs.msg import UInt16MultiArray
#from std_msgs.msg import Header
import copy
from bupt_interfaces.msg import Joy
import copy
import queue
import threading
import time

from py_pkg.handle_msg import handleMsg
from py_pkg.Socket import TCPSocket
from py_pkg.UART import SerialReader

current_message = handleMsg("Undefined")
lock = threading.Lock()
exit_signal =  threading.Event()


def update_message(new_message):
    global current_message
    with lock:
        # 根据Stamp值和来源更新当前消息
        if (new_message.stamp > current_message.stamp) or \
                (new_message.stamp == current_message.stamp and new_message.source == "TCP"):
            current_message = copy.deepcopy(new_message)
            #print("current_message id:",id(current_message))
            current_message.print()


def tcp_receiver(exit_signal):
    tcp_socket = TCPSocket("192.168.4.1", 3456)
    tcp_socket.connect()
    q = tcp_socket.get_queue()
    new_msg = handleMsg("TCP")
    try:
        while not exit_signal.is_set():
            if not q.empty():
                byte_datas = q.get()
                code = new_msg.calc(byte_datas, "TCP")
                if code == -1:
                    print("SOF or EOF Error")
                elif code == -2:
                    print("CRC32 Error")
                else:
                    update_message(new_msg)
    finally:
        print("Stopping")
        tcp_socket.disconnect()


def serial_receiver(exit_signal):
    q = queue.Queue()
    serial_reader = SerialReader('COM6', 115200, q)
    serial_reader.start_reading()
    new_msg_serial = handleMsg("Serial")
    try:
        while not exit_signal.is_set():
            if not q.empty():
                byte_datas = q.get()
                code = new_msg_serial.calc(byte_datas, "Serial")
                if code == -1:
                    print("SOF or EOF Error")
                elif code == -2:
                    print("CRC32 Error")
                elif code == -3:
                    pass
                else:
                    update_message(new_msg_serial)
    finally:
        print("停止读取串口数据")
        serial_reader.stop_reading()

class JoyPublisher(Node):
    def __init__(self,name):
        super().__init__(name)
        # 创建线程
        self.tcp_thread = threading.Thread(target=tcp_receiver, args=(exit_signal,))
        # serial_thread = threading.Thread(target=serial_receiver, args=(exit_signal,))
        # 启动线程
        self.tcp_thread.start()
        # serial_thread.start()
        self.array_publisher_ = self.create_publisher(Joy,"JoyStick_msg", 10) 
        self.timer = self.create_timer(0.05, self.timer_callback)
        self.get_logger().info("Node %s start")

    def __del__(self):
        exit_signal.set()
        self.tcp_thread.join()
        # serial_thread.join()
        print("Exited")
    
    def timer_callback(self):
        """
        定时器回调函数
        """
        joy_msg = Joy()
        #print(id(current_message))
        #current_message.print()
        #data = my_handle.get_data_lists()
        joy_msg.action = copy.deepcopy(current_message.action)
        joy_msg.botton = copy.deepcopy(current_message.button_array)
        self.array_publisher_.publish(joy_msg) 
        #test_code
        #print("test_code")