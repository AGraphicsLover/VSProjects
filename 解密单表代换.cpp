#include<iostream>
#include<fstream>
#include<Windows.h>
using namespace std;
char alphabet1[27] = "NHGDCFEIJKLAQBMXUPRSZTVWYO";
class SingleTableReplaceAlgo
{
public:
	SingleTableReplaceAlgo() {};
	static void attack(ifstream& fin);
};
void SingleTableReplaceAlgo::attack(ifstream& fin)
{
	char next;
	while (fin.get(next))
	{
		if (next == ' ')  //忽略空格
		{
			cout << " ";
			continue;
		}
		else
		{
			for (int j = 0; j < 26; j++)
			{
				if (next == alphabet1[j])
				{
					cout << char(j + 97);
					break;
				}
			}
		}
	}
	cout << endl;
}
int main()
{
	ifstream fin;
	fin.open("G:\\关于我的\\密码学\\实验一\\数据.txt");
	while (fin.fail())
	{
		cout << "文件打开错误！" << endl;
		exit(1);
	}
	cout << "解密得到的明文为：";
	SingleTableReplaceAlgo::attack(fin);
	fin.close();
	Sleep(10000);
	return 0;
}