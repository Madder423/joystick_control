#include "JoyListener.h"
#include "TwistPub.h"
#include "TestPub.h"
int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    /*创建对应节点的共享指针对象*/
    auto node = std::make_shared<JoyListener>("Joy_Node","/JoyStick_array");
    //增加发布者
    node->add_publisher(std::make_shared<TwistPub>("/cmd_vel",node));
    node->add_publisher(std::make_shared<TestPub>("/test_topic",node));
    /* 运行节点，并检测退出信号*/
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}