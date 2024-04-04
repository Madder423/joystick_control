#pragma once
#include<deque>
#include<algorithm>
#include<cmath>

#define Sigma 5

#define MAX_VELOCITY 5.0
#define MIN_VELOCITY 0.05
#define MAX_ANGULAR_VELOCITY 3.14
#define MIN_ANGULAR_VELOCITY 0.2

template<typename T>
class filter{
private:
    std::deque<T> data_deque;
    std::deque<double> weight_deque;
    double weight_sum;
public:
    filter(size_t size): data_deque(size, 0){
        for(int i = 0; (size_t)i < size;++i)
        {
            weight_deque.push_back(1/sqrt(6.28 *Sigma)*exp((-1)*i*i/(2*Sigma*Sigma)));
            std::cout<<weight_deque[i];
        }
        std::cout<<std::endl;
        weight_sum = std::accumulate(weight_deque.begin(), weight_deque.end(),0.0);
    };
    T data_filt(T data){
        data_deque.push_front(data);
        data_deque.pop_back();
        T result = 0;
        for(size_t i = 0;i < data_deque.size();++i)
        {
            result += data_deque[i]*weight_deque[i];
        }
        return result/weight_sum;
    }
};

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