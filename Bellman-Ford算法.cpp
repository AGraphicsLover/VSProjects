#include <iostream>
#include <stack>
#include<limits.h>   //需要使用INT_MAX
using namespace std;

struct edge
{
    int u;  //边的起点
    int v;  //边的终点
    int w;  //权值
};

int  vertex_num;  //节点数
int  edge_num;    //边数
int  source;      //源点
edge edges[10000];  //记录所有边，暂将数组大小声明为10000
int  dis[10000];  //源点到节点i的最短距离
int  path[10000];   //记录最短路径经过的节点

bool Bellman_Ford()
{
    bool flag = true;  //标记是否有负权环
    for (int i = 1; i <= vertex_num; i++)  //初始化dis[]数组元素大小为int类型所能表示的最大值
    {
        if (i == source)
            dis[i] = 0;
        else
            dis[i] = INT_MAX;
    }
    for (int i = 1; i < vertex_num; i++)    //n-1次循环求最短路径
    {
        for (int j = 0; j < edge_num; j++)
        {
            if (dis[edges[j].v] > dis[edges[j].u] + edges[j].w)
            {
                dis[edges[j].v] = dis[edges[j].u] + edges[j].w;
                path[edges[j].v] = edges[j].u;
            }
        }
    }
    for (int i = 0; i < edge_num; i++)  //第n次循环判断是否存在负权环
    {
        if (dis[edges[i].v] > dis[edges[i].u] + edges[i].w)
        {
            flag = false;
            break;
        }
    }
    return flag;
}

void print()
{
    for (int i = 1; i <= vertex_num; i++)
    {
        if (i != source)
        {
            int temp = i;
            stack<int> s;
            cout << "节点" << source << "到节点" << temp << "的最短路径为：";
            while (source != temp)  //路径顺序是逆向存储的，所以可以使用栈
            {
                s.push(temp);
                temp = path[temp];
            }
            cout << source;
            while (!s.empty())  //从栈中依次弹出的是正序路径
            {
                cout << "-->" << s.top();
                s.pop();
            }
            cout << "；最短路径长度为：" << dis[i] << endl;
        }
    }
}

int main()
{
    cout << "请依次输入节点数、边数、源点："<<endl;
    cin >> vertex_num >> edge_num >> source;
    cout << "请按顺序输入" << edge_num << "条边的起点、终点、权值："<<endl;
    for (int i = 0; i < edge_num; i++)
        cin >> edges[i].u >> edges[i].v >> edges[i].w;
    if (Bellman_Ford())
        print();
    else
        cout << "图中存在负权环，不能求出最短路径！" << endl;
    return 0;
}