#include<iostream>
using namespace std;
int a[10] = { 35, 89, 14, 54, 87, 36, 11, 74, 20, 86 };

int main()
{
	for (int i = 1; i < 10; i++)
	{
		int value = a[i];
		int position = i;
		while (position > 0 && a[position-1] > value)
		{
			a[position] = a[position - 1];
			position--;
		}
		a[position] = value;
	}
	for (int i = 0; i < 10; i++)
		cout << a[i] << "  ";
	cout << endl;
	return 0;
}