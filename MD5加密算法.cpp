#include<iostream>
#include<bitset>
#include<string>
using namespace std;

unsigned char FILL[64] = {
    0x80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };  //64字节填充

typedef struct
{
    unsigned int bitNum[2];
    unsigned int buffer[4];
    unsigned char data[64];
}MD5_Group;

int F(int b, int c, int d)
{
    return ((b & c) | (~b & d));
}
int G(int b, int c, int d)
{
    return ((b & d) | (c & ~d));
}
int H(int b, int c, int d)
{
    return (b ^ c ^ d);
}
int I(int b, int c, int d)
{
    return (c ^ (b | ~d));
}
unsigned int CLS(unsigned int x, int n)
{
    if (n <= 0)
        return x;
    unsigned int x1 = x << n;
    unsigned int x2 = x >> (32 - n);
    return x1 | x2;
}

void Init(MD5_Group* group);  //初始化分组及其相关信息
void GroupUpdate(MD5_Group* group, unsigned char* input, unsigned int inputLen);  //更新分组相关信息
void Compress(unsigned int state[4], unsigned char groupData[64]);  //压缩函数
void MD5(MD5_Group* group, unsigned char abstract[16]);  //MD5流程函数
void IntToChar(unsigned char* output, unsigned int* input, unsigned int inputLen);  //将int数组转换成char数组
void CharToInt(unsigned int* output, unsigned char* input, unsigned int inputLen);  //将char数组转换成int数组

void Init(MD5_Group* group) 
{
    group->bitNum[0] = 0;
    group->bitNum[1] = 0;
    group->buffer[0] = 0x67452301;  //四个链接变量，注意与大端序的区别，内存中是小端序
    group->buffer[1] = 0xEFCDAB89;
    group->buffer[2] = 0x98BADCFE;
    group->buffer[3] = 0x10325476;
}

void GroupUpdate(MD5_Group* group, unsigned char* input, unsigned int inputLen) 
{
    unsigned int i = 0, index = 0, groupLen = 0;
    index = (group->bitNum[0] >> 3) & 0x3F;
    groupLen = 64 - index;  //GroupUpdate调用时index为0，groupLen为64，预留出64位存放数据长度
    group->bitNum[0] += inputLen << 3;
    group->bitNum[1] += inputLen >> 29;
    if (inputLen >= groupLen) 
    {
        memcpy(&group->data[index], input, groupLen);
        Compress(group->buffer, group->data);
        for (i = groupLen; i + 64 <= inputLen; i += 64) 
            Compress(group->buffer, &input[i]);
        index = 0;
    }
    else i = 0;
    memcpy(&group->data[index], &input[i], inputLen - i);  //最后剩下的分组
}

void MD5(MD5_Group* group, unsigned char abstract[16])
{
    unsigned int index = 0, fillLen = 0;
    unsigned char bits[8];
    index = (group->bitNum[0] >> 3) & 0x3F;
    fillLen = (index < 56) ? (56 - index) : (120 - index);  //得到需要填充的长度，注意长度占8字节
    IntToChar(bits, group->bitNum, 8);
    GroupUpdate(group, FILL, fillLen);
    GroupUpdate(group, bits, 8);
    IntToChar(abstract, group->buffer, 16);
}

void IntToChar(unsigned char* output, unsigned int* input, unsigned int inputLen) 
{
    unsigned int i = 0, j = 0;
    while (j < inputLen)
    {
        output[j] = input[i] & 0xFF;
        output[j + 1] = (input[i] >> 8) & 0xFF;
        output[j + 2] = (input[i] >> 16) & 0xFF;
        output[j + 3] = (input[i] >> 24) & 0xFF;
        i++;
        j += 4;
    }
}

void CharToInt(unsigned int* output, unsigned char* input, unsigned int inputLen) 
{
    unsigned int i = 0, j = 0;
    while (j < inputLen) 
    {
        output[i] = (input[j]) | (input[j + 1] << 8) | (input[j + 2] << 16) | (input[j + 3] << 24);
        i++;
        j += 4;
    }
}

