#ifndef CIRCUIT_H
#define CIRCUIT_H

#include<unordered_map>
#include<unordered_set>
#include<iostream>
#include"Logic_Gate.h"

/*
������ͼ֮���������������ɾ������
VPI�ӿ��޷��������߼��ŵ��ڽ��ţ���Ҫ�����߼��ŵ�����������н����ڵ���������
*/

class Circuit
{
	std::unordered_map<std::string, LogicGate> Gates;//�߼��ż��ϣ���ͼ�нڵ㼯��		
	//�߼���������Ϊʶ���߼��ŵ�Ψһ��ʶ

	std::unordered_map<std::string, std::vector<std::string>>adj;//�ڽӱ�
	std::unordered_set<std::string>visited;//��ǽڵ��Ƿ񱻷���
	std::unordered_set<std::string>recStack;//�ݹ�ջ
	std::vector<std::vector<std::string>> circles; // �洢���л�


public:


	//����������ڽӱ����ڵ���
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

	//�����߼��ű����������������ͼ
	Circuit(const std::unordered_map<std::string, LogicGate>& Nodes, const std::unordered_map<std::string, std::string>& outputToGate, const std::unordered_map<std::string, std::vector<std::string>>& inputToGate)
	{
		//��������ͼ�ڵ�
		Gates = Nodes;

		//���������
		//�����������ҵ������źţ���Ϊ����߼��ź������߼�������ӱ�
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
				// �ҵ������ӻ�����ʼ�㵽��ǰ�ڵ��������
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
				circle.push_back(next); // ��ӵ�ǰ�ڵ�
				circles.push_back(circle);
				recStack.erase(next); // �ӵݹ�ջ���Ƴ�������ʼ�ڵ㣬�����ظ���¼
			}
		}

		if (recStack.find(v) != recStack.end())
		{
			recStack.erase(v); // �ӵݹ�ջ���Ƴ���ǰ�ڵ�
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

