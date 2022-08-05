#include<iostream>
#include<WinSock2.h>
#pragma comment(lib, "ws2_32.lib")
#include<Windows.h>
using namespace std;

SOCKET clientSocket;
bool connection(const char* serverIP, int serverPort);
UINT recvMsg(LPVOID lpvoid);
void sendMsg(char* msg);

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
	while (1)
	{
		cin >> msgBuff;
		sendMsg(msgBuff);
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

	if (connect(clientSocket, (sockaddr*)&clientAddr, sizeof(clientAddr)) != 0)  //与服务器代码不同，客户端利用connect()函数连接到服务器
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
		if (recv(clientSocket, msgBuff, 1024, 0) <= 0)  //根据recv()函数接收到的字符串消息特征来进行输出
		{
			cout << "服务器已退出聊天" << endl;
			break;
		}
		int i = 0;
		cout << "时间：";
		while (msgBuff[i] != '\0')
		{
			if (msgBuff[i] != '\n')
			{
				cout << msgBuff[i];
				i++;
			}
			else
			{
				cout << endl;
				i = i + 1;
				cout << "对方：";
			}
		}
		cout << endl << endl;
	}
	return 0;
}

void sendMsg(char* msg)
{
	struct tm* now_time;
	time_t now;
	now = time(NULL);
	now_time = gmtime(&now);
	char* timebuff = new char[1024];
	timebuff = ctime(&now);
	msg = strcat(timebuff, msg);
	send(clientSocket, msg, 1024, 0);
	int i = 0;
	cout << "时间：";
	while (msg[i] != '\0')
	{
		if (msg[i] != '\n')
		{
			cout << msg[i];
			i++;
		}
		else
		{
			cout << endl;
			i = i + 1;
			cout << "我：";
		}
	}
	cout << endl << endl;
}