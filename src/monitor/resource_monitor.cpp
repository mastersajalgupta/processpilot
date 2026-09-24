#include "resource_monitor.hpp"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <unistd.h>

void ResourceMonitor::showMemory(pid_t pid) {

    std::string path = "/proc/" + std::to_string(pid) + "/status";

    std::ifstream file(path);

    if (!file) {
        std::cout << "Unable to read memory information\n";
        return;
    }

    std::string line;

    while (std::getline(file, line)) {

        if (line.find("VmRSS:") == 0) {
            std::cout << "Memory Usage: " << line.substr(6) << "\n";
            return;
        }
    }

    std::cout << "Memory information not found\n";
}

void ResourceMonitor::showCPU(pid_t pid) {

    std::string processPath =
        "/proc/" + std::to_string(pid) + "/stat";

    std::ifstream processFile(processPath);

    if (!processFile) {
        std::cout << "Unable to read CPU information\n";
        return;
    }

    std::string data;
    std::getline(processFile, data);

    size_t pos = data.rfind(')');

    if (pos == std::string::npos) {
        std::cout << "Unable to read CPU information\n";
        return;
    }

    std::string remaining = data.substr(pos + 2);

    std::stringstream ss(remaining);

    char state;
    long value;

    ss >> state;

    for (int i = 0; i < 11; i++) {
        ss >> value;
    }

    long processTime1 = value;

    std::ifstream cpuFile("/proc/stat");

    if (!cpuFile) {
        std::cout << "Unable to read CPU information\n";
        return;
    }

    std::string line;
    std::getline(cpuFile, line);

    std::stringstream cpuSS(line);

    std::string cpu;
    long user, nice, system, idle, iowait, irq, softirq, steal;

    cpuSS >> cpu
          >> user
          >> nice
          >> system
          >> idle
          >> iowait
          >> irq
          >> softirq
          >> steal;

    long total1 = user + nice + system + idle +
                  iowait + irq + softirq + steal;

    sleep(1);

    processFile.close();
    processFile.open(processPath);

    if (!processFile) {
        std::cout << "Unable to read CPU information\n";
        return;
    }

    std::getline(processFile, data);

    pos = data.rfind(')');

    if (pos == std::string::npos) {
        return;
    }

    remaining = data.substr(pos + 2);

    ss.clear();
    ss.str(remaining);

    ss >> state;

    for (int i = 0; i < 11; i++) {
        ss >> value;
    }

    long processTime2 = value;

    cpuFile.close();
    cpuFile.open("/proc/stat");

    std::getline(cpuFile, line);

    cpuSS.clear();
    cpuSS.str(line);

    cpuSS >> cpu
          >> user
          >> nice
          >> system
          >> idle
          >> iowait
          >> irq
          >> softirq
          >> steal;

    long total2 = user + nice + system + idle +
                  iowait + irq + softirq + steal;

    long processDiff = processTime2 - processTime1;
    long totalDiff = total2 - total1;

    double cpuUsage = 0;

    if (totalDiff > 0) {
        cpuUsage = (double)processDiff / totalDiff * 100;
    }

    std::cout << "CPU Usage: " << cpuUsage << "%\n";
}