void Compress(unsigned int buffer[4], unsigned char groupData[64])
{
    unsigned int a = buffer[0];
    unsigned int b = buffer[1];
    unsigned int c = buffer[2];
    unsigned int d = buffer[3];
    unsigned int x[16];

    CharToInt(x, groupData, 64);
    a = b + CLS(a + F(b, c, d) + x[0] + 0xD76AA478, 7);
    d = a + CLS(d + F(a, b, c) + x[1] + 0xE8C7B756, 12);
    c = d + CLS(c + F(d, a, b) + x[2] + 0x242070DB, 17);
    b = c + CLS(b + F(c, d, a) + x[3] + 0xC1BDCEEE, 22);
    a = b + CLS(a + F(b, c, d) + x[4] + 0xF57C0FAF, 7);
    d = a + CLS(d + F(a, b, c) + x[5] + 0x4787C62A, 12);
    c = d + CLS(c + F(d, a, b) + x[6] + 0xA8304613, 17);
    b = c + CLS(b + F(c, d, a) + x[7] + 0xFD469501, 22);
    a = b + CLS(a + F(b, c, d) + x[8] + 0x698098D8, 7);
    d = a + CLS(d + F(a, b, c) + x[9] + 0x8B44F7AF, 12);
    c = d + CLS(c + F(d, a, b) + x[10] + 0xFFFF5BB1, 17);
    b = c + CLS(b + F(c, d, a) + x[11] + 0x895CD7BE, 22);
    a = b + CLS(a + F(b, c, d) + x[12] + 0x6B901122, 7);
    d = a + CLS(d + F(a, b, c) + x[13] + 0xFD987193, 12);
    c = d + CLS(c + F(d, a, b) + x[14] + 0xA679438E, 17);
    b = c + CLS(b + F(c, d, a) + x[15] + 0x49B40821, 22);

    a = b + CLS(a + G(b, c, d) + x[1] + 0xF61E2562, 5);
    d = a + CLS(d + G(a, b, c) + x[6] + 0xC040B340, 9);
    c = d + CLS(c + G(d, a, b) + x[11] + 0x265E5A51, 14);
    b = c + CLS(b + G(c, d, a) + x[0] + 0xE9B6C7AA, 20);
    a = b + CLS(a + G(b, c, d) + x[5] + 0xD62F105D, 5);
    d = a + CLS(d + G(a, b, c) + x[10] + 0x2441453, 9);
    c = d + CLS(c + G(d, a, b) + x[15] + 0xD8A1E681, 14);
    b = c + CLS(b + G(c, d, a) + x[4] + 0xE7D3FBC8, 20);
    a = b + CLS(a + G(b, c, d) + x[9] + 0x21E1CDE6, 5);
    d = a + CLS(d + G(a, b, c) + x[14] + 0xC33707D6, 9);
    c = d + CLS(c + G(d, a, b) + x[3] + 0xF4D50D87, 14);
    b = c + CLS(b + G(c, d, a) + x[8] + 0x455A14ED, 20);
    a = b + CLS(a + G(b, c, d) + x[13] + 0xA9E3E905, 5);
    d = a + CLS(d + G(a, b, c) + x[2] + 0xFCEFA3F8, 9);
    c = d + CLS(c + G(d, a, b) + x[7] + 0x676F02D9, 14);
    b = c + CLS(b + G(c, d, a) + x[12] + 0x8D2A4C8A, 20);

    a = b + CLS(a + H(b, c, d) + x[5] + 0xFFFA3942, 4);
    d = a + CLS(d + H(a, b, c) + x[8] + 0x8771F681, 11);
    c = d + CLS(c + H(d, a, b) + x[11] + 0x6D9D6122, 16);
    b = c + CLS(b + H(c, d, a) + x[14] + 0xFDE5380C, 23);
    a = b + CLS(a + H(b, c, d) + x[1] + 0xA4BEEA44, 4);
    d = a + CLS(d + H(a, b, c) + x[4] + 0x4BDECFA9, 11);
    c = d + CLS(c + H(d, a, b) + x[7] + 0xF6BB4B60, 16);
    b = c + CLS(b + H(c, d, a) + x[10] + 0xBEBFBC70, 23);
    a = b + CLS(a + H(b, c, d) + x[13] + 0x289B7EC6, 4);
    d = a + CLS(d + H(a, b, c) + x[0] + 0xEAA127FA, 11);
    c = d + CLS(c + H(d, a, b) + x[3] + 0xD4EF3085, 16);
    b = c + CLS(b + H(c, d, a) + x[6] + 0x4881D05, 23);
    a = b + CLS(a + H(b, c, d) + x[9] + 0xD9D4D039, 4);
    d = a + CLS(d + H(a, b, c) + x[12] + 0xE6DB99E5, 11);
    c = d + CLS(c + H(d, a, b) + x[15] + 0x1FA27CF8, 16);
    b = c + CLS(b + H(c, d, a) + x[2] + 0xC4AC5665, 23);

    a = b + CLS(a + I(b, c, d) + x[0] + 0xF4292244, 6);
    d = a + CLS(d + I(a, b, c) + x[7] + 0x432AFF97, 10);
    c = d + CLS(c + I(d, a, b) + x[14] + 0xAB9423A7, 15);
    b = c + CLS(b + I(c, d, a) + x[5] + 0xFC93A039, 21);
    a = b + CLS(a + I(b, c, d) + x[12] + 0x655B59C3, 6);
    d = a + CLS(d + I(a, b, c) + x[3] + 0x8F0CCC92, 10);
    c = d + CLS(c + I(d, a, b) + x[10] + 0xFFEFF47D, 15);
    b = c + CLS(b + I(c, d, a) + x[1] + 0x85845DD1, 21);
    a = b + CLS(a + I(b, c, d) + x[8] + 0x6FA87E4F, 6);
    d = a + CLS(d + I(a, b, c) + x[15] + 0xFE2CE6E0, 10);
    c = d + CLS(c + I(d, a, b) + x[6] + 0xA3014314, 15);
    b = c + CLS(b + I(c, d, a) + x[13] + 0x4E0811A1, 21);
    a = b + CLS(a + I(b, c, d) + x[4] + 0xF7537E82, 6);
    d = a + CLS(d + I(a, b, c) + x[11] + 0xBD3AF235, 10);
    c = d + CLS(c + I(d, a, b) + x[2] + 0x2AD7D2BB, 15);
    b = c + CLS(b + I(c, d, a) + x[9] + 0xEB86D391, 21);

    buffer[0] += a;
    buffer[1] += b;
    buffer[2] += c;
    buffer[3] += d;
}
int main() 
{
    unsigned char m[] = "";
    unsigned char c[16];
    MD5_Group md5;
    Init(&md5);
    GroupUpdate(&md5, m, (int)strlen((char*)m));
    MD5(&md5, c);
    cout << "加密前：" << m << endl;
    cout << "加密后：";
    for (int i = 0; i < 16; i++)
        printf("%02x", c[i]);
    return 0;
}