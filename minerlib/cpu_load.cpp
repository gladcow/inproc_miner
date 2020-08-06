#include "cpu_load.h"

namespace stratum 
{
cpuload::cpuload()
{
    reset();
}

void cpuload::reset()
{
    start_time_ = time(nullptr);
    start_clock_ = clock();
}

double cpuload::usage() const
{
    time_t current_time = time(nullptr);
    clock_t current_clock = clock();
    time_t used_time = (current_clock - start_clock_) / CLOCKS_PER_SEC;
    if (current_time == start_time_)
        return 0;
    return double(used_time) / 8.0 / double(current_time - start_time_);
}

}
