#include <iostream>
#include <fstream>
#include <unistd.h>
#include <cstdio>

#include "process/process_manager.hpp"
#include "config/config_parser.hpp"
#include "monitor/resource_monitor.hpp"
#include "dependency/dependency_graph.hpp"
#include "logging/logger.hpp"
#include "daemon/daemon.hpp"
int main(int argc, char* argv[]) {

    if (argc < 2) {
        std::cout << "Usage: ./processpilot <start|stop|restart|status|test-crash|auto-recover|config-test|monitor|dependency-test|log-test|signal-test>\n";
        return 1;
    }

    std::string command = argv[1];

    ProcessManager manager;

    const char* pidFile = "process.pid";

    if (command == "start") {

        ConfigParser config;

        if (!config.load("../configs/demo.service")) {
            std::cout << "Failed to load configuration\n";
            return 1;
        }

        std::string program = config.get("program");
        std::string argument = config.get("argument");

        pid_t pid = manager.startProcess(
            program.c_str(),
            argument.c_str()
        );

        if (pid == -1) {
            std::cout << "Failed to start process\n";
            return 1;
        }

        std::ofstream file(pidFile);
        file << pid;
        file.close();

        std::cout << "Process started\n";
        std::cout << "PID: " << pid << "\n";
    }

    else if (command == "stop") {

        std::ifstream file(pidFile);

        if (!file) {
            std::cout << "Process is not running\n";
            return 0;
        }

        pid_t pid;
        file >> pid;
        file.close();

        if (!manager.isRunning(pid)) {
            std::cout << "Process is not running\n";
            std::remove(pidFile);
            return 0;
        }

        if (manager.stopProcess(pid)) {
            std::cout << "Process stopped\n";
            std::remove(pidFile);
        }
        else {
            std::cout << "Failed to stop process\n";
            return 1;
        }
    }

    else if (command == "status") {

        std::ifstream file(pidFile);

        if (!file) {
            std::cout << "Process is not running\n";
            return 0;
        }

        pid_t pid;
        file >> pid;
        file.close();

        if (manager.isRunning(pid)) {
            std::cout << "Process is running\n";
            std::cout << "PID: " << pid << "\n";
        }
        else {
            std::cout << "Process is not running\n";
            std::remove(pidFile);
        }
    }

    else if (command == "restart") {

        std::ifstream file(pidFile);

        if (file) {

            pid_t pid;
            file >> pid;
            file.close();

            if (manager.isRunning(pid)) {
                manager.stopProcess(pid);
                std::cout << "Old process stopped\n";
            }
        }

        std::remove(pidFile);

        ConfigParser config;

        if (!config.load("../configs/demo.service")) {
            std::cout << "Failed to load configuration\n";
            return 1;
        }

        std::string program = config.get("program");
        std::string argument = config.get("argument");

        pid_t pid = manager.startProcess(
            program.c_str(),
            argument.c_str()
        );

        if (pid == -1) {
            std::cout << "Failed to restart process\n";
            return 1;
        }

        std::ofstream out(pidFile);
        out << pid;
        out.close();

        std::cout << "Process restarted\n";
        std::cout << "New PID: " << pid << "\n";
    }

    else if (command == "test-crash") {

        pid_t pid = manager.startProcess("/usr/bin/sleep", "5");

        if (pid == -1) {
            std::cout << "Failed to start test process\n";
            return 1;
        }

        std::cout << "Test process started\n";
        std::cout << "PID: " << pid << "\n";
        std::cout << "Process will exit after 5 seconds\n";

        sleep(6);

        if (manager.isRunning(pid)) {
            std::cout << "Process is still running\n";
        }
        else {
            std::cout << "Process exited unexpectedly\n";
        }
    }

    else if (command == "auto-recover") {

        pid_t pid = manager.startProcess("/usr/bin/sleep", "5");

        if (pid == -1) {
            std::cout << "Failed to start process\n";
            return 1;
        }

        std::cout << "Process started\n";
        std::cout << "PID: " << pid << "\n";

        sleep(6);

        if (!manager.isRunning(pid)) {

            std::cout << "Process crashed or exited\n";
            std::cout << "Restarting process...\n";

            pid = manager.startProcess("/usr/bin/sleep");

            if (pid == -1) {
                std::cout << "Recovery failed\n";
                return 1;
            }

            std::cout << "Process recovered\n";
            std::cout << "New PID: " << pid << "\n";
        }
        else {
            std::cout << "Process is still running\n";
        }
    }

    else if (command == "config-test") {

        ConfigParser config;

        if (!config.load("../configs/demo.service")) {
            std::cout << "Failed to load configuration\n";
            return 1;
        }

        std::cout << "Configuration loaded successfully\n";
        std::cout << "Name: " << config.get("name") << "\n";
        std::cout << "Program: " << config.get("program") << "\n";
        std::cout << "Argument: " << config.get("argument") << "\n";
        std::cout << "Restart: " << config.get("restart") << "\n";
        std::cout << "Depends On: " << config.get("depends_on") << "\n";
    }

    else if (command == "monitor") {

        std::ifstream file(pidFile);

        if (!file) {
            std::cout << "Process is not running\n";
            return 0;
        }

        pid_t pid;
        file >> pid;
        file.close();

        if (!manager.isRunning(pid)) {
            std::cout << "Process is not running\n";
            return 0;
        }

        ResourceMonitor monitor;

        std::cout << "Monitoring PID: " << pid << "\n";

        monitor.showMemory(pid);
        monitor.showCPU(pid);
    }
else if (command == "dependency-test") {

    DependencyGraph graph;

    graph.addService("database");
    graph.addService("backend");

    graph.addDependency("backend", "database");

    if (graph.canStart("backend")) {
        std::cout << "Dependency satisfied\n";
    }
    else {
        std::cout << "Dependency not satisfied\n";
    }
}
else if (command == "log-test") {

    Logger logger;

    logger.log("ProcessPilot logger test");

    std::cout << "Log message written successfully\n";
}

else if (command == "signal-test") {

    Daemon::setupSignals();

    std::cout << "Signal handling enabled\n";
    std::cout << "Press Ctrl+C to test SIGINT\n";

    while (true) {
        sleep(1);
    }
}
    else {

        std::cout << "Unknown command\n";
        std::cout << "Usage: ./processpilot <start|stop|restart|status|test-crash|auto-recover|config-test|monitor>\n";
        return 1;
    }

    return 0;
}
