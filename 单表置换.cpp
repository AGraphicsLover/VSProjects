#include<iostream>
#include<fstream>
#include<string>
#include<iomanip>
#include<Windows.h>
using namespace std;
string alphabet1 = "abcdefghijklmnopqrstuvwxyz";  //小写字母表
string alphabet2 = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";  //大写字母表
class SingleTableReplaceAlgo
{
public:
	SingleTableReplaceAlgo() {};
	static void buildTable(char* str);  //根据密钥建立字母表
	static void encryption(char* str);  //加密
	static void decryption(char* str);  //解密
	static void attack(ifstream& fin);  //获得每个字母占字母总数的百分比
};
void SingleTableReplaceAlgo::attack(ifstream& fin)
{
	char next;
	int totalNum = 0;  //字母总数
	int a[26];  //存储每个字母个数的int数组
	for (int i = 0; i < 26; i++)
	{
		a[i] = 0;
	}
	while (fin.get(next))
	{
		if (next == ' ')  //忽略空格
		{
		}
		else
		{
			totalNum++;  //如果不是空格，字母总数自增1
			a[int(next) - 65]++;  //对应字母个数自增1
		}
	}
	cout << "总字母数为：" << totalNum << endl;
	for (int i = 0; i < 26; i++)
	{
		cout << char(i + 65) << "：" << fixed << setprecision(3) << double(double(a[i]) * 100 / double(totalNum)) << "%    ";  //输出每个字母占字母总数的百分比
	}
	cout << endl;
}
void SingleTableReplaceAlgo::buildTable(char* str)
{
	string temp;
	int i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == ' ')  //忽略空格
		{
			i++;
			continue;
		}
		int j = 0;
		while (j < temp.length())
		{
			if (temp[j] == str[i])
			{
				break;
			}
			j++;
		}
		if (j==temp.length())
		{
			temp.push_back(str[i]);  //如果temp字符串中不存在该字母，则把该字母加入temp字符串
		}
		i++;
	}
	for (int l = 0; l < 26; l++)
	{
		int j = 0;
		while (j < temp.length())
		{
			if (temp[j] == alphabet2[l] || temp[j] == char(int(alphabet2[l]) + 32))
			{
				break;
			}
			j++;
		}
		if (j == temp.length())
		{
			temp.push_back(alphabet2[l]);  //把字母表中未在密钥中出现的字母逐个依次加入temp字符串，最后temp中存储的即为字母表
		}
	}
	for (int l = 0; l < temp.length(); l++)
	{
		if (temp[l] <= 'Z' && temp[l] >= 'A')
		{
			alphabet2[l] = temp[l];  //alphabet2存储的为大写字母表
		}
		else
		{
			alphabet2[l] = char(int(temp[l]) - 32);
		}
	}
	for (int l = 0; l < 26; l++)
	{
		alphabet1[l] = char(int(alphabet2[l]) + 32);  //alphabet1存储的为小写字母表
	}
}
void SingleTableReplaceAlgo::encryption(char* str)
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
			cout << alphabet2[int(str[i]) - 65];  //利用ascii码进行int与char类型的转换并查询大写字母表
			i++;
			continue;
		}
		cout << alphabet1[int(str[i]) - 97];  //利用ascii码进行int与char类型的转换并查询小写字母表
		i++;
	}
	cout << endl;
}
void SingleTableReplaceAlgo::decryption(char* str)
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
			for (int j = 0; j < 26; j++)
			{
				if (str[i] == alphabet2[j])
				{
					cout << char(j + 65);
					i++;
					break;
				}
			}
		}
		for (int j = 0; j < 26; j++)
		{
			if (str[i] == alphabet1[j])
			{
				cout << char(j + 97);
				i++;
				break;
			}
		}
	}
	cout << endl;
}
int main()
{
	char* s0 = new char[1000];
	char* s1 = new char[1000];
	char* s2 = new char[1000];
	char* s3 = new char[1000];
	cout << "请输入密钥：";
	cin.getline(s0, 1000);
	SingleTableReplaceAlgo::buildTable(s0);
	cout << "请输入你要加密的内容：";
	cin.getline(s1, 1000);
	cout << "加密结果为：";
	SingleTableReplaceAlgo::encryption(s1);
	cout << "请输入你要解密的内容：";
	cin.getline(s2, 1000);
	cout << "解密结果为：";
	SingleTableReplaceAlgo::decryption(s2);
	cout << "请输入密文便于统计字母占比：";

	ifstream fin;
	fin.open("G:\\关于我的\\密码学\\实验一\\数据.txt");
	while (fin.fail())
	{
		cout << "文件打开错误！" << endl;
		exit(1);
	}
	SingleTableReplaceAlgo::attack(fin);
	fin.close();
	Sleep(10000);
	return 0;
}