import rclpy
from rclpy.node import Node
from std_msgs.msg import UInt16MultiArray
#from std_msgs.msg import Header
from py_pkg.Handle_Lib import *

class JoyPublisher(Node):
    def __init__(self,name,uart_port="com9",Baud_rate=115200,socket_host='192.168.4.1',socket_port=3456):
        super().__init__(name)
        self.uart_port = uart_port
        self.Baud_rate = Baud_rate
        self.socket_host = socket_host
        self.socket_port = socket_port
        self.get_logger().info("Node %s start" % name)
        #self.header_publisher_ = self.create_publisher(Header,"JoyStick_Header", 10) 
        self.array_publisher_ = self.create_publisher(UInt16MultiArray,"JoyStick_array", 10) 
        self.timer = self.create_timer(0.05, self.timer_callback)
    
    def timer_callback(self):
        """
        定时器回调函数
        """
        array_msg = UInt16MultiArray()
        my_handle = HandleDataProcessor(self.uart_port, self.Baud_rate, self.socket_host, self.socket_port)
        data = my_handle.get_data_lists()
        if(data):
            array_msg.data = data
            self.array_publisher_.publish(array_msg) 
        #test_code
        self.get_logger().info(f'array:{my_handle.get_data_lists()}')