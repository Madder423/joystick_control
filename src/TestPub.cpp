#include "TestPub.h"

void TestPub::msg_publish(const std_msgs::msg::UInt8MultiArray::SharedPtr array)
{
    //创建消息
    std_msgs::msg::UInt8MultiArray msg = *array;
    //TODO:解算 
    
    //发布消息
    publisher->publish(msg);
}