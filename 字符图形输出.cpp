#include<iostream>
using namespace std;
int main()
{
	char alphabet;
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < i; j++)
			cout << " ";
		alphabet = 'A';
		int m = 4-i;
		for (int k = 0; k < 5 - i; k++)
		{
			cout << char(alphabet+m);
			m--;
		}
		for (int j = 1; j < 5 - i; j++)
		{
			cout << char(alphabet + j);
		}
		cout << endl;
	}
	for (int i = 1; i < 5; i++)
	{
		for (int j = 0; j <4-i; j++)
			cout << " ";
		alphabet = 'A';
		for (int k = 0;k<i+1;k++)
		{
			cout << char(alphabet + i-k);
		}
		for (int j = 1; j < i+1; j++)
		{
			cout << char(alphabet+j) ;
		}
		cout << endl;
	}
	return 0;
}