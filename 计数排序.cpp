#include<iostream>
using namespace std;

int a[10] = { 35, 89, 14, 54, 87, 36, 11, 74, 20, 86 };

void countSort(int a[], int max, int min)
{
	int* b = new int[10];
	int* count = new int[max - min +1];
	for (int num = min; num <= max; num++)
		count[num - min] = 0;
	for (int i = 0; i < 10; i++)
		count[a[i] - min]++;
	for (int i = min + 1; i <= max; i++)
		count[i - min] += count[i - min - 1];
	for (int i = 0; i < 10; i++)
	{
		int index = count[a[i] - min] - 1;
		b[index] = a[i];
		count[a[i] - min]--;
	}
	for (int i = 0; i < 10; i++)
		a[i] = b[i];
}

int main()
{
	countSort(a, 89, 11);
	for (int i = 0; i < 10; i++)
		cout << a[i] << "  ";
	cout << endl;
	return 0;
}