#ifndef DAEMON_HPP
#define DAEMON_HPP

class Daemon {
public:
    static void handleSignal(int signal);
    static void setupSignals();
};

#endif
