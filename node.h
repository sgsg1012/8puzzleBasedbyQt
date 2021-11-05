#pragma once
#include <iostream>
#include <vector>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <queue>
#include <cstring>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <QTreeWidgetItem>
using namespace std;
class node
{
public:
    string s;
    vector<node *> son;
    node *father;
};

