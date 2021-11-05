#include "bfs.h"
int BFS::algo()
{
    int dx[4] = {-1, 0, 1, 0}, dy[4] = {0, 1, 0, -1}; //拓展的四个方向
    // unsigned long long sum = 0;
    // unsigned long long num = 0;
    while (q.size())
    {
        // num++;
        // cout << "num: " << num << endl;
        // sum = max(sum, q.size());
        // cout << sum << endl;
        auto t = q.front();
        q.pop();

        if (t->s == end)
        {
            this->last=t;
            return d[t->s];
        }

        int distance = d[t->s];
        int k = (t->s).find('*');
        int x = k / 3, y = k % 3;
        for (int i = 0; i < 4; i++)
        {
            int a = x + dx[i], b = y + dy[i];
            if (a >= 0 && a < 3 && b >= 0 && b < 3)
            {
                string s = this->mySwap(t->s, a * 3 + b, k);
                if (!d.count(s))
                {
                    node *newNode = new node();
                    newNode->s = s;
                    newNode->father = t;
                    t->son.push_back(newNode);
                    q.push(newNode);
                    d[s] = distance + 1;
                }
            }
        }
    }

    return -1;
}
BFS::BFS(string s, string goal) : Fun(s, goal)
{
    this->q.push(init);
}
