#include<iostream>
#include<bitset>
#include<WinSock2.h>
#pragma comment(lib, "ws2_32.lib")
#include<Windows.h>
using namespace std;

SOCKET clientSocket;
bool connection(const char* serverIP, int serverPort);
UINT recvMsg(LPVOID lpvoid);
void sendMsg(char* msg);

bitset<64> key = 0x0101010101010101;
bitset<48>subKey[16];
int shiftLeft[16] = { 1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1 };

int IP_Init[64] = { 58, 50, 42, 34, 26, 18, 10, 2,
						   60, 52, 44, 36, 28, 20, 12, 4,
						   62, 54, 46, 38, 30, 22, 14, 6,
						   64, 56, 48, 40, 32, 24, 16, 8,
						   57, 49, 41, 33, 25, 17, 9,  1,
						   59, 51, 43, 35, 27, 19, 11, 3,
						   61, 53, 45, 37, 29, 21, 13, 5,
						   63, 55, 47, 39, 31, 23, 15, 7
};

int IP_Reverse[64] = { 40, 8, 48, 16, 56, 24, 64, 32,
									39, 7, 47, 15, 55, 23, 63, 31,
									38, 6, 46, 14, 54, 22, 62, 30,
									37, 5, 45, 13, 53, 21, 61, 29,
									36, 4, 44, 12, 52, 20, 60, 28,
									35, 3, 43, 11, 51, 19, 59, 27,
									34, 2, 42, 10, 50, 18, 58, 26,
									33, 1, 41,  9, 49, 17, 57, 25
};

int E[48] = { 32,  1,  2,  3,  4,  5,
					4,  5,  6,  7,  8,  9,
					8,  9, 10, 11, 12, 13,
					12, 13, 14, 15, 16, 17,
					16, 17, 18, 19, 20, 21,
					20, 21, 22, 23, 24, 25,
					24, 25, 26, 27, 28, 29,
					28, 29, 30, 31, 32, 1
};

int P[32] = { 16,  7, 20, 21,
					29, 12, 28, 17,
					1, 15, 23, 26,
					5, 18, 31, 10,
					2,  8, 24, 14,
					32, 27,  3,  9,
					19, 13, 30,  6,
					22, 11,  4, 25
};


int S_Box[8][4][16] = {
	{
		{14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7},
		{0,15,7,4,14,2,13,1,10,6,12,11,9,5,3,8},
		{4,1,14,8,13,6,2,11,15,12,9,7,3,10,5,0},
		{15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13}
	},
	{
		{15,1,8,14,6,11,3,4,9,7,2,13,12,0,5,10},
		{3,13,4,7,15,2,8,14,12,0,1,10,6,9,11,5},
		{0,14,7,11,10,4,13,1,5,8,12,6,9,3,2,15},
		{13,8,10,1,3,15,4,2,11,6,7,12,0,5,14,9}
	},
	{
		{10,0,9,14,6,3,15,5,1,13,12,7,11,4,2,8},
		{13,7,0,9,3,4,6,10,2,8,5,14,12,11,15,1},
		{13,6,4,9,8,15,3,0,11,1,2,12,5,10,14,7},
		{1,10,13,0,6,9,8,7,4,15,14,3,11,5,2,12}
	},
	{
		{7,13,14,3,0,6,9,10,1,2,8,5,11,12,4,15},
		{13,8,11,5,6,15,0,3,4,7,2,12,1,10,14,9},
		{10,6,9,0,12,11,7,13,15,1,3,14,5,2,8,4},
		{3,15,0,6,10,1,13,8,9,4,5,11,12,7,2,14}
	},
	{
		{2,12,4,1,7,10,11,6,8,5,3,15,13,0,14,9},
		{14,11,2,12,4,7,13,1,5,0,15,10,3,9,8,6},
		{4,2,1,11,10,13,7,8,15,9,12,5,6,3,0,14},
		{11,8,12,7,1,14,2,13,6,15,0,9,10,4,5,3}
	},
	{
		{12,1,10,15,9,2,6,8,0,13,3,4,14,7,5,11},
		{10,15,4,2,7,12,9,5,6,1,13,14,0,11,3,8},
		{9,14,15,5,2,8,12,3,7,0,4,10,1,13,11,6},
		{4,3,2,12,9,5,15,10,11,14,1,7,6,0,8,13}
	},
	{
		{4,11,2,14,15,0,8,13,3,12,9,7,5,10,6,1},
		{13,0,11,7,4,9,1,10,14,3,5,12,2,15,8,6},
		{1,4,11,13,12,3,7,14,10,15,6,8,0,5,9,2},
		{6,11,13,8,1,4,10,7,9,5,0,15,14,2,3,12}
	},
	{
		{13,2,8,4,6,15,11,1,10,9,3,14,5,0,12,7},
		{1,15,13,8,10,3,7,4,12,5,6,11,0,14,9,2},
		{7,11,4,1,9,12,14,2,0,6,10,13,15,3,5,8},
		{2,1,14,7,4,10,8,13,15,12,9,0,3,5,6,11}
	}
};

