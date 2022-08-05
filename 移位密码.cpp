#include<iostream>
#include<Windows.h>
using namespace std;
char alphabet1[27] = "abcdefghijklmnopqrstuvwxyz";
char alphabet2[27] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
class SingleTableReplaceAlgo
{
public:
	SingleTableReplaceAlgo() {};
	static void encryption(char* str, int n);
	static void decryption(char* str, int n);
	static void attack(char* str);
};
void SingleTableReplaceAlgo::attack(char* str)
{
	for (int j = 0; j < 26; j++)
	{
		int i = 0;
		while (str[i] != '\0')
		{
			if (str[i] == ' ')
			{
				cout << str[i];
				i++;
				continue;
			}
			if (str[i] <= 'Z' && str[i] >= 'A')
			{
				cout << alphabet2[(int(str[i]) - 65 + j) % 26];
				i++;
				continue;
			}
			cout << alphabet1[(int(str[i]) - 97 + j) % 26];
			i++;
		}
		cout << "    移位大小为" << (26 - j) % 26 << endl;
	}
}
void SingleTableReplaceAlgo::encryption(char* str, int n)
{
	int i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == ' ')
		{
			cout << str[i];
			i++;
			continue;
		}
		if (str[i] <= 'Z' && str[i] >= 'A')
		{
			cout << alphabet2[(int(str[i]) - 65 + n) % 26];
			i++;
			continue;
		}
		cout << alphabet1[(int(str[i]) - 97 + n)%26];
		i++;
	}
	cout << endl;
}
void SingleTableReplaceAlgo::decryption(char* str, int n)
{
	int i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == ' ')
		{
			cout << str[i];
			i++;
			continue;
		}
		if (str[i] <= 'Z' && str[i] >= 'A')
		{
			cout << alphabet2[(int(str[i]) - 65 - n + 26) % 26];
			i++;
			continue;
		}
		cout << alphabet1[(int(str[i]) - 97 - n + 26) % 26];
		i++;
	}
	cout << endl;
}
int main()
{
	int a;
	char* s1 = new char[1000];
	char* s2 = new char[1000];
	char* s3 = new char[1000];
	cout << "请输入你要加密的内容：";
	cin.getline(s1, 1000);
	cout << "请输入移位大小：";
	cin >> a;
	cout << "加密结果为：";
	SingleTableReplaceAlgo::encryption(s1, a);
	cin.ignore();
	cout << "请输入你要解密的内容：";
	cin.getline(s2, 1000);
	cout << "解密结果为：";
	SingleTableReplaceAlgo::decryption(s2, a);
	cout << "请输入你想暴力解密的内容：";
	cin.getline(s3, 1000);
	SingleTableReplaceAlgo::attack(s3);
	Sleep(10000);
	return 0;
}