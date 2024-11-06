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

    // ������ʽƥ��Combined Logic Module Definationģ�鿪ʼ
    regex combinedLogicRegex(R"(//\*\*\*\*\*\* Combined Logic Module Defination \*\*\*\*\*\*)");
    smatch match;

    // ������ʽƥ���߼��Ŷ���
    regex gateRegex(R"((\w+)\s+(\w+)\((\w+)(?:,\s*(\w+))?(?:,\s*(\w+))?\);)");
    smatch gateMatch;

    bool isCombinedLogicModule = false;

    while (getline(file, line)) {
        // ����Ƿ���Combined Logic Module Definationģ��
        if (regex_search(line, match, combinedLogicRegex)) {
            isCombinedLogicModule = true;
            cout << "Found Combined Logic Module Defination" << endl;
            continue;
        }

        if (isCombinedLogicModule) {
            // ƥ���߼��Ŷ���
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

                    // ����outputToGateӳ��
                    outputToGate[outputPort] = gateInstance;

                    // ����inputToGateӳ��
                    inputToGate[inputPort1].push_back(gateInstance);
                    if (!inputPort2.empty()) {
                        inputToGate[inputPort2].push_back(gateInstance);
                    }
                }
            }
            else if (line.find("endmodule") != string::npos) {
                // ����endmodule����ʾģ�鶨�����
                isCombinedLogicModule = false;
                cout << "End of Combined Logic Module Defination" << endl;
            }
        }
    }

    return make_tuple(gates, outputToGate, inputToGate);
}


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



    auto [gates, outputToGate, inputToGate] = parseLogicGates("D:\\Desktop\\testcase.txt");

    

    Circuit circuit(gates, outputToGate, inputToGate);
    circuit.detectCircles();
       
    cout << gates.size() << endl;

    return 0;

}