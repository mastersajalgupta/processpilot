#include "daemon.hpp"

#include <iostream>
#include <csignal>

void Daemon::handleSignal(int signal) {

    if (signal == SIGINT) {
        std::cout << "\nProcessPilot received SIGINT\n";
    }

    else if (signal == SIGTERM) {
        std::cout << "\nProcessPilot received SIGTERM\n";
    }
}

void Daemon::setupSignals() {

    signal(SIGINT, Daemon::handleSignal);
    signal(SIGTERM, Daemon::handleSignal);
}
