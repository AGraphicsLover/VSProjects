#include<iostream>
#include<WinSock2.h>
#pragma comment(lib, "ws2_32.lib")
#include<Windows.h>
using namespace std;

SOCKET clientSocket;
bool connection(const char* serverIP, int serverPort);
UINT recvMsg(LPVOID lpvoid);
void sendMsg(char* msg, int client_n);
char* int_to_char(int a);

int main()
{
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (HIBYTE(wsaData.wVersion) != 2 || LOBYTE(wsaData.wVersion) != 2)
	{
		cout << "确定协议版本失败：" << GetLastError() << endl;
		return 0;
	}
	cout << "确定协议版本成功！" << endl;

	if (connection("10.139.213.68", 7611) == 0)
	{
		cout << "连接服务器失败！" << endl;
		return -1;
	}
	cout << "连接服务器成功！" << endl;
	char msgBuff[1024] = { 0 };
	int client_n = 0;
	while (1)
	{
		cin >> msgBuff >> client_n;
		sendMsg(msgBuff, client_n);
	}
	closesocket(clientSocket);
	WSACleanup();
	return 0;
}
bool connection(const char* serverIP, int serverPort)
{
	clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (clientSocket == SOCKET_ERROR)
	{
		cout << "创建socket失败：" << GetLastError() << endl;
		WSACleanup();
		return 0;
	}

	SOCKADDR_IN clientAddr = { 0 };
	clientAddr.sin_family = AF_INET;
	clientAddr.sin_addr.S_un.S_addr = inet_addr(serverIP);   //IP地址
	clientAddr.sin_port = htons(serverPort);   //端口

	if (connect(clientSocket, (sockaddr*)&clientAddr, sizeof(clientAddr)) != 0)
	{
		return 0;
	}

	CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)recvMsg, NULL, NULL, NULL);
	return 1;
}

UINT recvMsg(LPVOID lpvoid)
{
	char msgBuff[1024] = { 0 };
	while (1)
	{
		if (recv(clientSocket, msgBuff, 1024, 0) <= 0)  //获得服务器发送的字符串
		{
			cout << "服务器已退出聊天" << endl;
			break;
		}
		int i = 0;
		int j = 0;  //记录第一个'\n'所在的下标
		int k = 0;  //记录第二个'\n'所在的下标
		char a[1024] = { 0 };  //存储服务器发送的字符串的时间
		char b[1024] = { 0 };  //存储服务器发送的字符串的消息内容
		while (msgBuff[i] != '\0')
		{
			if (msgBuff[i] != '\n')
			{
				i++;
			}
			else
			{
				if (j == 0)
				{
					j = i;
					i++;
				}
				else
				{
					k = i;
					i++;
					break;
				}
			}
		}
		for (int x = 0; x < j; x++)
		{
			a[x] = msgBuff[x];
		}
		a[j] = '\0';
		cout << "时间：" << a << endl;  //输出时间
		for (int x = 0; x < k - j - 1; x++)
		{
			b[x] = msgBuff[x + j + 1];
		}
		b[k - j - 1] = '\0';
		cout << "客户端";
		while (msgBuff[i] != '\0')
		{
			cout << msgBuff[i];  //输出客户端ID
			i++;
		}
		cout << "：" << b << endl;  //输出消息
		cout << endl;
	}
	return 0;
}

void sendMsg(char* msg, int client_n)
{
	struct tm* now_time;
	time_t now;
	now = time(NULL);
	now_time = gmtime(&now);
	char* timebuff = new char[1024];
	timebuff = ctime(&now);
	msg = strcat(timebuff, msg);
	strcat(msg, "\n");
	strcat(msg, int_to_char(client_n));
	send(clientSocket, msg, 1024, 0);
	int x = 0;
	int flag = 0;
	cout << "时间：";
	while (msg[x] != '\0')
	{
		if (msg[x] != '\n')
		{
			cout << msg[x];
			x++;
		}
		else
		{
			if (flag == 0)
			{
				cout << endl;
				x = x + 1;
				cout << "我：";
			}
			if (flag == 1)
				break;
			flag++;
		}
	}
	cout << endl << endl;
}
char* int_to_char(int a)
{
	char* b;
	b = new char[10];
	sprintf(b, "%d", a);
	return b;
}