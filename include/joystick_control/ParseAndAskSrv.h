#pragma once
#include "rclcpp/rclcpp.hpp"
//#include "std_msgs/msg/header.hpp"
#include "std_msgs/msg/u_int8_multi_array.hpp"

class ParseAndAskSrv{
protected:
    std::string srv_name;   //服务名称
    std::shared_ptr<rclcpp::Node> node; //调用者指针
public:
    ParseAndAskSrv(std::string _srv_name,std::shared_ptr<rclcpp::Node> _node): 
    srv_name(_srv_name),node(_node){};
    virtual void send_request(const std_msgs::msg::UInt8MultiArray::SharedPtr array) = 0;
    bool wait_for_server(rclcpp::ClientBase::SharedPtr client){
         // 1.等待服务端上线
    while (!client->wait_for_service(std::chrono::seconds(1))) {
      //等待时检测rclcpp的状态
      if (!rclcpp::ok()) {
        RCLCPP_ERROR(node->get_logger(), "等待服务的过程中被打断...");
        return false;
      }
      RCLCPP_INFO(node->get_logger(), "等待服务端上线中");
    } return true;
    }
    virtual ~ParseAndAskSrv(){}
};