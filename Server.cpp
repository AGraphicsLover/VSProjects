#include<iostream>
#include<time.h>
#include<WinSock2.h>
#pragma comment(lib, "ws2_32.lib")
#include<Windows.h>
using namespace std;

SOCKET serverSocket, clientSocket;  //服务器，客户端
bool initSocket(const char* addr, int port);  //初始化socket
UINT recvMsg(LPVOID lpvoid);  //接收消息
void sendMsg(char* msg);  //发送消息

int main()
{
	WSADATA wsaData;  //声明WSADATA数据结构
	WSAStartup(MAKEWORD(2, 2), &wsaData);  //调用WSAStartup函数，后面就可以调用所请求的Socket库中的其它Socket函数
	if (HIBYTE(wsaData.wVersion) != 2 || LOBYTE(wsaData.wVersion) != 2)  //使用2.2版本的socket
	{
		cout << "确定协议版本失败：" << GetLastError() << endl;
		return -1;
	}
	cout << "确定协议版本成功！" << endl;
	if (initSocket("10.139.213.68", 7611) == 0)  //在初始化socket时第一个参数要记得更改为当前IP地址
	{
		cout << "初始化失败！" << endl;
		return -1;
	}
	cout << "初始化成功！" << endl;
	cout << "正在监听..." << endl;
	char buff[1024] = { 0 };
	while (1)  //不断获取用户输入并发送消息
	{
		cin >> buff;
		sendMsg(buff);
	}
	closesocket(serverSocket);  //关闭socket
	WSACleanup();  //调用WSACleanup函数来解除与Socket库的绑定并且释放Socket库所占用的系统资源
	return 0;
}
bool initSocket(const char* addr, int port)
{
	serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);  //socket采用IPv4地址，TCP协议
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

	CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)recvMsg, NULL, NULL, NULL);  //创建接收消息的线程，使得发送和接收消息并行
	return 1;
}

UINT recvMsg(LPVOID lpvoid)
{
	sockaddr_in clientAddr = { 0 };
	int len = sizeof(clientAddr);
	clientSocket = accept(serverSocket, (sockaddr*)&clientAddr, &len);
	if (clientSocket == SOCKET_ERROR)
	{
		cout << "未与客户端连接：" << GetLastError() << endl;
		closesocket(serverSocket);
		WSACleanup();
		return 0;
	}
	cout << "连接客户端成功：" << inet_ntoa(clientAddr.sin_addr) << endl;  //输出客户端IP地址
	char msgBuff[1024] = { 0 };
	while (1)
	{
		if (recv(clientSocket, msgBuff, 1024, 0) <= 0)
		{
			cout << "客户端已退出聊天" << endl;
			break;
		}
		int i = 0;
		cout << "时间：";
		while (msgBuff[i] != '\0')  //根据recv()函数接收到的字符串消息特征来进行输出
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
	timebuff= ctime(&now);
	msg = strcat(timebuff, msg);
	send(clientSocket, msg, 1024, 0);  //在上述代码对字符串处理后发送字符串消息
	int i = 0;
	cout << "时间：";  //并在本地输出自己发送的消息
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