#ifndef PROCESS_MANAGER_HPP
#define PROCESS_MANAGER_HPP

#include <sys/types.h>

class ProcessManager {
public:
    pid_t startProcess(const char* program, const char* argument = "1000");
    bool stopProcess(pid_t pid);
    bool isRunning(pid_t pid);
};

#endif
