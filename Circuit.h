#ifndef CIRCUIT_H
#define CIRCUIT_H

#include<unordered_map>
#include<unordered_set>
#include"Logic_Gate.h"

/*
������ͼ֮���������������ɾ������
VPI�ӿ��޷��������߼��ŵ��ڽ��ţ���Ҫ�����߼��ŵ�����������н����ڵ���������
*/

class Circuit
{
	std::unordered_map<std::string, LogicGate> Gates;//�߼��ż��ϣ���ͼ�нڵ㼯��		
	//�߼���������Ϊʶ���߼��ŵ�Ψһ��ʶ

	std::unordered_map<std::string, std::vector<std::string>>adj;
	std::unordered_set<std::string>visited;
	std::unordered_set<std::string>recStack;
	std::vector<std::vector<std::string>> circles; // �洢���л�


public:
	
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

		//�������
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
			if (visited.find(next) == visited.end())//�ڽӽڵ�û�б�����
			{
				DFSUtil(next, visited, recStack, path);
			}
			else if (recStack.find(next) != recStack.end())//�ڽӽڵ��ڵݹ�ջ�У������ҵ���һ����·
			{
				std::vector<std::string> circle;
				for (size_t i = path.size() - 1; i != 0; --i) //�����������·����¼��Circle��
				{
					if (path[i] == next) 
					{
						circle.insert(circle.begin(), path[i]);
						break;
					}
					circle.insert(circle.begin(), path[i]);
				}
				circle.push_back(next);
				circles.push_back(circle);
			}
		}

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
	}
};

#endif // !CIRCUIT_H

