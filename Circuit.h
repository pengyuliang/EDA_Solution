#ifndef CIRCUIT_H
#define CIRCUIT_H

#include<unordered_map>
#include"Logic_Gate.h"
using namespace std;

/*
������ͼ֮���������������ɾ������
VPI�ӿ��޷��������߼��ŵ��ڽ��ţ���Ҫ�����߼��ŵ�����������н����ڵ���������
*/

//�ڽӱ���
struct GNode
{
	LogicGate Gate;
	GNode* next;
};


class Circuit
{
	vector<LogicGate> Gates;//�߼��ż��ϣ���ͼ�нڵ㼯��
							//�߼������������еı����ΪΨһ��ʶ

	vector<vector<int>> adj;//�ڽӱ�


public:
	
	//addEdge������
	void addEdge(int start, vector<int> end){};

	//�����߼���ʱ����������źź������źŵ�ӳ��
	//
	Circuit(const vector<LogicGate>& Nodes, const unordered_map<string, int>& outputToGate, const unordered_map<string, vector<int>>& inputToGate)
	{
		Gates = Nodes;


	}

	Circuit(const vector<LogicGate>& Nodes)
	{
		Gates = Nodes;
		int NodesSize = static_cast<int>(Nodes.size());

		unordered_map<string, vector<int>> input;//��ֵΪ�����ź����ƣ�ֵΪ�߼��ű��
		unordered_map<string , int> output;//��ֵΪ����ź����ƣ�ֵΪ�߼��ű��

		//��¼�߼��ŵ������������
		for (int i = 0; i < NodesSize; i++)
		{
			output.insert({ Gates[i].port[0], i });

			input[Gates[i].port[1]].push_back(i);
			if (Gates[i].type != 3)
			{
				input[Gates[i].port[2]].push_back(i);
			}
		}


		//�����߼��ŵ�������������ͼ�ı�
		unordered_map<string, int >::iterator iter_out = output.begin();
		unordered_map<string, vector<int>>::iterator iter_in;
		for (; iter_out != output.end(); iter_out++)
		{
			//�������������ҵ���ĳ������źţ����������߼���ָ�������߼��ŵı�
			iter_in = input.find(iter_out->first);
			if (iter_in != input.end())
			{
				addEdge(iter_out->second, iter_in->second);
			}

		}

	}

};

#endif // !CIRCUIT_H

