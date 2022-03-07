#include "philo.h"

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
    return ((end.tv_sec * 1000000 + end.tv_usec) -
    (start.tv_sec * 1000000 + start.tv_usec));
}