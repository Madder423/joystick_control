#pragma once 
#include "ParseAndPub.h"
#include "geometry_msgs/msg/twist.hpp"
#include<cmath>

#define MAX_VELOCITY 1.0
#define MIN_VELOCITY 0.05
#define MAX_ANGULAR_VELOCITY 3.14
#define MIN_ANGULAR_VELOCITY 0.2

class TwistPub : public ParseAndPub{
private:
    rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr publisher;
public:
    TwistPub(std::string topic_name,std::shared_ptr<rclcpp::Node> node):
    ParseAndPub(topic_name,node)
    { publisher = node->create_publisher<geometry_msgs::msg::Twist>(topic_name, 10);}
    virtual void msg_publish(const std_msgs::msg::UInt8MultiArray::SharedPtr array) override;
};