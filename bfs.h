#pragma once
#include "node.h"
#include "fun.h"

class BFS : public Fun
{
public:
    queue<node *> q;            //队列
    int algo();                 //算法
    BFS(string s, string goal); //构造函数，初始化
};