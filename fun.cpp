#include "fun.h"
Fun::Fun(string s, string goal)
{
    this->state = s;
    this->end = goal;
    this->init = new node();
    this->init->father = nullptr;
    this->init->s = state;
    this->d[state] = 0;
    this->last=nullptr;
}
string Fun::mySwap(string s, int a, int b)
{
    swap(s[a], s[b]);
    return s;
}
void Fun::printRoad()
{
    node *tem = last;
//    ofstream ofs;
//    ofs.open("./doc/road.txt");
    while (tem != nullptr)
    {
//        ofs << tem->s << endl;
        cout << tem->s << " ";
        tem = tem->father;
    }
    cout<<endl;
}
void Fun::printTree()
{
//    ofstream ofs;
//    ofs.open("./doc/tree.txt");
    queue<node *> q;
//    ofs << init->s << endl;
    cout << init->s << endl;
    q.push(init);
    while (q.size())
    {
        int n = q.size();
//        ofs << n << endl;
        cout<<n<<endl;
        while (n--)
        {
            auto x = q.front();
            q.pop();
            // if (x->son.size() == 0)
            //     continue;
            for (int i = 0; i < x->son.size(); i++)
            {
                auto y = x->son[i];
//                ofs << y->s << " ";
                cout<<y->s<<" ";
                if (y->s == "12345678*")
                    return;
                q.push(y);
            }
//            ofs << "\t||||||\t";
            cout << "\t||||||\t";
        }
//        ofs << endl;
        cout<<endl;
    }
}
void Fun::freeMemory()
{
    node * tem=this->init;
    while(tem!=nullptr)
    {
        if(tem->son.empty())
        {
            node * a=tem;
            tem=tem->father;
            delete a;
            continue;
        }
        node * a=tem->son[0];
        tem->son.erase(tem->son.begin());
        tem=a;
    }
    this->init=nullptr;
    this->last=nullptr;
}
