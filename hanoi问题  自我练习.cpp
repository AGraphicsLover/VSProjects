#include<iostream>
using namespace std;
int s = 0;
void move(char A, char C)
{
	cout << A<<"=>"<<C << endl;
}
void hanoi(int n, char A, char B, char C)
{
	if (n == 1)
		move(A, C);
	else
	{
		hanoi(n - 1, A, C, B);
		move(A, C);
		s++;
		hanoi(n - 1, B, A, C);
	}
}
int main()
{
	int n;
	cout << "请输入你想移动的圆盘数(n>0)：" << endl;
	cin >> n;
	cout << "移动的步骤如下：" << endl;
	hanoi(n, 'A', 'B', 'C');
	cout << "移动的总步数：" << s << endl;
	return 0;
}