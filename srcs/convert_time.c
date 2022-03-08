#include "philo.h"

uint64_t    timeval_to_micro(timeval current_time)
{
    return ((current_time.tv_sec * 1000000 + current_time.tv_usec));
}

uint64_t milli_to_micro(uint64_t milliseconds)
{
    return (milliseconds * 1000);
}

uint64_t micro_to_milli(uint64_t microseconds)
{
    return (microseconds * 0.001);
}

uint64_t micro_to_seconds(uint64_t microseconds)
{
    return (microseconds * 0.000001);
}

uint64_t   difference(timeval start, timeval end)
{
    return (timeval_to_micro(end) -
    timeval_to_micro(start));
}