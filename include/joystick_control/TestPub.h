#pragma once 
#include "ParseAndPub.h"


class TestPub : public ParseAndPub{
private:
    rclcpp::Publisher<bupt_interfaces::msg::Joy>::SharedPtr publisher;
public:
    TestPub(std::string topic_name,std::shared_ptr<rclcpp::Node> node):
    ParseAndPub(topic_name,node)
    { publisher = node->create_publisher<bupt_interfaces::msg::Joy>(topic_name, 10);}
    virtual void msg_publish(const bupt_interfaces::msg::Joy::SharedPtr array) override;
};