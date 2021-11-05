#include "aStar.h"
AStar::AStar(string s, string goal) : Fun(s, goal)
{
    this->open.push_back(init);
}
int AStar::h1(string s)
{
    int dif = 0;
    for (int i = 0; i < s.size(); i++)
    {
        if (s[i] != end[i])
            dif++;
    }
    return dif;
}
int AStar::h2(string s)
{
    int dif = 0;
    for (int i = 0; i < s.size(); i++)
    {
        char c = s[i];
        int idx = end.find(c);
        int x1 = i / 3, y1 = i % 3;
        int x2 = idx / 3, y2 = idx % 3;
        dif += abs(x1 - x2) + abs(y1 - y2);
    }
    return dif;
}
int AStar::h3(string s)
{
    int dif = 0;
    for (int i = 0; i < s.size(); i++)
    {
        char c = s[i];
        int idx = end.find(c);
        dif += abs(idx - i);
    }
    return dif;
}
int AStar::algo(int select)
{
    int dx[4] = {-1, 0, 1, 0}, dy[4] = {0, 1, 0, -1};
    // unsigned long long sum = 0;
    // unsigned long long num = 0;
    while (open.size())
    {
        // num++;
        // cout << "num: " << num << endl;
        // sum = max(sum, open.size());
        // cout << sum << endl;
        int grade = 1000000000;
        int j = -1;
        for (int i = 0; i < open.size(); i++)
        {
            int cur = 0;
            if (select == -1)
            {
                cur = h1(open[i]->s);
            }
            else if(select==-2)
            {
                cur = h2(open[i]->s);
            }
            else if(select==-3)
            {
                cur = h3(open[i]->s);
            }
            else if (select == 1)
            {
                cur = d[open[i]->s] + h1(open[i]->s);
            }
            else if (select == 2)
            {
                cur = d[open[i]->s] + h2(open[i]->s);
            }
            else
            {
                cur = d[open[i]->s] + h3(open[i]->s);
            }
            if (cur < grade)
            {
                grade = cur;
                j = i;
            }
        }
        auto t = open[j];
        open.erase(open.begin() + j);
        if (t->s == end)
        {
            this->last=t;
            return d[t->s];
        }
        int k = (t->s).find('*');
        int x = k / 3, y = k % 3;
        for (int i = 0; i < 4; i++)
        {
            int a = x + dx[i], b = y + dy[i];
            if (a >= 0 && a < 3 && b >= 0 && b < 3)
            {
                string s = mySwap(t->s, a * 3 + b, k);
                if (d.find(s) == d.end())
                {
                    node *newNode = new node();
                    newNode->s = s;
                    newNode->father = t;
                    t->son.push_back(newNode);
                    open.push_back(newNode);
                    d[s] = d[t->s] + 1;
                }
            }
        }
    }
    return -1;
}
