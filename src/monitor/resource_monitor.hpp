#ifndef RESOURCE_MONITOR_HPP
#define RESOURCE_MONITOR_HPP

#include <sys/types.h>

class ResourceMonitor {
public:
    void showMemory(pid_t pid);
    void showCPU(pid_t pid);
};

#endif
