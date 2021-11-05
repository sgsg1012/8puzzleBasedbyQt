#include "dfs.h"
DFS::DFS(string s, string goal) : Fun(s, goal)
{
}
int DFS::algo()
{
    int dx[4] = {-1, 0, 1, 0}, dy[4] = {0, 1, 0, -1};
    node *tem = this->init;
    unsigned long long num=0;
    unsigned long long depth=0;
    while (tem != nullptr)
    {
        if (tem->s == end)
        {
            this->last=tem;
            return depth;
        }
        int k = (tem->s).find('*');
        int x = k / 3, y = k % 3;
        int i = 0;
        for (i = 0; i < 4; i++)
        {
            int a = x + dx[i], b = y + dy[i];
            if (a >= 0 && a < 3 && b >= 0 && b < 3)
            {
                string s = mySwap(tem->s, a * 3 + b, k);
                if (!d.count(s))
                {
                    d[s] = 0;
                    node *newNode = new node();
                    newNode->s = s;
                    newNode->father = tem;
                    tem->son.push_back(newNode);
                    tem = newNode;
                    num++;
                    depth=max(depth,num);
                    break;
                }
            }
        }
        if (i >= 4)
        {
            tem = tem->father;
            num--;
        }
    }
    return -1;
}
