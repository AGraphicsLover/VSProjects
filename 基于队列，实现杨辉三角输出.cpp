#include<iostream>
#include<iomanip>
#include<queue>
using namespace std;
void Yanghui(int n);
int main()
{
	Yanghui(10);
	return 0;
}
void Yanghui(int n)
{
	queue<int>q;
	q.push(1);
	int s = 0;
	for (int i = 0; i <= n; i++)
	{
		cout << endl;
		cout << setw((n - i) * 2) << " ";
		q.push(0);
		for (int j = 1; j <= i + 2; j++)
		{
			int t = q.front();
			q.pop();
			q.push(s + t);
			s = t;
			if (j != i + 2)
				cout << setw(4) << s;
		}
	}
}