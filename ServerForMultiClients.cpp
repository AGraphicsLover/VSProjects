#include<iostream>
#include<map>
#include<time.h>
#include<WinSock2.h>
#pragma comment(lib, "ws2_32.lib")
#include<Windows.h>
using namespace std;

#define clientNum 100

SOCKET serverSocket, clientSocket[clientNum];
map<int, int> mapGroup;  //记录每个客户端ID及其所在的聊天群即分组序号ID

bool initSocket(const char* addr, int port);
UINT recvMsg(LPVOID lpvoid);
void sendMsg(char* msg);
void msgFromClients(int t);
char* int_to_char(int a);

int main()
{
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (HIBYTE(wsaData.wVersion) != 2 || LOBYTE(wsaData.wVersion) != 2)
	{
		cout << "确定协议版本失败：" << GetLastError() << endl;
		return -1;
	}
	cout << "确定协议版本成功！" << endl;

	for (int x = 0; x < 10; x++)
	{
		mapGroup[x] = x / 2;
	}

	if (initSocket("10.139.213.68", 7611) == 0)
	{
		cout << "初始化失败！" << endl;
		return -1;
	}
	cout << "初始化成功！" << endl;
	cout << "正在监听..." << endl;
	char buff[1024] = { 0 };
	while (1)
	{
		cin >> buff;
		sendMsg(buff);
	}
	closesocket(serverSocket);
	WSACleanup();
	return 0;
}
bool initSocket(const char* addr, int port)
{
	serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (serverSocket == SOCKET_ERROR)
	{
		cout << "创建socket失败：" << GetLastError() << endl;
		WSACleanup();
		return 0;
	}

	SOCKADDR_IN serveraddr = { 0 };
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.S_un.S_addr = inet_addr(addr);   //IP地址
	serveraddr.sin_port = htons(port);   //端口

	if (bind(serverSocket, (sockaddr*)&serveraddr, sizeof serveraddr) != 0)
	{
		cout << "绑定失败：" << GetLastError() << endl;
		closesocket(serverSocket);
		WSACleanup();
		return 0;
	}
	cout << "绑定成功！" << endl;

	if (listen(serverSocket, 100) != 0)
	{
		cout << "监听失败：" << GetLastError() << endl;
		closesocket(serverSocket);
		WSACleanup();
		return 0;
	}

	CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)recvMsg, NULL, NULL, NULL);
	return 1;
}

UINT recvMsg(LPVOID lpvoid)
{
	sockaddr_in clientAddr = { 0 };
	int len = sizeof(clientAddr);
	for (int i = 0; i < 100; i++)
	{
		clientSocket[i] = accept(serverSocket, (sockaddr*)&clientAddr, &len);
		if (clientSocket[i] == SOCKET_ERROR)
		{
			cout << "未与客户端连接：" << GetLastError() << endl;
			closesocket(serverSocket);
			WSACleanup();
			return 0;
		}
		cout << "连接客户端" << i + 1 << "成功！" << endl;
		CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)msgFromClients, (LPVOID)i, NULL, NULL);
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
	for (int j = 0; j < 100; j++)
	{
		send(clientSocket[j], msg, 1024, 0);
	}
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
			i++;
			cout << "我：";
		}
	}
	cout << endl << endl;
}
void msgFromClients(int t)
{
	while (1)
	{
		char msgBuff[1024] = { 0 };  //存储客户端的消息
		char sendBuff[1024] = { 0 };  //存储发送给其他客户端的消息
		char clientStr[10] = { 0 };  //分组序号的字符串形式
		if (recv(clientSocket[t], msgBuff, 1024, 0) <= 0)  //获得客户端信息
		{
			cout << "客户端" << t + 1 << "已退出聊天" << endl;
			break;
		}
		int i = 0;
		int flag = 0;  //flag==2表示遍历到了2次'\n'
		cout << "时间：";
		while (msgBuff[i] != '\0')  //这个while循环实现了对客户端消息进行输出
		{
			if (msgBuff[i] != '\n')
			{
				cout << msgBuff[i];
				i++;
			}
			else
			{
				if (flag == 0)
				{
					cout << endl;
					i = i + 1;
					cout << "客户端" << t + 1 << "：";
				}
				if (flag == 1)
				{
					flag++;
					break;
				}
				flag++;
			}
		}
		cout << endl << endl;
		if (flag == 2)
		{
			int temp = i;
			i++;
			while (msgBuff[i] != '\0')
			{
				clientStr[i - temp - 1] = msgBuff[i];
				i++;
			}
			clientStr[i - temp] = '\0';
			int client_n = atoi(clientStr);  //将分组序号字符串转成int类型
			int z = 0;
			while (z < temp)
			{
				sendBuff[z] = msgBuff[z];  //时间和消息字符串拷贝
				z++;
			}
			strcat(sendBuff, "\n");
			strcat(sendBuff, int_to_char(t + 1));  //将客户端的序号加在字符串中
			mapGroup[t] = client_n - 1;  //将发送消息的客户端加入该分组序号的客户端的聊天群中
			map<int, int>::iterator it;
			for (it = mapGroup.begin(); it != mapGroup.end(); it++)  //给每一位在该分组序号的聊天群的客户端发送消息
			{
				if (it->second == client_n - 1 && it->first != t)
				{
					send(clientSocket[it->first], sendBuff, 1024, 0);
				}
			}
		}
		else  //如果该客户端本来就在该聊天群中，则不用改变聊天群，并且能直接发送消息
		{
			strcat(sendBuff, msgBuff);
			strcat(sendBuff, "\n");
			strcat(sendBuff, int_to_char(t + 1));
			map<int, int>::iterator it;
			for (it = mapGroup.begin(); it != mapGroup.end(); it++)
			{
				if (it->second == mapGroup[t])
				{
					send(clientSocket[it->first], sendBuff, 1024, 0);
				}
			}
		}
	}
}
char* int_to_char(int a)  //int类型转为字符串
{
	char* b;
	b = new char[10];
	sprintf(b, "%d", a);
	return b;
}