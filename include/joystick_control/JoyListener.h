#pragma once
#include "rclcpp/rclcpp.hpp"
#include<vector>
#include "ParseAndPub.h"
#include "ParseAndAskSrv.h"
#include<memory>
//template<class T_sub>//订阅的消息的类型,发布消息的类型
class JoyListener: public rclcpp::Node{
private:
    rclcpp::Subscription<std_msgs::msg::UInt8MultiArray>::SharedPtr subscribe;//订阅者
    std::string sub_topic_name; //订阅话题名称
    std::vector<std::shared_ptr<ParseAndPub>> publishers; //发布者
    std::vector<std::shared_ptr<ParseAndAskSrv>> clients; //请求客户
    void sub_callback(const std_msgs::msg::UInt8MultiArray::SharedPtr msg);  //收到话题的回调
public:
    JoyListener(std::string name,std::string _sub_topic_name);
    void add_publisher(std::shared_ptr<ParseAndPub> _publisher);//增加发布者
    void add_client(std::shared_ptr<ParseAndAskSrv> _client);//增加请求客户

};