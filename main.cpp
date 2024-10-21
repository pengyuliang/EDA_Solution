#include<iostream>
#include"Circuit.h"
using namespace std;


int main() {

	/*
	* ��������ʱ
	* ��һ���ֶ�Ϊor2��not1��nand2��and2����ʽ����
	* �ڶ���Ϊ�߼�������
	* ���Ϊ����������ź�
	*/

	//�޷��ڶ���ʱʹ���±���Ϊ�߼��ŵ�Ψһ��ʶ
	//����ʱ�������߼���������ΪΨһ��ʶ
	//����ʱ������unordered_map
	// unordered_map<string,<LogicGate>>����Ϊ�߼������ơ�ֵΪ�߼��Ŷ���
	// unordered_map<string,string>����Ϊ����ź����ơ�ֵΪ�߼������ƣ�ÿ���߼�������źž���ͬ�����迼�ǹ�ϣ�������⣩
	// unordered_map<string,vector<string>>����Ϊ�����ź����ơ�ֵΪ�߼����������飨һ���źſ������������߼��ţ�



    unordered_map<string, LogicGate> nodes = {
        {"A", LogicGate("A", 1, "Z", "X", "H")},
        {"B", LogicGate("B", 2, "M", "Z", "H")},
        {"C", LogicGate("C", 3, "N", "M")},
        {"D", LogicGate("D", 3, "P", "N")},
        {"E", LogicGate("E", 3, "Q", "P")},
        {"F", LogicGate("F", 3, "H", "Q")}
    };
    unordered_map<string, string> outputToGate = {
        {"Z", "A"},
        {"M", "B"},
        {"N", "C"},
        {"P", "D"},
        {"Q", "E"},
        {"H", "F"}
    };
    unordered_map<string, vector<string>> inputToGate = {
        {"X", {"A"}},
        
        {"Z", {"B"}},
        {"M", {"C"}},
        {"N", {"D"}},
        {"P", {"E"}},
        {"Q", {"F"}},
        {"H", {"A", "B"}}
    };

    Circuit circuit(nodes, outputToGate, inputToGate);
    circuit.detectCircle();
    circuit.printAdjList();

    return 0;

}