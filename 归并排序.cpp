#include<iostream>
using namespace std;

int a[10] = { 35, 89, 14, 54, 87, 36, 11, 74, 20, 86 };

void mergeSortArray(int a1[], int a2[], int left, int middle, int right)
{
	int i = left;
	int j = middle + 1;
	int k = 0;
	while (i <= middle && j <= right)
		a2[k++] = a1[i] <= a1[j] ? a1[i++] : a1[j++];
	while (i <= middle)
		a2[k++] = a1[i++];
	while (j <= right)
		a2[k++] = a1[j++];
	for (i = 0; i < k; i++)
		a1[left + i] = a2[i];
}

void coreMergeSort(int a1[], int a2[], int left, int right)
{
	if (left < right)
	{
		int middle = (left + right) / 2;
		coreMergeSort(a1, a2, left, middle);
		coreMergeSort(a1, a2, middle + 1, right);
		mergeSortArray(a1, a2, left, middle, right);
	}
}

int main()
{
	int* temp = new int[10];
	for (int i = 0; i < 10; i++)
		temp[i] = 0;
	coreMergeSort(a, temp, 0, 9);
	for (int i = 0; i < 10; i++)
		cout << a[i] << "  ";
	cout << endl;
	return 0;
}