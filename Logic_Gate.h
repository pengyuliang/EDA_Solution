#ifndef LOGIC_GATE_H
#define LOGIC_GATE_H
#include<string>
#include<vector>

class LogicGate {
public:
	std::string name;//�߼�������

	std::vector<std::string> port;//��������ź�

	int type;//�߼������ͣ���1��ʼ���롢�򡢷ǡ����
	bool isReverse;//�Ƿ��з�����



	LogicGate(std::string in_name, int in_type, std::string port0, std::string port1, std::string port2 = "")
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
