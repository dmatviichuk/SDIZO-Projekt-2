#ifndef SDIZO_PROJEKT_1_TIME_H
#define SDIZO_PROJEKT_1_TIME_H
#include <iostream>
#include <chrono>

using namespace std;
using namespace std::chrono;

class Time {
public:
    high_resolution_clock::time_point StartTime;
    high_resolution_clock::time_point EndTime;

    void TimeStart();
    void TimeEnd();
    long TimeExecution();
};

#endif //SDIZO_PROJEKT_1_TIME_H
