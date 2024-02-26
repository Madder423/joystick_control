#include "JoyListener.h"
JoyListener::JoyListener(std::string name,std::string _sub_topic_name): Node(name), sub_topic_name(_sub_topic_name){
    RCLCPP_INFO(this->get_logger(),"%s start",name.c_str());
    //创建订阅者
    subscribe = this->create_subscription<std_msgs::msg::UInt8MultiArray>(sub_topic_name,10,std::bind(&JoyListener::sub_callback,this,std::placeholders::_1));
}

void JoyListener::add_publisher(std::shared_ptr<ParseAndPub> _publisher){
    this->publishers.push_back(_publisher);
}
void JoyListener::add_client(std::shared_ptr<ParseAndAskSrv> _client){
    this->clients.push_back(_client);
}

void JoyListener::sub_callback(const std_msgs::msg::UInt8MultiArray::SharedPtr msg){
    RCLCPP_INFO(this->get_logger(),"msg receive:");
    for(auto &i : msg->data)
    {
        std::cout<<(int)i<<"\t";
    }
    std::cout<<std::endl;
    for(auto &pub : publishers)
    {
        pub->msg_publish(msg);
    }
    for(auto &clt : clients)
    {
        clt->send_request(msg);
    }
}
