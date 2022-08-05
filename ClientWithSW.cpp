#pragma comment(lib, "Ws2_32.lib")
#include <iostream>
#include <winsock.h>
#include <fstream>
#include <time.h>
#include <string>
#include <queue>
using namespace std;

#define PORT 10055
const int MAXLEN = 509;//单个包内存放数据的最大长度
char buffer[10000000];
const int MAX_WAIT_TIME = 500; //最大等待时间
const unsigned char ACK = 0x01;
const unsigned char NAK = 0x02;
const unsigned char SHAKE_1 = 0x03;
const unsigned char SHAKE_2 = 0x04;
const unsigned char SHAKE_3 = 0x05;
const unsigned char WAVE_1 = 0x06;
const unsigned char WAVE_2 = 0x07;
const unsigned char LAST = 0x08;  //标记最后一个数据包
const unsigned char NOTLAST = 0x18;   //标记不是最后一个数据包
struct flags
{
	int time;
	int order;
	flags(int t, int o) :time(t), order(o) {}
};
SOCKET client;
SOCKADDR_IN server_Addr, client_Addr;

unsigned char checkSum(char* package, int len) //计算校验和
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
		char shake_Package[2];
		shake_Package[1] = SHAKE_1;
		shake_Package[0] = checkSum(shake_Package + 1, 1);
		sendto(client, shake_Package, 2, 0, (sockaddr*)&server_Addr, sizeof(server_Addr));  //发送第一次握手包
		int start = clock();
		char recv[2];
		int len_Addr = sizeof(client_Addr);
		int fail = 0;
		while (recvfrom(client, recv, 2, 0, (sockaddr*)&server_Addr, &len_Addr) == SOCKET_ERROR) 
		{
			if (clock() - start > MAX_WAIT_TIME)  //如果超时则握手失败
			{
				fail = 1;
				break;
			}
		}
		if (fail == 0 && checkSum(recv, 2) == 0 && recv[1] == SHAKE_2)  //第三次握手
		{
			shake_Package[1] = SHAKE_3;
			shake_Package[0] = checkSum(shake_Package + 1, 1);
			sendto(client, shake_Package, 2, 0, (sockaddr*)&server_Addr, sizeof(server_Addr));  //发送第三次握手包
			break;
		}
	}
	cout << "握手成功！" << endl;
	return true;
}

void waveHand() 
{
	while (true) 
	{
		char wave_Package[2];
		wave_Package[1] = WAVE_1;
		wave_Package[0] = checkSum(wave_Package + 1, 1);
		sendto(client, wave_Package, 2, 0, (sockaddr*)&server_Addr, sizeof(server_Addr));
		int start = clock();
		char recv[2];
		int len_Addr = sizeof(client_Addr);
		int fail = 0;
		while (recvfrom(client, recv, 2, 0, (sockaddr*)&server_Addr, &len_Addr) == SOCKET_ERROR) 
		{
			if (clock() - start > MAX_WAIT_TIME) 
			{
				fail = 1;
				break;
			}
		}
		if (fail == 0 && checkSum(recv, 2) == 0 && recv[1] == WAVE_2)
			break;
	}
	cout << "挥手成功！" << endl;
}

bool sendPackage(char* package, int len, int serial_num, int last = 0) 
{
	if (len > MAXLEN || (last == false && len != MAXLEN))
		return false;
	char* package_Send;
	int len_Send;
	if (!last) 
	{
		package_Send = new char[len + 3];
		package_Send[1] = NOTLAST;
		package_Send[2] = serial_num;
		for (int i = 3; i < len + 3; i++)
			package_Send[i] = package[i - 3];
		package_Send[0] = checkSum(package_Send + 1, len + 2);
		len_Send = len + 3;
	}
	else //最后一个包
	{
		package_Send = new char[len + 4];
		package_Send[1] = LAST;
		package_Send[2] = serial_num;
		package_Send[3] = len;
		for (int i = 4; i < len + 4; i++)
			package_Send[i] = package[i - 4];
		package_Send[0] = checkSum(package_Send + 1, len + 3);
		len_Send = len + 4;
	}
	sendto(client, package_Send, len_Send, 0, (sockaddr*)&server_Addr, sizeof(server_Addr));
	printf("校验和为：0x%x\n", (unsigned char)package_Send[0]);
	return true;
}

