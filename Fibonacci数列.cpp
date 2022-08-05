#include<iostream>
using namespace std;
int main()
{
	const int max = 1000;
	double Fibonacci[max] = { 1,1 };
	int n;
	cin >> n;
	if (n > max||n<1)
		cout << "WRONG" << endl;
	else
	{
		for (int i = 0; i < max - 2; i++)
			Fibonacci[i + 2] = Fibonacci[i] + Fibonacci[i + 1];
		cout << Fibonacci[n-1];
	}
	return 0;
}