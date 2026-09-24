#include "dependency_graph.hpp"

void DependencyGraph::addService(const std::string& service) {

    if (dependencies.find(service) == dependencies.end()) {
        dependencies[service] = {};
    }
}

void DependencyGraph::addDependency(
    const std::string& service,
    const std::string& dependency
) {

    dependencies[service].push_back(dependency);
}

bool DependencyGraph::canStart(const std::string& service) {

    if (dependencies.find(service) == dependencies.end()) {
        return true;
    }

    for (const std::string& dependency : dependencies[service]) {

        if (dependencies.find(dependency) == dependencies.end()) {
            return false;
        }
    }

    return true;
}
