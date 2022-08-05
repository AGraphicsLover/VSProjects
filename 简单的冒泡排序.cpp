#include<iostream>
using namespace std;
int a[10] = { 35,89,14,54,87,36,11,74,20,86 };
int main()
{
	int temp = 0;
	bool flag;
	for (int i = 9; i >=0; i--)
	{
		flag = false;
		for (int j = 0; j < i; j++)
		{
			if (a[j] > a[j + 1])
			{
				temp = a[j + 1];
				a[j + 1] = a[j];
				a[j] = temp;
				flag = true;
			}
		}
		if (flag == false)
			break;
	}
	for (int i = 0; i < 10; i++)
		cout << a[i] << "  ";
	cout << endl;
	return 0;
}