cmake_minimum_required(VERSION 3.16)

project(ProcessPilot)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(processpilot
    src/main.cpp
   src/process/process_manager.cpp
     src/config/config_parser.cpp
src/monitor/resource_monitor.cpp
src/dependency/dependency_graph.cpp
src/logging/logger.cpp
src/daemon/daemon.cpp
)
