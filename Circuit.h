#ifndef CIRCUIT_H  
#define CIRCUIT_H  

#include<unordered_map>  
#include<unordered_set>  
#include<vector>  
#include<iostream>  
#include"Logic_Gate.h"  

class Circuit {
    std::unordered_map<std::string, LogicGate> Gates; // 逻辑门集合，即图中节点集合  
    std::unordered_map<std::string, std::vector<std::string>> adj; // 邻接表  
    std::unordered_set<std::string> visited; // 标记节点是否被访问  
    std::unordered_set<std::string> recStack; // 递归栈  
    std::vector<std::vector<std::string>> circles; // 存储所有环  
    std::unordered_map<std::string, std::vector<std::vector<std::string>>> nodeCycles; // 每个节点参与的环  

public:
    void addEdge(std::string from, const std::vector<std::string>& to) {
        for (auto& it : to) {
            adj[from].push_back(it);
        }
    }

    Circuit(const std::unordered_map<std::string, LogicGate>& Nodes, const std::unordered_map<std::string, std::string>& outputToGate, const std::unordered_map<std::string, std::vector<std::string>>& inputToGate)
        : Gates(Nodes) {
        for (const auto& output : outputToGate) {
            auto it = inputToGate.find(output.first);
            if (it != inputToGate.end()) {
                addEdge(output.second, it->second);
            }
        }
    }

    void DFSUtil(std::string v, std::unordered_set<std::string>& visited, std::unordered_set<std::string>& recStack, std::vector<std::string>& path) {
        visited.insert(v);
        recStack.insert(v);
        path.push_back(v);

        for (std::string next : adj[v]) {
            if (visited.find(next) == visited.end()) {
                DFSUtil(next, visited, recStack, path);
            }
            else if (recStack.find(next) != recStack.end()) {
                // 找到环，从环的起始点到当前节点逆序遍历
                std::vector<std::string> circle;
                for (auto it = path.rbegin(); it != path.rend(); ++it) {
                    if (*it == next) {
                        break;
                    }
                    circle.push_back(*it);
                }
                circle.push_back(next); // 添加当前节点形成闭环
                circles.push_back(circle);

                // 更新每个节点参与的环
                for (auto node : circle) {
                    if (nodeCycles.find(node) == nodeCycles.end()) {
                        nodeCycles[node] = std::vector<std::vector<std::string>>{ circle };
                    }
                    else {
                        nodeCycles[node].push_back(circle);
                    }
                }

                recStack.erase(next); // 从递归栈中移除环的起始节点，避免重复记录
            }
        }

        recStack.erase(v); // 回溯时从递归栈中移除当前节点  
        path.pop_back();
    }

    void detectCircles() {
        std::vector<std::string> path;
        for (auto& it : Gates) {
            if (visited.find(it.second.name) == visited.end()) {
                DFSUtil(it.second.name, visited, recStack, path);
            }
        }

        findCommonCycles();
        printCycles();
    }

    void findCommonCycles() {
        std::cout << "All cycles involving each node:" << std::endl;
        for (const auto& nodeCyclesPair : nodeCycles) {
            const std::string& nodeName = nodeCyclesPair.first;
            const std::vector<std::vector<std::string>>& cycles = nodeCyclesPair.second;

            std::cout << "Node " << nodeName << " is involved in cycles: ";
            for (const auto& cycle : cycles) {
                bool first = true;
                for (const auto& node : cycle) {
                    if (!first) {
                        std::cout << " -> ";
                    }
                    std::cout << node;
                    first = false;
                }
                std::cout << std::endl;
            }
        }
    }

    void printCycles() {
        std::cout << "Detected cycles:" << std::endl;
        for (const auto& circle : circles) {
            for (const auto& node : circle) {
                std::cout << node << " ";
            }
            std::cout << std::endl;
        }
    }
};

#endif // !CIRCUIT_H