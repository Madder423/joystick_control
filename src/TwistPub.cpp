#include "TwistPub.h"

void TwistPub::msg_publish(const std_msgs::msg::UInt8MultiArray::SharedPtr array)
{
    //创建消息
    geometry_msgs::msg::Twist twist;
    //TODO:解算  
    //前进与后退  
    twist.linear.x += (int)(array->data[0]>128? int(array->data[0])-256 : array->data[0])/50;
    //转向
    twist.angular.z += -(int)(array->data[1]>128? int(array->data[1])-256 : array->data[1])/50;
    //微调
    //twist.linear.x += array->data[2]/50;
    //发布消息
    publisher->publish(twist);
}