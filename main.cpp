#include<iostream>
using namespace std;


int main() {

	/*
	* 读入数据时
	* 第一个字段为or2，not1，nand2或and2，表式类型
	* 第二个为逻辑门名称
	* 随后为输出、输入信号
	*/

	//无法在读入时使用下标作为逻辑门的唯一标识
	//读入时可以用逻辑门名称作为唯一标识
	//读入时用三个unordered_map
	// unordered_map<string,<LogicGate>>，键为逻辑门名称、值为逻辑门对象
	// unordered_map<string,string>，键为输出信号名称、值为逻辑门名称（每个逻辑门输出信号均不同，无需考虑哈希表覆盖问题）
	// unordered_map<string,vector<string>>，键为输入信号名称、值为逻辑门名称数组（一个信号可能输入进多个逻辑门）



}