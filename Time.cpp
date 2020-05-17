#include <chrono>
#include "Time.h"
using namespace std;
using namespace std::chrono;

void Time::TimeStart() {
    StartTime = high_resolution_clock::now();
}

void Time::TimeEnd() {
    EndTime = high_resolution_clock::now();
}

long Time::TimeExecution() {
    return duration_cast<nanoseconds>(Time::EndTime - Time::StartTime).count();
}