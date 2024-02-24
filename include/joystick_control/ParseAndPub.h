#pragma once
#include "rclcpp/rclcpp.hpp"
//#include "std_msgs/msg/header.hpp"
#include "std_msgs/msg/u_int8_multi_array.hpp"

class ParseAndPub{
protected:
    //std_msgs::msg::Header *header;
    std::string topic_name;   //话题名称
    std::shared_ptr<rclcpp::Node> node; //调用者指针
    //rclcpp::Publisher<T>::SharedPtr publisher; //话题发布者
public:
    virtual void msg_publish(const std_msgs::msg::UInt8MultiArray::SharedPtr array) = 0;
    ParseAndPub(std::string _topic_name,std::shared_ptr<rclcpp::Node> _node): 
    topic_name(_topic_name),node(_node){};
    virtual ~ParseAndPub(){}
};