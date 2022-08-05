#include<iostream>
#include<fstream>
#include<string>
using namespace std;
void func(char ch[], int a[], int index, int length)
{
	if (index == length)
	{
		for (int i = 0; i < length; i++)
		{
			if (a[i] == 1)
			{
				if (i == length - 1)
					cout << ch[i];
				else
				{
					cout << ch[i] << " ";
				}
			}
		}
		cout << endl;
	}
	else
	{
		a[index] = 0;
		func(ch, a, index + 1, length);
		a[index] = 1;
		func(ch, a, index + 1, length);
	}
}
int main()
{
	int n=0;
	char* c = new char[26];
	for (int i = 0; i < 26; i++)
		c[i] = i + 'a';
	string s;
	fstream fin("D:\\°Ù¶ÈÍøÅÌÏÂÔØ\\input2.txt");
	getline(fin, s);
	for (int i = 0; s[i]; i++)
	{
		n = n * 10 + s[i] - '0';
	}
	int* a = new int[n];
	func(c, a, 0, n);
	return 0;
}