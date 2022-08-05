#include <iostream>
#include <stack>
#include<limits.h>    //需要使用INT_MAX
#include <queue>
#include<vector>
using namespace std;

struct edge
{
	int u;  //边的起点
	int v;  //边的终点
	int w;  //权值
};

int vertex_num;  //节点数
int edge_num;  //边数
int source;  //源点
vector<edge> edges[1000];  //vector数组，不仅记录了边的信息，数组里的vector里的元素用来记录邻接点
int dis[1000];  //源点到节点i的最短距离
int path[1000];  //记录最短路径经过的节点
bool in_queue[1000];
int in_count[1000];
queue<int> q;

bool BFImproved()  //Bellman_Ford算法改进版
{
	bool flag = true;  //标记是否有负权环
	for (int i = 1; i <= vertex_num; i++)
	{
		if (i == source)
			dis[i] = 0;
		else
			dis[i] = INT_MAX;   //初始化dis[]数组元素大小为int类型所能表示的最大值
		in_queue[i] = false;  //所有节点都不在队列里
		in_count[i] = 0;  //所有节点入队次数为0
	}
	q.push(source);
	in_queue[source] = true;
	in_count[source] = 1;
	while (!q.empty())
	{
		int temp = q.front();
		q.pop();
		in_queue[temp] = false;
		int adjoin_num = edges[temp].size();  //统计temp的邻接点的个数
		for (int i = 0; i < adjoin_num; i++)  //对temp点的每个邻接点进行入队出队操作，相应的，对边进行松弛操作
		{
			edge* edges_adjoin = &edges[temp][i];
			if (dis[(*edges_adjoin).v] > dis[temp] + (*edges_adjoin).w)
			{
				dis[(*edges_adjoin).v] = dis[temp] + (*edges_adjoin).w;
				path[(*edges_adjoin).v] = temp;
				if (!in_queue[(*edges_adjoin).v])
				{
					q.push((*edges_adjoin).v);
					in_queue[(*edges_adjoin).v] = true;
					in_count[(*edges_adjoin).v] ++;
					if (in_count[(*edges_adjoin).v] > vertex_num)  //如果某个点入队次数超过节点数，那么必然存在负权环
					{
						while (!q.empty()) 
						{
							q.pop();  //回收空间
						}
						flag = false;
						break;
					}
				}
			}
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
			while(!s.empty()) {  //从栈中依次弹出的是正序路径
				cout << "-->" << s.top();  
				s.pop();
			}
			cout << "；最短路径长度为：" << dis[i] << endl;
		}
	}
}

int main()
{
	cout << "请依次输入节点数、边数、源点：" << endl;
	cin >> vertex_num >> edge_num >> source;
	cout << "请按顺序输入" << edge_num << "条边的起点、终点、权值：" << endl;
	int u, v, w;
	edge temp;
	for (int i = 0; i < edge_num; i++)
	{
		cin >> u >> v >> w;
		temp.v = v;
		temp.w = w;
		edges[u].push_back(temp);
	}
	if (BFImproved())
		print();
	else
		cout << "图中存在负权环，不能求出最短路径！" << endl;
	return 0;
}