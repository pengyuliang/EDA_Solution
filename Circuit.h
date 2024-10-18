#ifndef CIRCUIT_H
#define CIRCUIT_H

#include<unordered_map>
#include"Logic_Gate.h"
using namespace std;

/*
建立起图之后，无需对其进行添加删除操作
VPI接口无法解析出逻辑门的邻接门，需要根据逻辑门的输入输出自行建立节点的连接情况
*/

//邻接表结点
struct GNode
{
	LogicGate Gate;
	GNode* next;
};


class Circuit
{
	unordered_map<string, LogicGate> Gates;//逻辑门集合，即图中节点集合		

	vector<vector<int>> adj;//邻接表


public:
	
	//addEdge待补充
	void addEdge(int start, vector<int> end){};

	
	//根据逻辑门表，输入输出表
	Circuit(const unordered_map<string, LogicGate>& Nodes, const unordered_map<string, string>& outputToGate, const unordered_map<string, vector<string>>& inputToGate)
	{
		Gates = Nodes;


	}

	//Circuit(const vector<LogicGate>& Nodes)
	//{
	//	Gates = Nodes;
	//	int NodesSize = static_cast<int>(Nodes.size());

	//	unordered_map<string, vector<int>> input;//键值为输入信号名称，值为逻辑门编号
	//	unordered_map<string , int> output;//键值为输出信号名称，值为逻辑门编号

	//	//记录逻辑门的输入和输出情况
	//	for (int i = 0; i < NodesSize; i++)
	//	{
	//		output.insert({ Gates[i].port[0], i });

	//		input[Gates[i].port[1]].push_back(i);
	//		if (Gates[i].type != 3)
	//		{
	//			input[Gates[i].port[2]].push_back(i);
	//		}
	//	}


	//	//根据逻辑门的输入输出表，添加图的边
	//	unordered_map<string, int >::iterator iter_out = output.begin();
	//	unordered_map<string, vector<int>>::iterator iter_in;
	//	for (; iter_out != output.end(); iter_out++)
	//	{
	//		//如果在输入表中找到了某个输出信号，则添加输出逻辑门指向输入逻辑门的边
	//		iter_in = input.find(iter_out->first);
	//		if (iter_in != input.end())
	//		{
	//			addEdge(iter_out->second, iter_in->second);
	//		}

	//	}

	//}

};

#endif // !CIRCUIT_H

