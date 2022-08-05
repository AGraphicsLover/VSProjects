#include<iostream>
using namespace std;

int a[10] = { 35, 89, 14, 54, 87, 36, 11, 74, 20, 86 };

void shellSort()
{
	int delta = 1;
	while (delta < 10 / 3)
		delta = delta * 3 + 1;
	int temp = 0;
	for (; delta >= 1; delta /= 3)
	{
		for (int i = delta; i < 10; i++)
		{
			for (int j = i; j >= delta && a[j] < a[j - delta]; j -= delta)
			{
				temp = a[j];
				a[j] = a[j - delta];
				a[j - delta] = temp;
			}
		}
	}
}

int main()
{
	shellSort();
	for (int i = 0; i < 10; i++)
		cout << a[i] << "  ";
	cout << endl;
	return 0;
}