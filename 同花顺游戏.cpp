#include<iostream>
#include<vector>
#include<list>
using namespace std;
class poker
{
	int num;
	int color;
public:
	poker() {};
	poker(int n, int c) :num(n), color(c) {}
	int get_num() { return num; }
	int get_col() { return color; }
};
class player
{
	poker p[5];
public:
	player(poker p1[5])
	{
		for (int i = 0; i < 5; i++)
		{
			p[i] = p1[i];
		}
	}
	bool judge()
	{
		vector<int> v;
		list<int> l;
		int j = 0;
		list<int>::iterator it1= l.begin();
		list<int>::iterator it2 = l.begin();
		for (int i = 0; i < 5; i++)
		{
			l.push_back(p[i].get_num());
			v.push_back(p[i].get_col());
		}
		l.sort();
		for (int i = 0; i < 5; i++)
		{
			if (v[0] != v[i])
				return false;
			else
				j++;
		}
		while (it1 != l.end())
		{
			it2++;
			if (*it1 != *it2-1)
				return false;
			else
			{
				it1++;
				continue;
			}
		}
		if (j == 5 && it1 == l.end())
			return true;
	}
};
int main()
{
	poker p[5] = { poker(10,1),poker(9,1),poker(8,1),poker(11,1),poker(12,2) };
	player p1(p);
	cout << p1.judge();
	return 0;
}