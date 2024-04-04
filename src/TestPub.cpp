#include "TestPub.h"

void TestPub::msg_publish(const bupt_interfaces::msg::Joy::SharedPtr array)
{
    //创建消息
    bupt_interfaces::msg::Joy msg = *array;
    //TODO:解算 
    
    //发布消息
    publisher->publish(msg);
}