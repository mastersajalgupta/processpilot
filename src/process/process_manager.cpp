#include "process_manager.hpp"

#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <fstream>
#include <string>

pid_t ProcessManager::startProcess(const char* program, const char* argument) {

    pid_t pid = fork();

    if (pid < 0) {
        return -1;
    }

    if (pid == 0) {
        execl(program, program, argument, (char*)nullptr);
        _exit(1);
    }

    return pid;
}

bool ProcessManager::stopProcess(pid_t pid) {

    if (kill(pid, SIGTERM) == -1) {
        return false;
    }

    waitpid(pid, nullptr, 0);

    return true;
}

bool ProcessManager::isRunning(pid_t pid) {

    if (kill(pid, 0) != 0) {
        return false;
    }

    std::string path = "/proc/" + std::to_string(pid) + "/stat";

    std::ifstream file(path);

    if (!file) {
        return false;
    }

    std::string data;
    std::getline(file, data);

    size_t pos = data.rfind(')');

    if (pos == std::string::npos) {
        return false;
    }

    char state = data[pos + 2];

    if (state == 'Z') {
        return false;
    }

    return true;
}
