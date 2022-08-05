#include<iostream>
using namespace std;
int main()
{
	int n;
	cin >> n;
	int* man = new int[n];
	int* woman = new int[n];
	for (int i = 0; i < n; i++)
	{
		man[i] = 0;
		woman[i] = 0;
	}
	int** manlist;
	int** womanlist;
	int* temp = new int[n];
	manlist = new int* [n];
	womanlist = new int* [n];
	for (int i = 0; i < n; i++)
		manlist[i] = new int[n];
	for (int i = 0; i < n; i++)
		womanlist[i] = new int[n];
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
			cin >> manlist[i][j];
	}
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
			cin >> womanlist[i][j];
	}
	for (int i = 0; i < n; i++)
	{
		for (int k = 0; k < n; k++)
			temp[k] = womanlist[i][k];
		for (int j = 0; j < n; j++)
		{
			for (int l = 0; l < n; l++)
			{
				if (temp[l] == j + 1)
				{
					womanlist[i][j] = l + 1;
					break;
				}
			}
		}
	}
	for (int i = 0; i < n; i++)
	{
		if (man[i] != 0)
			continue;
		for (int j = 0; j < n; j++)
		{
			if (woman[manlist[i][j] - 1] == 0)
			{
				woman[manlist[i][j] - 1] = i + 1;
				man[i] = manlist[i][j];
				break;
			}
			else
			{
				if (womanlist[manlist[i][j] - 1][i] < womanlist[manlist[i][j] - 1][woman[manlist[i][j] - 1] - 1])
				{
					int before = woman[manlist[i][j] - 1];
					woman[manlist[i][j] - 1] = i + 1;
					man[i] = manlist[i][j];
					man[before - 1] = 0;
					i = before - 2;
					break;
				}
				else
				{
					continue;
				}
			}
		}
	}
	for (int i = 0; i < n; i++)
		cout << man[i] << " ";
	cout << endl;
	return 0;
}