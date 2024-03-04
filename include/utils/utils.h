#pragma once
#include<deque>
#include<algorithm>
#include<cmath>

#define Sigma 5
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