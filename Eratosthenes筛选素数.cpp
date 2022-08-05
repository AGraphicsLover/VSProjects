#include<iostream>
using namespace std;
void Eratosthenes (int n)  //Eratosthenes筛选法
{
	int num = 0;
	bool* is_prime = new bool[n + 1];
	for (int i = 0; i < n + 1; i++)
		is_prime[i] = true;
	for (int i = 2; i < n + 1; i++)
	{
		if (is_prime[i] == true)
		{
			for (int j = 2 * i; j < n + 1; j += i)
				is_prime[j] = false;
		}
		else
			continue;
	}
	for (int i = 2; i < n + 1; i++)
	{
		if (is_prime[i] == true)
		{
			cout << i << " ";
			num++;
			if (num % 10 == 0)
				cout << endl;
		}
	}
	cout << endl;
}
int main()
{
	Eratosthenes(500);
	cout << "-------------------------" << endl;
	Eratosthenes(1000000);  //直接利用Eratosthenes筛选法
	return 0;
}