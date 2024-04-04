#pragma once 
#include "ParseAndAskSrv.h"
#include "std_srvs/srv/empty.hpp"

class TestSrv : public ParseAndAskSrv{
private:
    rclcpp::Client<std_srvs::srv::Empty>::SharedPtr client;
public:
    TestSrv(std::string srv_name,std::shared_ptr<rclcpp::Node> node):
    ParseAndAskSrv(srv_name,node)
    { client = node->create_client<std_srvs::srv::Empty>(srv_name);}
    void result_callback(rclcpp::Client<std_srvs::srv::Empty>::SharedFuture result_future);
    virtual void send_request(const bupt_interfaces::msg::Joy::SharedPtr array) override;
};