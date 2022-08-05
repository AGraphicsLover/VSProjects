#include<iostream>
using namespace std;
void move(char A, char C)
{
	cout << A << "==>" << C << endl;
}
void H(unsigned n,char A,char B,char C)
{
	if (n == 1)
	{
		move(A, C);
	}
	else
	{
		H(n - 1, A, C, B);
		move(A, C);
		H(n - 1, B, A, C);
	}
}
int main()
{
	unsigned n;
	cout << "你想移动的盘子数：" << endl;
	cin >> n;
	cout << "The steps are as followed." << endl;
	H(n,'A','B','C');
	return 0;
}