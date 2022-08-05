#include<iostream>
using namespace std;
int a[10] = { 35, 89, 14, 54, 87, 36, 11, 74, 20, 86 };

int main()
{
	int temp, min = 0;
	for (int i = 0; i < 9; i++)
	{
		min = i;
		for (int j = i + 1; j < 10; j++)
		{
			if (a[min] > a[j])
				min = j;
		}
		if (min != i)
		{
			temp = a[min];
			a[min] = a[i];
			a[i] = temp;
		}
	}
	for (int i = 0; i < 10; i++)
		cout << a[i] << "  ";
	cout << endl;
	return 0;
}