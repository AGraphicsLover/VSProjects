#include<iostream>
using namespace std;
int main()
{
	int* p, m;
	cout << "请输入你想输入的数的个数:" << endl;
	cin >> m;
	p = new int[m];
	for (int i = 0; i < m; i++)
		cin >> p[i];
	for (int j = 1; j < m; j++)
	{
		int key = p[j];
		int i = j - 1;
		while (i >= 0 && p[i] < key)
		{
			p[i + 1] = p[i];
			i = i - 1;
		}
		p[i + 1] = key;
	}
	for (int i = 1; i <= m; i++)
	{
		cout << p[i - 1] << " ";
	}
	return 0;
}