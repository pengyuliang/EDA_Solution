#ifndef LOGIC_GATE_H
#define LOGIC_GATE_H
#include<string>
#include<vector>
using namespace std;

class LogicGate {
public:
	string name;//�߼�������

	vector<string> port;//��������ź�

	int type;//�߼������ͣ���1��ʼ���롢�򡢷ǡ����
	bool isReverse;//�Ƿ��з�����



	LogicGate(string in_name, int in_type, string port0, string port1, string port2 = "")
	{
		name = in_name;
		type = in_type;

		port.push_back(port0);
		port.push_back(port1);
		if (type != 3)
			port.push_back(port2);
		

		if (type == 3 || type == 4)
		{
			isReverse = 1;
		}
		else
		{
			isReverse = 0;
		}
	}
};


#endif // !LOGIC_GATE_H
