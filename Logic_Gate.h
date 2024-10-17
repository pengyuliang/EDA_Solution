#ifndef LOGIC_GATE_H
#define LOGIC_GATE_H
#include<string>
#include<vector>
using namespace std;

class LogicGate {
public:
	string name;//逻辑门名称

	vector<string> port;//输入输出信号

	int type;//逻辑门类型，从1开始，与、或、非、与非
	bool isReverse;//是否含有反相器



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
