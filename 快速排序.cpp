#include<iostream>
using namespace std;
int a[] = { 35, 89, 14, 54, 87, 36, 11, 74, 20, 86 };

int partition(int a[], int low, int high)
{
	int p = a[low];
	while (low < high)
	{
		while (low < high && a[high] >= p)
			high--;
		a[low] = a[high];
		while (low < high && a[low] <= p)
			low++;
		a[high] = a[low];
	}
	a[low] = p;
	return low;
}

void quickSort(int a[], int low, int high)
{
	if (low >= high)
		return;
	int p = partition(a, low, high);
	quickSort(a, low, p - 1);
	quickSort(a, p + 1, high);
}

int main()
{
	quickSort(a, 0, 9);
	for (int i = 0; i < 9; i++)
		cout << a[i] << "  ";
	cout << endl;
	return 0;
}