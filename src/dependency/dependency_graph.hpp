#ifndef DEPENDENCY_GRAPH_HPP
#define DEPENDENCY_GRAPH_HPP

#include <string>
#include <map>
#include <vector>

class DependencyGraph {
public:
    void addService(const std::string& service);
    void addDependency(
        const std::string& service,
        const std::string& dependency
    );

    bool canStart(const std::string& service);

private:
    std::map<std::string, std::vector<std::string>> dependencies;
};

#endif