int PC_1[56] = { 57, 49, 41, 33, 25, 17, 9,
						  1, 58, 50, 42, 34, 26, 18,
						  10,  2, 59, 51, 43, 35, 27,
						  19, 11,  3, 60, 52, 44, 36,
						  63, 55, 47, 39, 31, 23, 15,
						  7, 62, 54, 46, 38, 30, 22,
						  14,  6, 61, 53, 45, 37, 29,
						  21, 13,  5, 28, 20, 12,  4
};

int PC_2[48] = { 14, 17, 11, 24,  1,  5,
					  3, 28, 15,  6, 21, 10,
					  23, 19, 12,  4, 26,  8,
					  16,  7, 27, 20, 13,  2,
					  41, 52, 31, 37, 47, 55,
					  30, 40, 51, 45, 33, 48,
					  44, 49, 39, 56, 34, 53,
					  46, 42, 50, 36, 29, 32
};

bitset<28> leftShift(bitset<28> K, int n)  //????????????????????bitset????bit??01????????????
{
	bitset<28> temp = K;
	for (int i = 27; i >= 0; i--)
	{
		if (i - n < 0)
			K[i] = temp[i - n + 28];
		else
			K[i] = temp[i - n];
	}
	return K;
}

void getSubKey()  //??????????????bitset????bit??01????????????
{
	bitset<56> key56;
	bitset<28> left;
	bitset<28> right;
	bitset<48> subKey48;
	for (int i = 0; i < 56; i++)
		key56[55 - i] = key[64 - PC_1[i]];
	for (int n = 0; n < 16; n++)
	{
		for (int i = 0; i < 28; i++)  //????key56????28????????????????28-55??????28????????????????0-27??
		{
			left[i] = key56[i + 28];
			right[i] = key56[i];
		}
		left = leftShift(left, shiftLeft[n]);
		right = leftShift(right, shiftLeft[n]);
		for (int i = 0; i < 28; i++)
		{
			key56[i] = right[i];
			key56[i + 28] = left[i];
		}
		for (int i = 0; i < 48; i++)
			subKey48[47 - i] = key56[56 - PC_2[i]];
		subKey[n] = subKey48;
	}
}

bitset<32> F(bitset<32> R, bitset<48> K)
{
	bitset<48> R_After_Expand;
	bitset<32> out;
	for (int i = 0; i < 48; i++)  //????
	{
		R_After_Expand[47 - i] = R[32 - E[i]];
	}
	R_After_Expand = R_After_Expand ^ K;
	int  index = 0;
	for (int i = 0; i < 48; i = i + 6)  //S??????
	{
		int row = R_After_Expand[47 - i] * 2 + R_After_Expand[47 - i - 5];
		int col = R_After_Expand[47 - i - 1] * 8 + R_After_Expand[47 - i - 2] * 4 + R_After_Expand[47 - i - 3] * 2 + R_After_Expand[47 - i - 4];
		int  location = S_Box[i / 6][row][col];
		bitset<4> temp(location);
		out[31 - index] = temp[3];
		out[30 - index] = temp[2];
		out[29 - index] = temp[1];
		out[28 - index] = temp[0];
		index = index + 4;
	}
	bitset<32> temp = out;
	for (int i = 0; i < 32; i++)  //P????
	{
		out[31 - i] = temp[32 - P[i]];
	}
	return out;
}

bitset<64> encrypt(bitset<64> m)
{
	bitset<64> c;
	bitset<64> temp;
	bitset<32> left;
	bitset<32> right;
	bitset<32> left_new;
	for (int i = 0; i < 64; i++)  //????????IP
		temp[63 - i] = m[64 - IP_Init[i]];
	for (int i = 0; i < 32; i++)  //??????????32bit
	{
		right[i] = temp[i];
		left[i] = temp[i + 32];
	}
	for (int n = 0; n < 16; n++)  //16??????
	{
		left_new = right;
		right = left ^ F(right, subKey[n]);
		left = left_new;
	}
	for (int i = 0; i < 32; i++)  //??16????????????????32??????????
	{
		c[i] = left[i];
		c[i + 32] = right[i];
	}
	temp = c;
	for (int i = 0; i < 64; i++)  //??????????
		c[63 - i] = temp[64 - IP_Reverse[i]];
	return c;  //????????
}

