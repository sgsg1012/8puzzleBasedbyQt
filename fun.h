#pragma once
#include "node.h"
using namespace std;
class Fun
{
public:
    string end;
    node *init;//根节点
    node *last;//终止节点
    string state;                 //初始状态
    unordered_map<string, int> d; //map表示已经拓展到的点，不管有没有访问，值代表代价
    void printRoad();
    void printTree();
    string mySwap(string s, int a, int b);
    Fun(string s, string goal);
    void freeMemory();
};
