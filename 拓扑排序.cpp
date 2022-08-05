#include<iostream>
#include<list>
#include<vector>
#include<algorithm>
using namespace std;
vector<list<int>> vertex_list;
vector<int> have_deleted;
vector<int> topo_order;
void create_graph()
{
	int n, m, v1, v2;
	cin >> n >> m;
	vertex_list.assign(n + 1, list<int>());
	have_deleted.assign(n + 1, 0);
	topo_order.assign(n + 1, 0);
	for (int i = 0; i < m; i++)
	{
		cin >> v1 >> v2;
		vertex_list[v2].push_back(v1);
	}
}
void output_circle()
{
	int rest_size = have_deleted.size();
	vector<int> circle_order;
	int first, before;
	for (int i = 1; i < rest_size; i++)
	{
		if (!vertex_list[i].empty())
		{
			first = i;
			break;
		}
	}
	while (true)
	{
		before = vertex_list[first].front();
		if (find(circle_order.begin(), circle_order.end(), before) != circle_order.end())
			break;
		circle_order.push_back(before);
		first = before;
	}
	auto it = find(circle_order.begin(), circle_order.end(), before);
	cout << before;
	vector<int> temp;
	while (it != circle_order.end())
	{
		temp.push_back((*it));
		it++;
	}
	int temp_size = temp.size();
	for (int i = 0; i < temp_size; i++)
		cout << "," << temp[temp_size - i - 1];
	exit(0);
}
void topological_sort()
{
	int rest_size = have_deleted.size();
	for (int i = 1; i < rest_size; i++)
	{
		for (int j = 1; j < rest_size; j++)
		{
			if (vertex_list[j].empty() && have_deleted[j] != 1)
			{
				topo_order[i] = j;
				have_deleted[j] = 1;
				for (int k = 1; k < rest_size; k++)
				{
					if (k != j)
						vertex_list[k].remove(j);
				}
				break;
			}
			if (j == (rest_size - 1))
			{
				cout << "NO" << endl;
				output_circle();
			}
		}
	}
	cout << "YES" << endl;
	for (int i = 1; i < rest_size - 1; i++)
	{
		cout << topo_order[i] << ",";
	}
	cout << topo_order[rest_size - 1];
}
int main()
{
	create_graph();
	topological_sort();
}