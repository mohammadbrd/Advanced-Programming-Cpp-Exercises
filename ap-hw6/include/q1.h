#ifndef Q1_H
#define Q1_H
#include<cmath>

namespace q1
{
    template<typename T , typename Func>
    double gradient_descent(T initial_value, double step_size , Func func=Func{})
    {
        T min = initial_value;
        double learning_rate = step_size;
        double difference = learning_rate * (func(min + 0.0001) - func(min)) / 0.0001;
        while (std::abs(difference) > 0.00001)
        {
            difference = learning_rate * (func(min + 0.0001) - func(min)) / 0.0001; 
            min = min - difference;
        }
        return min;
    }
}

#endif //Q1_H