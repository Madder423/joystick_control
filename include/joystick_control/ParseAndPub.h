#pragma once

#include "rclcpp/rclcpp.hpp"
//#include "std_msgs/msg/header.hpp"
#include "bupt_interfaces/msg/joy.hpp"

class ParseAndPub{
protected:
    //std_msgs::msg::Header *header;
    std::string topic_name;   //话题名称
    std::shared_ptr<rclcpp::Node> node; //调用者指针
    //rclcpp::Publisher<T>::SharedPtr publisher; //话题发布者
public:
    virtual void msg_publish(const bupt_interfaces::msg::Joy::SharedPtr array) = 0;
    ParseAndPub(std::string _topic_name,std::shared_ptr<rclcpp::Node> _node): 
    topic_name(_topic_name),node(_node){};
    virtual ~ParseAndPub(){}
};