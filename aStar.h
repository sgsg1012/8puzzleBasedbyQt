#include "node.h"
#include "fun.h"

/*  
    优化a*算法 因为每条路的代价相同皆为1，所以不会出现open表和closed表中已存在的节点
    被更新，所以可以把open表和closed表的信息用一个map来存储，在map中则删除拓展节点，不在就把节点加到open表和map中

    从而大大提升了效率
    并且把原有的排序操作变成了遍历取最小值操作，加快速度
*/

class AStar : public Fun
{
public:
    vector<node *> open;
    AStar(string s, string goal);
    int algo(int select);
    //启发式函数
    int h1(string s); //位置错误的点的个数 但是值太小效果不好，非常慢
    int h2(string s); //位置错误的点的曼哈顿距离之和
    //注意：h3函数是个错误的启发式函数，应为它并不<=h*()  所以并不能保证最优解，但是速度却非常快
    int h3(string s); //把九宫格展开成一个向量后，位置错误的点的距离之和
};