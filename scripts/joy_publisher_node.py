#!/usr/bin/env python3
import rclpy
from rclpy.node import Node
from py_pkg.joy_publisher import JoyPublisher

def main(args=None):
    rclpy.init(args=args) # 初始化rclpy
    node = JoyPublisher("joy_publisher")  # 新建一个节点
    rclpy.spin(node) # 保持节点运行，检测是否收到退出指令（Ctrl+C）
    rclpy.shutdown() # 关闭rclpy


if __name__ == '__main__':
    main()