void sendPackages(char* package, int len) 
{
	queue<flags> send_Queue;
	int send_Num = 0;//已经发送的数量
	int next_Package = 0;
	int send_Succ = 0;//已经成功发送的数量
	int total_Package = len / MAXLEN + (len % MAXLEN != 0);  //包的总数
	while (true) 
	{
		if (send_Succ == total_Package)
			break;
		while (send_Queue.size() < 1 && send_Num != total_Package) 
		{
			sendPackage(package + send_Num * MAXLEN, send_Num == total_Package - 1 ? len - (total_Package - 1) * MAXLEN : MAXLEN, next_Package % ((int)UCHAR_MAX + 1), send_Num == total_Package - 1);
			send_Queue.push(flags(clock(), next_Package % ((int)UCHAR_MAX + 1)));
			next_Package++;
			send_Num++;
			cout << "已经发送序列号为" << send_Num - 1 << "的包" << endl;
		}
		char recv[3];
		int len_Addr = sizeof(server_Addr);
		if (recvfrom(client, recv, 3, 0, (sockaddr*)&server_Addr, &len_Addr) != SOCKET_ERROR && checkSum(recv, 3) == 0 && recv[1] == ACK && clock() - send_Queue.front().time < MAX_WAIT_TIME)
		{
			if ((unsigned char)recv[2] == unsigned char((send_Succ) % ((int)UCHAR_MAX + 1))) 
			{
				send_Succ++;
				send_Queue.pop();
				cout << "ACK：已经确认发送序列号为" << send_Succ - 1 << "的包" << endl;
				continue;
			}
		}
		else
		{
			next_Package--;
			send_Num -= send_Queue.size();
			while (!send_Queue.empty())
				send_Queue.pop();
			cout << "因为超时正在重传序列号为" << send_Num << "的包" << endl;
		}
	}
}

int main() {
	WSADATA wsadata;
	if (WSAStartup(MAKEWORD(2, 2), &wsadata)) 
	{
		cout << "WSA初始化失败！" << endl;
		return 0;
	}
	server_Addr.sin_family = AF_INET;
	server_Addr.sin_port = htons(PORT);
	server_Addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	client = socket(AF_INET, SOCK_DGRAM, 0);
	setsockopt(client, SOL_SOCKET, SO_RCVTIMEO, (char*)&MAX_WAIT_TIME, sizeof(MAX_WAIT_TIME));
	if (client == INVALID_SOCKET) 
	{
		cout << "创建服务器Socket失败！" << endl;
		closesocket(client);
		return 0;
	}
	cout << "连接中..." << endl;
	if (!shakeHand())
	{
		cout << "连接失败，退出程序！" << endl;
		return 0;
	}
	cout << "连接成功！" << endl;
	string file_Name;
	cout << "请输入将要传输的文件名：";
	cin >> file_Name;
	sendPackages((char*)file_Name.c_str(), file_Name.length());
	ifstream in(file_Name.c_str(), ifstream::binary);
	int len = 0;
	if (!in) 
	{
		cout << "文件打开失败！" << endl;
		return 0;
	}
	BYTE b = in.get();
	while (in) 
	{
		buffer[len] = b;
		len++;
		b = in.get();
	}
	in.close();
	cout << "文件读取完成！" << endl;
	sendPackages(buffer, len);
	cout << "发送完成！" << endl;
	waveHand();
	closesocket(client);
	WSACleanup();
	cout << "程序将自动退出..." << endl;
	Sleep(4000);
	return 0;
}