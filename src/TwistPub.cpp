#include "TwistPub.h"

void TwistPub::msg_publish(const std_msgs::msg::UInt8MultiArray::SharedPtr array)
{
    //创建消息
    geometry_msgs::msg::Twist twist;
    //TODO:杨晖还没定好协议，解算先留着  

    //发布消息
    publisher->publish(twist);
}