bitset<64> decrypt(bitset<64> c)  //????????????????????????????????????????
{
	bitset<64> m;
	bitset<64> temp;
	bitset<32> left;
	bitset<32> right;
	bitset<32> left_new;
	for (int i = 0; i < 64; i++)
		temp[63 - i] = c[64 - IP_Init[i]];
	for (int i = 0; i < 32; i++)
	{
		left[i] = temp[i + 32];
		right[i] = temp[i];
	}
	for (int n = 0; n < 16; n++)  //????????????????????????????
	{
		left_new = right;
		right = left ^ F(right, subKey[15 - n]);
		left = left_new;
	}
	for (int i = 0; i < 32; i++)
	{
		m[i] = left[i];
		m[i + 32] = right[i];
	}
	temp = m;
	for (int i = 0; i < 64; i++)
		m[63 - i] = temp[64 - IP_Reverse[i]];
	return m;  //????????
}

char* encryptMessage(const char* buf)
{
	bitset<8320> bs1, bs2;
	char* buf2 = new char[1024];
	int length = strlen(buf);
	for (int i = 0; i < length; i++)
	{
		char c = buf[i];
		int offset = 8 * i;
		for (int j = 0; j < 8; j++)
		{
			bs1.set(offset + j, c & (1 << j));
		}
	}
	bitset<64> bs64, bsc;
	for (int i = 0; i < length; i = i + 8)
	{
		for (int j = 0; j < 64; j++)
		{
			bs64.set(j, bs1[8 * i + j]);
		}
		bsc = encrypt(bs64);
		for (int j = 0; j < 64; j++)
		{
			bs2.set(8 * i + j, bsc[j]);
		}
	}
	for (int i = 0; i < 8 * (length % 8 == 0 ? length : length + 8 - (length % 8)); i = i + 8)
	{
		char c;
		for (int j = 0; j < 8; j++)
		{
			if (bs2.test(i + j))
				c |= (1 << j);
			else
				c &= ~(1 << j);
		}
		buf2[i / 8] = c;
	}
	buf2[length + 8 - (length % 8)] = '\0';
	return buf2;
}

char* decryptMessage(const char* buf)
{
	bitset<8320> bs1, bs2;
	char* buf2 = new char[1024];
	int length = strlen(buf);
	for (int i = 0; i < length; i++)
	{
		char c = buf[i];
		int offset = 8 * i;
		for (int j = 0; j < 8; j++)
		{
			bs1.set(offset + j, c & (1 << j));
		}
	}
	bitset<64> bs64, bsm;
	for (int i = 0; i < length; i = i + 8)
	{
		for (int j = 0; j < 64; j++)
		{
			bs64.set(j, bs1[8 * i + j]);
		}
		bsm = decrypt(bs64);
		for (int j = 0; j < 64; j++)
		{
			bs2.set(8 * i + j, bsm[j]);
		}
	}
	for (int i = 0; i < 8 * length; i = i + 8)
	{
		char c;
		for (int j = 0; j < 8; j++)
		{
			if (bs2.test(i + j))
				c |= (1 << j);
			else
				c &= ~(1 << j);
		}
		buf2[i / 8] = c;
	}
	return buf2;
}

int main()
{
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (HIBYTE(wsaData.wVersion) != 2 || LOBYTE(wsaData.wVersion) != 2)
	{
		cout << "??????????????????" << GetLastError() << endl;
		return 0;
	}
	cout << "??????????????????" << endl;

	if (connection("127.0.0.1", 7611) == 0)
	{
		cout << "????????????????" << endl;
		return -1;
	}
	cout << "????????????????" << endl;
	char msgBuff[1024] = { 0 };
	while (1)
	{
		cin.getline(msgBuff, 1024);
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
		cout << "????socket??????" << GetLastError() << endl;
		WSACleanup();
		return 0;
	}

	SOCKADDR_IN clientAddr = { 0 };
	clientAddr.sin_family = AF_INET;
	clientAddr.sin_addr.S_un.S_addr = inet_addr(serverIP);   //IP????
	clientAddr.sin_port = htons(serverPort);   //????

	if (connect(clientSocket, (sockaddr*)&clientAddr, sizeof(clientAddr)) != 0)  //????????????????????????????connect()????????????????
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
		if (recv(clientSocket, msgBuff, 1024, 0) <= 0)  //????recv()????????????????????????????????????
		{
			cout << "????????????????" << endl;
			break;
		}
		char* decryptedMsg = new char[1024];
		decryptedMsg = decryptMessage(msgBuff);
		int i = 0;
		cout << "??????";
		while (decryptedMsg[i] != '\0')
		{
			if (decryptedMsg[i] != '\n')
			{
				cout << decryptedMsg[i];
				i++;
			}
			else
			{
				cout << endl;
				i = i + 1;
				cout << "??????";
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
	char* encryptedMsg = new char[1024];
	encryptedMsg = encryptMessage(msg);
	send(clientSocket, encryptedMsg, 1024, 0);
	int i = 0;
	cout << "??????";
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
			cout << "????";
		}
	}
	cout << endl << endl;
}