# ProcessPilot

**ProcessPilot** is a lightweight Linux process and service supervision system built in **modern C++**.

It provides a command-line interface to start, stop, restart, and monitor background processes. It can also detect terminated processes, perform basic automatic recovery, monitor CPU and memory usage, handle Linux signals, manage configuration, dependencies, and maintain process logs.

## Features

* Start background processes
* Stop running processes
* Check process status
* Restart processes
* Detect unexpected process termination
* Automatic process recovery
* Configuration-based process startup
* Basic service dependency management
* CPU usage monitoring
* Memory usage monitoring
* Linux signal handling
* Process logging
* CMake-based build system
* Linux `/proc` filesystem integration

## Project Structure

```text
processpilot/
├── src/
│   ├── main.cpp
│   ├── daemon/
│   │   ├── daemon.cpp
│   │   └── daemon.hpp
│   ├── process/
│   │   ├── process_manager.cpp
│   │   └── process_manager.hpp
│   ├── config/
│   │   ├── config_parser.cpp
│   │   └── config_parser.hpp
│   ├── monitor/
│   │   ├── resource_monitor.cpp
│   │   └── resource_monitor.hpp
│   ├── dependency/
│   │   ├── dependency_graph.cpp
│   │   └── dependency_graph.hpp
│   ├── ipc/
│   │   ├── unix_socket.cpp
│   │   └── unix_socket.hpp
│   └── logging/
│       ├── logger.cpp
│       └── logger.hpp
├── cli/
│   └── processpilot_cli.cpp
├── configs/
│   └── demo.service
├── tests/
│   ├── process_tests.cpp
│   ├── config_tests.cpp
│   └── dependency_tests.cpp
├── docs/
│   ├── architecture.md
│   └── requirements.md
├── CMakeLists.txt
└── README.md
```

## Technologies Used

* **C++17**
* **Linux**
* **CMake**
* **GCC**
* Linux system calls
* `/proc` filesystem
* POSIX signals
* `fork()`
* `exec()`
* `kill()`
* `waitpid()`

## Requirements

* Linux operating system
* GCC/G++
* CMake
* Git

For Ubuntu/Debian:

```bash
sudo apt update
sudo apt install build-essential cmake git
```

## Build

Clone the repository:

```bash
git clone https://github.com/mastersajalgupta/processpilot.git
cd processpilot
```

Create the build directory:

```bash
mkdir build
cd build
```

Configure the project:

```bash
cmake ..
```

Build:

```bash
make
```

The executable will be created as:

```text
build/processpilot
```

## Usage

Run the executable from the `build` directory.

### Start a process

```bash
./processpilot start
```

Example:

```text
Process started
PID: 1234
```

### Check status

```bash
./processpilot status
```

Example:

```text
Process is running
PID: 1234
```

### Stop a process

```bash
./processpilot stop
```

### Restart a process

```bash
./processpilot restart
```

### Test crash detection

```bash
./processpilot test-crash
```

### Test automatic recovery

```bash
./processpilot auto-recover
```

Example:

```text
Process started
PID: 3949
Process crashed or exited
Restarting process...
Process recovered
New PID: 3954
```

### Test configuration

```bash
./processpilot config-test
```

### Test dependency management

```bash
./processpilot dependency-test
```

### Test logging

```bash
./processpilot log-test
```

### Test signal handling

```bash
./processpilot signal-test
```

Press `Ctrl+C` to send `SIGINT`.

## Configuration

The demo service configuration is stored in:

```text
configs/demo.service
```

Example:

```text
name=demo
program=/usr/bin/sleep
argument=1000
restart=true
depends_on=
```

ProcessPilot reads this configuration to determine which program should be started and which recovery policy should be used.

## Resource Monitoring

ProcessPilot uses the Linux `/proc` filesystem to obtain process information.

For example:

```text
/proc/<PID>/status
/proc/<PID>/stat
/proc/stat
```

Memory information is obtained from `/proc/<PID>/status`.

CPU usage is calculated using process CPU time and system CPU statistics from `/proc`.

## Process Recovery

ProcessPilot can detect when a monitored process has terminated.

The recovery flow is:

```text
Start Process
     ↓
Monitor Process
     ↓
Process Terminates
     ↓
Detect Failure
     ↓
Restart Process
     ↓
Continue Monitoring
```

## Dependency Management

ProcessPilot contains a basic dependency graph for services.

For example:

```text
Database
   ↓
Backend
```

The backend service depends on the database service.

## Logging

ProcessPilot provides a simple logging component for recording important events.

Example:

```text
Thu Sep 24 16:45:57 2026
ProcessPilot logger test
```

## Learning Objectives

This project was developed to understand practical Linux system programming concepts, including:

* Process creation
* Process termination
* Process monitoring
* Signals
* `/proc` filesystem
* CPU and memory monitoring
* Configuration parsing
* Dependency management
* Logging
* CMake
* Modern C++

## Project Status

**Status: Working Prototype**

The core process supervision functionality is implemented and tested on Ubuntu Linux.

The project can be extended with:

* Full Unix socket IPC
* Dedicated background daemon
* Separate CLI client
* Advanced dependency startup ordering
* More comprehensive automated tests
* Multiple service configurations
* Restart policies and restart limits
* Improved graceful shutdown
* Production-level error handling

## Author

**Sajal Gupta**

B.Tech Computer Science and Engineering

GitHub: `mastersajalgupta`
