#ifndef Q3_H
#define Q3_H

#include<iostream>
#include<queue>

namespace q3
{
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    struct Flight
    {
        std::string flight_number;
        size_t duration;
        size_t connections;
        size_t connection_times;
        size_t price;
    };
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    static size_t Time(std::string time)
    {   
        if(time.empty())
            return 0;
        std::regex pattern(R"((\d+)\h(\d+)?\m?)");
        std::smatch match;
        std::regex_search(time, match, pattern);
        size_t hour = std::stoi(match[1]) * 60;
        std::string minute = match[2];
        if(minute.empty())
            return hour;
        else
            return hour + std::stoi(minute);
    }
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    static std::stack<Flight> sortStack(std::stack<Flight> &input)
    {
        std::stack<Flight> tmpStack;
        int tmpstack = 0;
        while (!input.empty())
        {
            // pop out the first element
            auto tmp = input.top();
            int tmpinput = tmp.duration + tmp.connection_times + 3 * tmp.price;
            input.pop();
    
            // while temporary stack is not empty and top
            // of stack is greater than temp
            while (!tmpStack.empty() && tmpstack < tmpinput)
            {
                // pop from temporary stack and push
                // it to the input stack
                input.push(tmpStack.top());
                tmpStack.pop();
                if(!tmpStack.empty())
                    tmpstack = tmpStack.top().duration + tmpStack.top().connection_times + 3 * tmpStack.top().price;
            }
            // push temp in temporary of stack
            tmpStack.push(tmp);
            tmpstack = tmpStack.top().duration + tmpStack.top().connection_times + 3 * tmpStack.top().price;
        }
        return tmpStack;
    }
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    static auto gather_flights(std::string filename)
    {
        std::ifstream file(filename);
        std::stringstream buffer;
        buffer << file.rdbuf();
        std::string txt = buffer.str();
        std::regex pattern(R"(\d+\- \w+\:(\w+)\ - \w+\:(\d+\h\d*\m*)\ - \w+\:(\d+)\ - \w+\:(\d+\h\d*\m*)\,?(\d*\h*\d*\m*)\,?(\d*\h*\d*\m*) - \w+\:(\d+))");
        std::smatch match;
        std::stack<Flight> Flight_info{};
        while(std::regex_search(txt, match, pattern))
        {
            std::string flight_number = match[1];
            size_t duration = Time(match[2]);  
            size_t connections = std::stoi(match[3]);
            size_t connection_times =  Time(match[4]) + Time(match[5]) + Time(match[6]);
            size_t price = std::stoi(match[7]);
            Flight_info.push(Flight{flight_number, duration, connections, connection_times, price});
            txt = match.suffix().str();
        }
        Flight_info = sortStack(Flight_info);
        return Flight_info;
    }
}

#endif //Q3_H