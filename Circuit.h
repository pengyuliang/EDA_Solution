#ifndef CIRCUIT_H  
#define CIRCUIT_H  

#include<unordered_map>  
#include<unordered_set>  
#include<vector>  
#include<iostream>  
#include"Logic_Gate.h"  

class Circuit {
    std::unordered_map<std::string, LogicGate> Gates; // �߼��ż��ϣ���ͼ�нڵ㼯��  
    std::unordered_map<std::string, std::vector<std::string>> adj; // �ڽӱ�  
    std::unordered_set<std::string> visited; // ��ǽڵ��Ƿ񱻷���  
    std::unordered_set<std::string> recStack; // �ݹ�ջ  
    std::vector<std::vector<std::string>> circles; // �洢���л�  
    std::unordered_map<std::string, std::vector<std::vector<std::string>>> nodeCycles; // ÿ���ڵ����Ļ�  

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
                // �ҵ������ӻ�����ʼ�㵽��ǰ�ڵ��������
                std::vector<std::string> circle;
                for (auto it = path.rbegin(); it != path.rend(); ++it) {
                    if (*it == next) {
                        break;
                    }
                    circle.push_back(*it);
                }
                circle.push_back(next); // ��ӵ�ǰ�ڵ��γɱջ�
                circles.push_back(circle);

                // ����ÿ���ڵ����Ļ�
                for (auto node : circle) {
                    if (nodeCycles.find(node) == nodeCycles.end()) {
                        nodeCycles[node] = std::vector<std::vector<std::string>>{ circle };
                    }
                    else {
                        nodeCycles[node].push_back(circle);
                    }
                }

                recStack.erase(next); // �ӵݹ�ջ���Ƴ�������ʼ�ڵ㣬�����ظ���¼
            }
        }

        recStack.erase(v); // ����ʱ�ӵݹ�ջ���Ƴ���ǰ�ڵ�  
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