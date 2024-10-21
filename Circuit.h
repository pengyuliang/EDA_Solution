#ifndef CIRCUIT_H
#define CIRCUIT_H

#include<unordered_map>
#include<unordered_set>
#include<iostream>
#include"Logic_Gate.h"

/*
建立起图之后，无需对其进行添加删除操作
VPI接口无法解析出逻辑门的邻接门，需要根据逻辑门的输入输出自行建立节点的连接情况
*/

class Circuit
{
	std::unordered_map<std::string, LogicGate> Gates;//逻辑门集合，即图中节点集合		
	//逻辑门名称作为识别逻辑门的唯一标识

	std::unordered_map<std::string, std::vector<std::string>>adj;//邻接表
	std::unordered_set<std::string>visited;//标记节点是否被访问
	std::unordered_set<std::string>recStack;//递归栈
	std::vector<std::vector<std::string>> circles; // 存储所有环


public:


	//遍历并输出邻接表，用于调试
	void printAdjList() {
		for (const auto& pair : adj) {
			const std::string& vertex = pair.first;
			const std::vector<std::string>& neighbors = pair.second;

			std::cout << vertex << ": ";
			for (size_t i = 0; i < neighbors.size(); ++i) {
				std::cout << neighbors[i];
				if (i < neighbors.size() - 1) {
					std::cout << " -> ";
				}
			}
			std::cout << std::endl;
		}
	}
	
	void addEdge(std::string from,const std::vector<std::string>& to)
	{
		for (auto& it : to)
		{
			adj[from].push_back(it);
		}
	};

	//根据逻辑门表，输入输出表建立有向图
	Circuit(const std::unordered_map<std::string, LogicGate>& Nodes, const std::unordered_map<std::string, std::string>& outputToGate, const std::unordered_map<std::string, std::vector<std::string>>& inputToGate)
	{
		//接收有向图节点
		Gates = Nodes;

		//遍历输出表
		//若在输入中找到输入信号，则为输出逻辑门和输入逻辑门组添加边
		for (const auto& output : outputToGate)
		{
			auto it = inputToGate.find(output.first);
			if (it != inputToGate.end())
			{
				addEdge(output.second,it->second);
			}
		}

	}

	void DFSUtil(std::string v, std::unordered_set<std::string>& visited, std::unordered_set<std::string>& recStack, std::vector<std::string>& path)
	{
		visited.insert(v);
		recStack.insert(v);
		path.push_back(v);

		for (std::string next : adj[v]) 
		{
			if (visited.find(next) == visited.end())
			{
				DFSUtil(next, visited, recStack, path);
			}
			else if (recStack.find(next) != recStack.end()) 
			{
				// 找到环，从环的起始点到当前节点逆序遍历
				std::vector<std::string> circle;
				for (size_t i = path.size() - 1; i != 0; --i) 
				{
					if (path[i] == next) 
					{
						circle.insert(circle.begin(), path[i]);
						break;
					}
					circle.insert(circle.begin(), path[i]);
				}
				circle.push_back(next); // 添加当前节点
				circles.push_back(circle);
				recStack.erase(next); // 从递归栈中移除环的起始节点，避免重复记录
			}
		}

		if (recStack.find(v) != recStack.end())
		{
			recStack.erase(v); // 从递归栈中移除当前节点
		}
		path.pop_back();

	};

	void detectCircle()
	{
		std::vector<std::string>path;

		for (auto& it : Gates)
		{
			if (visited.find((it.second).name) == visited.end())
			{
				DFSUtil((it.second).name, visited, recStack, path);
			}
		}

		printCycles();
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

