#include<iostream>
using namespace std;

int a[10] = { 35, 89, 14, 54, 87, 36, 11, 74, 20, 86 };

int getMax()
{
	int max = a[0];
	for (int i = 1; i < 10; i++)
	{
		if (a[i] > max)
			max = a[i];
	}
	return max;
}

int getDistance()
{
	int max = getMax();
	int digits = 0;
	while (max != 0)
	{
		max /= 10;
		digits++;
	}
	return digits;
}

void radixSort()
{
	int** bucket = new int* [10];
	for (int i = 0; i < 10; i++)
		bucket[i] = new int[10];
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
			bucket[i][j] = 0;
	}
	int distance = getDistance();
	int divider = 1;
	int round = 1;
	while (round <= distance)
	{
		int* count = new int[10];
		for (int i = 0; i < 10; i++)
			count[i] = 0;
		for (int i = 0; i < 10; i++)
		{
			int which = (a[i] / divider) % 10;
			bucket[which][count[which]] = a[i];
			count[which]++;
		}
		int index = 0;
		for (int i = 0; i < 10; i++)
		{
			if (count[i] != 0)
			{
				for (int j = 0; j < count[i]; j++)
				{
					a[index] = bucket[i][j];
					index++;
				}
			}
			count[i] = 0;
		}
		divider *= 10;
		round++;
	}
}

int main()
{
	radixSort();
	for (int i = 0; i < 10; i++)
		cout << a[i] << "  ";
	cout << endl;
	return 0;
}