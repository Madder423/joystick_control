#include "TestSrv.h"
//TODO:构造回调函数  
void TestSrv::result_callback(rclcpp::Client<std_srvs::srv::Empty>::SharedFuture result_future){
  auto response = result_future.get();
  RCLCPP_INFO(node->get_logger(), "Get response");
}

void TestSrv::send_request(const std_msgs::msg::UInt8MultiArray::SharedPtr array){
    //test_code
    //RCLCPP_INFO(node->get_logger(), "Has sent request");
    if(!array->data.at(2) || !wait_for_server(client)){return;}
    //TODO:构造请求
    auto request = std::make_shared<std_srvs::srv::Empty_Request>();
  
    //发送异步请求，然后等待返回，返回时调用回调函数
    client->async_send_request(
      request, std::bind(&TestSrv::result_callback, this,
                         std::placeholders::_1));
}