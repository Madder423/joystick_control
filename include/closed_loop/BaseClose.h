#pragma once
#include "rclcpp/rclcpp.hpp"
#include "nav_msgs/msg/odometry.hpp"
#include "geometry_msgs/msg/twist.hpp"
class BaseClose
{
public:
    BaseClose(std::shared_ptr<rclcpp::Node> _node) : node(_node)
    {
        odom_subscribe_ = this->node->create_subscription<nav_msgs::msg::Odometry>("odom", 10, std::bind(&BaseClose::odom_subscribe_, this, std::placeholders::_1));
    }
    virtual geometry_msgs::msg::Twist closedLoopControl(geometry_msgs::msg::Twist &targetTwist) = 0;
protected:
    //调用者指针
    std::shared_ptr<rclcpp::Node> node;
    // 声明一个订阅者
    rclcpp::Subscription<nav_msgs::msg::Odometry>::SharedPtr odom_subscribe_;
    //获取到的当前位姿
    geometry_msgs::msg::Twist currentTwist;
     // 收到话题数据的回调函数
    void callback(const nav_msgs::msg::Odometry::SharedPtr msg)
    {
        currentTwist.angular = msg->twist.twist.angular;
        currentTwist.linear = msg->twist.twist.linear;
    }
};
