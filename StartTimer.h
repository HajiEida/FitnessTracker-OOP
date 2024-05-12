#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <fstream>
#include <chrono> // For timer

using namespace std;
using namespace std::chrono;

void startTimer(int timer_duration)
{
    auto start_time = system_clock::now();
    auto end_time = start_time + seconds(timer_duration);
    
    while (system_clock::now() < end_time)
    {
        // wait
    }
}
