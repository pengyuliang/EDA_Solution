#include <iostream>
#include <fstream>
#include <vector>
#include <regex>
#include <string>
#include <tuple>
#include"Circuit.h"
using namespace std;


tuple<unordered_map<string, LogicGate>, unordered_map<string, string>, unordered_map<string, vector<string>>> parseLogicGates(const string& filename) {
    ifstream file(filename);
    string line;
    unordered_map<string, LogicGate> gates;
    unordered_map<string, string> outputToGate;
    unordered_map<string, vector<string>> inputToGate;

    // 正则表达式匹配Combined Logic Module Defination模块开始
    regex combinedLogicRegex(R"(//\*\*\*\*\*\* Combined Logic Module Defination \*\*\*\*\*\*)");
    smatch match;

    // 正则表达式匹配逻辑门定义
    regex gateRegex(R"((\w+)\s+(\w+)\((\w+)(?:,\s*(\w+))?(?:,\s*(\w+))?\);)");
    smatch gateMatch;

    bool isCombinedLogicModule = false;

    while (getline(file, line)) {
        // 检查是否是Combined Logic Module Defination模块
        if (regex_search(line, match, combinedLogicRegex)) {
            isCombinedLogicModule = true;
            cout << "Found Combined Logic Module Defination" << endl;
            continue;
        }

        if (isCombinedLogicModule) {
            // 匹配逻辑门定义
            if (regex_search(line, gateMatch, gateRegex)) {
                string gateType = gateMatch[1];
                string gateInstance = gateMatch[2];
                string outputPort = gateMatch[3];
                string inputPort1 = gateMatch[4];
                string inputPort2 = gateMatch[5];

                int type = 0;
                if (gateType == "and2") type = 1;
                else if (gateType == "or2") type = 2;
                else if (gateType == "not1") type = 3;
                else if (gateType == "nand2") type = 4;

                if (type) {
                    gates.insert({ gateInstance, LogicGate(gateInstance, type, outputPort, inputPort1, inputPort2) });
                    //cout << "Found gate: " << gateInstance << " of type " << gateType << " with ports: " << outputPort << ", " << inputPort1 << ", " << inputPort2 << endl;

                    // 更新outputToGate映射
                    outputToGate[outputPort] = gateInstance;

                    // 更新inputToGate映射
                    inputToGate[inputPort1].push_back(gateInstance);
                    if (!inputPort2.empty()) {
                        inputToGate[inputPort2].push_back(gateInstance);
                    }
                }
            }
            else if (line.find("endmodule") != string::npos) {
                // 遇到endmodule，表示模块定义结束
                isCombinedLogicModule = false;
                cout << "End of Combined Logic Module Defination" << endl;
            }
        }
    }

    return make_tuple(gates, outputToGate, inputToGate);
}


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



    auto [gates, outputToGate, inputToGate] = parseLogicGates("D:\\Desktop\\testcase.txt");

    

    Circuit circuit(gates, outputToGate, inputToGate);
    circuit.detectCircles();
       
    cout << gates.size() << endl;

    return 0;

}