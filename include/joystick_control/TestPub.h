#pragma once 
#include "ParseAndPub.h"


class TestPub : public ParseAndPub{
private:
    rclcpp::Publisher<std_msgs::msg::UInt8MultiArray>::SharedPtr publisher;
public:
    TestPub(std::string topic_name,std::shared_ptr<rclcpp::Node> node):
    ParseAndPub(topic_name,node)
    { publisher = node->create_publisher<std_msgs::msg::UInt8MultiArray>(topic_name, 10);}
    virtual void msg_publish(const std_msgs::msg::UInt8MultiArray::SharedPtr array) override;
};