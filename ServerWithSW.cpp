#pragma comment(lib, "Ws2_32.lib")
#include <iostream>
#include <winsock.h>
#include <fstream>
#include <time.h>
#include <string>
using namespace std;

#define PORT 8585
const int MAXLEN = 509;//单个包内存放数据的最大长度
char buffer[10000000];
const int MAX_WAIT_TIME = 500;  //最大等待时间
const unsigned char ACK = 0x01;
const unsigned char NAK = 0x02;
const unsigned char SHAKE_1 = 0x03;
const unsigned char SHAKE_2 = 0x04;
const unsigned char SHAKE_3 = 0x05;
const unsigned char WAVE_1 = 0x06;
const unsigned char WAVE_2 = 0x07;
const unsigned char LAST = 0x08;  //标记最后一个数据包
const unsigned char NOTLAST = 0x18;  //标记不是最后一个数据包
SOCKET server;
SOCKADDR_IN server_Addr, client_Addr;

unsigned char checkSum(char* package, int len)  //计算校验和
{
	if (len == 0)
		return ~(0);
	unsigned int sum = 0;
	int i = 0;
	while (len) 
	{
		sum += (unsigned char)package[i];
		i++;
		len--;
		if (sum & 0xFF00) 
		{
			sum &= 0x00FF;
			sum++;
		}
	}
	return ~(sum & 0x00FF);
}

bool shakeHand() 
{
	while (true) 
	{
		char recv[2];
		int len_Addr = sizeof(client_Addr);
		while (recvfrom(server, recv, 2, 0, (sockaddr*)&client_Addr, &len_Addr) == SOCKET_ERROR);
		if (checkSum(recv, 2) != 0 || recv[1] != SHAKE_1)  //第一次握手
			continue;
		while (true)
		{
			recv[1] = SHAKE_2;
			recv[0] = checkSum(recv + 1, 1);
			sendto(server, recv, 2, 0, (sockaddr*)&client_Addr, sizeof(client_Addr));  //发送第二次握手包
			while (recvfrom(server, recv, 2, 0, (sockaddr*)&client_Addr, &len_Addr) == SOCKET_ERROR);
			if (checkSum(recv, 2) == 0 && recv[1] == SHAKE_1)
				continue;
			if (checkSum(recv, 2) == 0 && recv[1] == SHAKE_3)  //第三次握手成功
				break;
			if (checkSum(recv, 2) != 0 || recv[1] != SHAKE_3)
			{
				cout<<"握手失败！"<<endl;
				return false;
			}
		}
		break;
	}
	cout << "握手成功！" << endl;
	return true;
}

void rcv(char* package, int& len_recv)
{
	len_recv = 0;
	char recv[MAXLEN + 4];
	int last_Recv = -1;
	int recv_Num = 0;
	int len_Addr = sizeof(client_Addr);
	while (true)
	{
		while (true) 
		{
			memset(recv, 0, sizeof(recv));
			if (recvfrom(server, recv, MAXLEN + 4, 0, (sockaddr*)&client_Addr, &len_Addr) == SOCKET_ERROR)
				continue;
			printf("校验和：0x%x\n", (unsigned char)recv[0]);
			char send[3];
			if (checkSum(recv, MAXLEN + 4) == 0) 
			{
				if ((unsigned char)recv[2] == unsigned char((last_Recv + 1) % ((int)UCHAR_MAX + 1)))
				{
					send[1] = ACK;
					send[2] = recv[2];
					send[0] = checkSum(send + 1, 2);
					sendto(server, send, 3, 0, (sockaddr*)&client_Addr, sizeof(client_Addr));
					cout << "已经接收序号为" << recv_Num << "的包" << endl;
					recv_Num++;
					break;
				}
			}
			else 
			{
				send[1] = NAK;
				send[2] = recv[2];
				send[0] = checkSum(send + 1, 2);
				sendto(server, send, 3, 0, (sockaddr*)&client_Addr, sizeof(client_Addr));
				cout << "NAK" << endl;
				continue;
			}
		}
		last_Recv++;
		if (recv[1] == LAST)
		{
			for (int i = 4; i < recv[3] + 4; i++)
			{
				package[len_recv] = recv[i];
				len_recv++;
			}
			break;
		}
		else 
		{
			for (int i = 3; i < MAXLEN + 3; i++) 
			{
				package[len_recv] = recv[i];
				len_recv++;
			}
		}
	}
}

void waveHand()
{
	while (true)
	{
		char recv[2];
		int len_Addr = sizeof(client_Addr);
		while (recvfrom(server, recv, 2, 0, (sockaddr*)&client_Addr, &len_Addr) == SOCKET_ERROR);
		if (checkSum(recv, 2) != 0 || recv[1] != (char)WAVE_1)  //第一次挥手
			continue;
		recv[1] = WAVE_2;
		recv[0] = checkSum(recv + 1, 1);
		sendto(server, recv, 2, 0, (sockaddr*)&client_Addr, sizeof(client_Addr));  //发送第二次挥手包
		break;
	}
	cout << "挥手成功！" << endl;
}
int main() {
	clock_t start, end;
	WSADATA wsadata;
	if (WSAStartup(MAKEWORD(2, 2), &wsadata)) 
	{
		cout << "WSA初始化失败！" << endl;
		return 0;
	}
	server_Addr.sin_family = AF_INET;
	server_Addr.sin_port = htons(PORT);
	server_Addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	server = socket(AF_INET, SOCK_DGRAM, 0);
	setsockopt(server, SOL_SOCKET, SO_RCVTIMEO, (char*)&MAX_WAIT_TIME, sizeof(MAX_WAIT_TIME));
	if (server == INVALID_SOCKET) 
	{
		cout << "创建服务器Socket失败！" << endl;
		closesocket(server);
		return 0;
	}
	if (bind(server, (sockaddr*)(&server_Addr), sizeof(server_Addr)) == SOCKET_ERROR) 
	{
		cout << "绑定失败！" << endl;
		closesocket(server);
		WSACleanup();
		return 0;
	}
	cout << "连接中..." << endl;
	if (!shakeHand()) 
	{
		cout << "连接失败，退出程序！" << endl;
		return 0;
	}
	cout << "连接成功！" << endl;
	int len = 0;
	rcv(buffer, len);  //接收文件名
	buffer[len] = 0;
	string file_Name(buffer);
	cout << "文件名为：" << file_Name << endl;
	memset(buffer, 0, file_Name.length());
	start = clock();  //开始计时
	//Sleep(2000);
	rcv(buffer, len);  //接收文件内容
	end = clock();  //停止计时
	ofstream out(file_Name.c_str(), ofstream::binary);
	for (int i = 0; i < len; i++)
		out << buffer[i];
	out.close();
	cout << "成功收到文件: " << file_Name.c_str() << endl;
	double total_Time = (double)(end - start) / CLOCKS_PER_SEC;
	cout << "文件长度：" << len << endl;
	cout << "文件传输时间：" << total_Time << "秒" << endl;
	cout << "平均吞吐率：" << len / total_Time << "字节/秒" << endl;
	waveHand();
	closesocket(server);
	WSACleanup();
	cout << "程序将自动退出..." << endl;
	Sleep(4000);
	return 0;
}