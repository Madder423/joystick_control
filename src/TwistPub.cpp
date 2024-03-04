#include "TwistPub.h"
#include "utils.h"
inline double vel_limiting(const double vel)
{
    if (abs(vel) >= MAX_VELOCITY)
    {
        return (vel > 0? MAX_VELOCITY : -MAX_VELOCITY);
    }
    else if(abs(vel) <= MIN_VELOCITY)
    {
        return 0;
    }
    //return (abs(vel) >= MAX_VELOCITY? (vel > 0? MAX_VELOCITY : -MAX_VELOCITY):(abs(vel) <= MIN_VELOCITY ? 0 : vel));
    return vel;
}

inline double angular_vel_limiting(const double av)
{
    if (abs(av) >= MAX_ANGULAR_VELOCITY)
    {
        return (av > 0? MAX_ANGULAR_VELOCITY : -MAX_ANGULAR_VELOCITY);
    }
    else if(abs(av) <= MIN_ANGULAR_VELOCITY)
    {
        return 0;
    }
    //return (abs(av) >= MAX_VELOCITY? (av > 0? MAX_VELOCITY : -MAX_VELOCITY):(abs(av) <= MIN_VELOCITY ? 0 : av));  
    return av;
}


double max_vel_cmd = 0.5;
double max_anlVel_cmd = 1.0;
filter<double> x_filter(5);
filter<double> y_filter(5);
filter<double> z_filter(5);

void TwistPub::msg_publish(const std_msgs::msg::UInt8MultiArray::SharedPtr array)
{
    //创建消息
    geometry_msgs::msg::Twist twist;
    //TODO:解算  
    //线速度  
    twist.linear.x += x_filter.data_filt(vel_limiting(((double)(array->data[0]>128? int(array->data[0])-256 : array->data[0])/100)*max_vel_cmd));
    twist.linear.y -= y_filter.data_filt(vel_limiting(((double)(array->data[1]>128? int(array->data[1])-256 : array->data[1])/100)*max_vel_cmd));

    //转向
    twist.angular.z -= z_filter.data_filt(angular_vel_limiting(((double)(array->data[2]>128? int(array->data[2])-256 : array->data[2])/100)*max_anlVel_cmd));
    //发布消息
    publisher->publish(twist);
    //打印数据
    std::cout<<twist.linear.x<<'\t'<<twist.linear.y<<'\t'<<twist.angular.z<<'\t'<<std::endl;
}