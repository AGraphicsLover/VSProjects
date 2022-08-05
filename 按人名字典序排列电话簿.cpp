#include<iostream>
#include<iomanip>
using namespace std;
void swap(char* &, char* &);
int compword(char*, char*);
void main(void)
{
	const int n = 5, t = 8;
	int i, j, index;
	char *tele[n], *sele;
	char* name[n] = { (char*)"Chenziying",(char*)"Wanglinhua",(char*)"Yixinchen",(char*)"Yixinhua",(char*)"Nianlan" };
	for (i = 0; i < n; i++)
	{
		cout << "Input" << name[i] << "\'s telephone number:";
		tele[i] = new(char[t]);
		cin >> tele[i];
	}
	cout << setw(15) << "NAME" << setw(15) << "TELE NO";
	for (i = 0; i < n - 1; i++)
	{
		sele = name[i];
		index = i;
		for (j = i + 1; j < n; j++)
		{
			if (compword(name[j], sele))
			{
				sele = name[j];
				index = j;
			}
		}
		swap(name[index], name[i]);
		swap(tele[index], tele[i]);
	}
	for (i = 0; i < n; i++)
	{
		cout << endl << "    " << setw(14);
		cout << setiosflags(ios::left);
		cout << name[i] << tele[i];
	}
}
void swap(char*& a, char*& b)
{
	char* temp;
	temp = a;
	a = b;
	b = temp;
}
int compword(char* a, char* b)
{
	while (*a != '\0' && *b != '\0')
		if (*a != *b)
			return (*a < *b);
		else	
		{
			a++; b++;
		}
	return (*a == '\0');
}