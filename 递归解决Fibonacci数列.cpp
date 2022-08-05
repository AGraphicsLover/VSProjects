#include<iostream>
#include<fstream>
#include<string>
using namespace std;
long long int fibonacci(int n, long long int a[]);
int main()
{
	int n=0;
	string s;
	fstream fin("D:\\°Ù¶ÈÍøÅÌÏÂÔØ\\input1.txt");
	getline(fin, s);
	for (int i = 0; s[i]; i++)
	{
		n = n * 10 + s[i] - '0';
	}
	if (n <= 0)
	{
		cout << "WRONG" << endl;
		return 0;
	}
	long long int* a = new long long int[n];
	for (int i = 0; i < n; i++)
		a[i] = 0;
	long long int result = fibonacci(n, a);
	cout << result << endl;
	return 0;
}
long long int fibonacci(int n, long long int a[])
{
	if (a[n - 1] != 0)
		return a[n - 1];
	else
	{
		try 
		{
			if (n == 1 || n == 2)
			{
				a[n - 1] = 1;
				return 1;

			}
			if (n > 2)
			{
				a[n - 1] = fibonacci(n - 1, a) + fibonacci(n - 2, a);
				return a[n - 1];
			}
			else
				throw 3;
		}
		catch (int)
		{
			cout << "WRONG" << endl;
			exit(0);
		}
	}
}