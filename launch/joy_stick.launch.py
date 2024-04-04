from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    joy_publisher = Node(
        package="joystick_control",
        executable="joy_publisher_node.py"
    )
    joy_cmd_node = Node(
        package="joystick_control",
        executable="Joy_node"
    )
    # 创建LaunchDescription对象launch_description,用于描述launch文件
    launch_description = LaunchDescription(
        [joy_publisher, joy_cmd_node])
    # 返回让ROS2根据launch描述执行节点
    return launch_description
