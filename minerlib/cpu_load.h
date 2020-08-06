#pragma once

#include <time.h>

namespace stratum
{

class cpuload
{
    public:
        cpuload();

        void reset();
        double usage() const;
    private:
        time_t start_time_;
        clock_t start_clock_;
};

}
