#include<iostream>
using namespace std;
int main()
{
	int n, m;
	int** p;
	cin >> n >> m;
	if (n < 1 || n>99 || m < 1 || m>99)
		cout << "WRONG" << endl;
	else
	{
		p = new int* [m];
		for (int i = 0; i < m; i++)
		{
			*p = new int[n];
		}
		for (int i = 0; i < m; i++)
		{
			for (int j = 0; j < n; j++)
			{
				p[i][j] = j + 1;
			}
		}
		int a = 0,b=0,c=0;
		for (int i = 0; i < m; i++)
		{
			for (int j = 0; j < n; j++)
			{
				if (p[i][j] != 0)
					a++;
				else
					b++;
				if (a % m == 0)
				{
					c++;
					int l = a + b;
					if (c == n - 1)
					{
						while (l >= n)
							l -= n;
						cout <<endl<< p[0][l];
					}
					while (l >= n)
						l -= n;
					cout << p[0][l] << " ";
					p[i][l] = 0;
				}
			}
		}
	}
	return 0;
}