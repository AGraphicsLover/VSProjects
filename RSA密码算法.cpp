#include <iostream>
#include<ctime>
using namespace std;

static int prime[] = {
3,    5,    7,    11,   13,   17,   19,   23,   29,   31,
37,   41,   43,   47,   53,   59,   61,   67,   71,   73,
79,   83,   89,   97,   101,  103,  107,  109,  113,  127,
131,  137,  139,  149,  151,  157,  163,  167,  173,  179,
181,  191,  193,  197,  199,  211,  223,  227,  229,  233,
239,  241,  251,  257,  263,  269,  271,  277,  281,  283,
293,  307,  311,  313,  317,  331,  337,  347,  349,  353,
359,  367,  373,  379,  383,  389,  397,  401,  409,  419,
421,  431,  433,  439,  443,  449,  457,  461,  463,  467,
479,  487,  491,  499,  503,  509,  521,  523,  541,  547,
557,  563,  569,  571,  577,  587,  593,  599,  601,  607,
613,  617,  619,  631,  641,  643,  647,  653,  659,  661,
673,  677,  683,  691,  701,  709,  719,  727,  733,  739,
743,  751,  757,  761,  769,  773,  787,  797,  809,  811,
821,  823,  827,  829,  839,  853,  857,  859,  863,  877,
881,  883,  887,  907,  911,  919,  929,  937,  941,  947,
953,  967,  971,  977,  983,  991,  997,  1009, 1013, 1019,
1021, 1031, 1033, 1039, 1049, 1051, 1061, 1063, 1069, 1087,
1091, 1093, 1097, 1103, 1109, 1117, 1123, 1129, 1151, 1153,
1163, 1171, 1181, 1187, 1193, 1201, 1213, 1217, 1223, 1229,
1231, 1237, 1249, 1259, 1277, 1279, 1283, 1289, 1291, 1297,
1301, 1303, 1307, 1319, 1321, 1327, 1361, 1367, 1373, 1381,
1399, 1409, 1423, 1427, 1429, 1433, 1439, 1447, 1451, 1453,
1459, 1471, 1481, 1483, 1487, 1489, 1493, 1499, 1511, 1523,
1531, 1543, 1549, 1553, 1559, 1567, 1571, 1579, 1583, 1597,
1601, 1607, 1609, 1613, 1619, 1621, 1627, 1637, 1657, 1663,
1667, 1669, 1693, 1697, 1699, 1709, 1721, 1723, 1733, 1741,
1747, 1753, 1759, 1777, 1783, 1787, 1789, 1801, 1811, 1823,
1831, 1847, 1861, 1867, 1871, 1873, 1877, 1879, 1889, 1901,
1907, 1913, 1931, 1933, 1949, 1951, 1973, 1979, 1987, 1993,
1997, 1999, 2003, 2011, 2017, 2027, 2029, 2039, 2053, 2063,
2069, 2081, 2083, 2087, 2089, 2099, 2111, 2113, 2129, 2131,
2137, 2141, 2143, 2153, 2161, 2179, 2203, 2207, 2213, 2221,
2237, 2239, 2243, 2251, 2267, 2269, 2273, 2281, 2287, 2293,
2297, 2309, 2311, 2333, 2339, 2341, 2347, 2351, 2357, 2371,
2377, 2381, 2383, 2389, 2393, 2399, 2411, 2417, 2423, 2437,
2441, 2447, 2459, 2467, 2473, 2477, 2503 };

const int BNSize = 64;
class BigNum {

	friend BigNum operator+ (const BigNum&, const BigNum&);
	friend BigNum operator- (const BigNum&, const BigNum&);
	friend BigNum operator- (const BigNum&, const int&);
	friend BigNum operator* (const BigNum&, const BigNum&);
	friend BigNum operator% (const BigNum&, const BigNum&);
	friend BigNum operator/ (const BigNum&, const BigNum&);
	friend BigNum operator* (const BigNum&, const unsigned int&);
	friend bool operator< (const BigNum&, const BigNum&);
	friend bool operator> (const BigNum&, const BigNum&);
	friend bool operator<= (const BigNum&, const int&);
	friend bool operator== (const BigNum&, const BigNum&);
	friend bool operator== (const BigNum&, const int&);
	friend ostream& operator<< (ostream&, const BigNum&);
	friend BigNum FastPower(const BigNum&, const BigNum&, const BigNum&);
	friend void SortPrime(BigNum& n);

private:
	unsigned int data[BNSize];
	bool sign;

public:
	BigNum();
	BigNum(const int&);
	BigNum(const BigNum&);

	void operator= (const BigNum&);
	void operator= (const int& a) { Clear(); data[0] = a; }
	void operator>> (const int&);
	inline int getLength() const;   //返回大数的长度
	bool getSign() { return sign; }  //返回大数的正负 
	void Clear();  //大数清0
	void Random(); //随机产生一个大数
	void Display() const;
	void Output(ostream& out) const;
	bool IsOdd() const { return (data[0] & 1); }  //判断大数奇偶性
};

BigNum::BigNum()
{
	for (int i = 0; i < BNSize; i++)
		data[i] = 0;
	sign = true;
}

BigNum::BigNum(const int& input)
{
	for (int i = 0; i < BNSize; i++)
		data[i] = 0;
	data[0] = input;
	if (input >= 0)
		sign = true;
	else
		sign = false;
}

BigNum::BigNum(const BigNum& input)
{
	for (int i = 0; i < BNSize; i++)
		data[i] = input.data[i];
	sign = input.sign;
}

void BigNum::operator= (const BigNum& input)
{
	for (int i = 0; i < BNSize; i++)
		data[i] = input.data[i];
	sign = input.sign;
}

bool operator< (const BigNum& a, const BigNum& b)
{
	for (int i = BNSize - 1; i >= 0; i--)
	{
		if (a.data[i] < b.data[i])
			return true;
		if (a.data[i] > b.data[i])
			return false;
	}
	return false;
}

bool operator> (const BigNum& a, const BigNum& b)
{
	for (int i = BNSize - 1; i >= 0; i--)
	{
		if (a.data[i] > b.data[i])
			return true;
		if (a.data[i] < b.data[i])
			return false;
	}
	return false;
}

bool operator== (const BigNum& a, const BigNum& b)
{
	for (int i = 0; i < BNSize; i++)
		if (a.data[i] != b.data[i])
			return false;
	return true;
}

bool operator== (const BigNum& a, const int& b)
{
	for (int i = 1; i < a.getLength(); i++)
	{
		if (a.data[i] != 0)
			return false;
	}
	return a.data[0] == b;
}

BigNum operator+ (const BigNum& a, const BigNum& b)
{
	BigNum result;
	unsigned __int64 sum;  //sum占64位，存放两个大数相加的和
	unsigned int carry = 0, sub;  //carry为进位标志；当两数符号相异时，sub存放两个大数相减的差
	int length = (a.getLength() >= b.getLength() ? a.getLength() : b.getLength());  //取a、b中较长的长度为总长度
	if (a.sign == b.sign)
	{
		for (int i = 0; i < length; i++)  //对应每1字节进行相加
		{
			sum = (unsigned __int64)a.data[i] + b.data[i] + carry;
			result.data[i] = (unsigned int)sum;
			carry = (sum >> 32);  //sum超过32位的值为进位的大小
		}
		result.sign = a.sign;
		return result;
	}
	else  //符号不同时,进行减法运算
	{
		BigNum tempa, tempb;
		if (a < b)  //取出a、b中绝对值较大的作为被减数
		{
			tempa = b;
			tempb = a;
		}
		else
		{
			tempa = a;
			tempb = b;
		}
		for (int i = 0; i < length; i++)
		{
			sub = tempb.data[i] + carry;
			if (tempa.data[i] >= sub)
			{
				result.data[i] = tempa.data[i] - sub;
				carry = 0;
			}
			else
			{
				result.data[i] = (unsigned __int64)tempa.data[i] + (1 << 32) - sub;
				carry = 1;
			}
		}
		result.sign = tempa.sign;
		return result;
	}
}

BigNum operator- (const BigNum& a, const BigNum& b)
{
	BigNum result;
	unsigned __int64 sum;
	unsigned int carry = 0, sub;

	if (a.sign == b.sign)
	{
		BigNum tempa, tempb;
		if (a < b)
		{
			tempa = b;
			tempb = a;
			tempa.sign = !tempa.sign;
		}
		else
		{
			tempa = a;
			tempb = b;
		}
		for (int i = 0; i < BNSize; i++)
		{
			sub = tempb.data[i] + carry;
			if (tempa.data[i] >= sub)
			{
				result.data[i] = tempa.data[i] - sub;
				carry = 0;
			}
			else
			{
				result.data[i] = (unsigned __int64)tempa.data[i] + (1 << 32) - sub;
				carry = 1;
			}
		}
		result.sign = tempa.sign;
		return result;
	}
	else
	{
		for (int i = 0; i < BNSize; i++)
		{
			sum = (unsigned __int64)a.data[i] + b.data[i] + carry;
			result.data[i] = (unsigned int)sum;
			carry = (sum >> 32);
		}
		result.sign = a.sign;
		return result;
	}
}

BigNum operator- (const BigNum& a, const int& b)
{
	BigNum temp(b);
	BigNum result = a - temp;
	return result;
}

BigNum operator* (const BigNum& a, const unsigned int& b)
{
	BigNum result;
	unsigned __int64 sum;
	unsigned int carry = 0;
	for (int i = 0; i < BNSize; i++)
	{
		sum = ((unsigned __int64)a.data[i]) * b + carry;
		result.data[i] = (unsigned int)sum;
		carry = (sum >> 32);
	}
	result.sign = a.sign;
	return result;
}

BigNum operator* (const BigNum& a, const BigNum& b)
{
	BigNum result, last, temp;
	unsigned __int64 sum;
	unsigned int carry;
	for (int i = 0; i < b.getLength(); i++)
	{
		carry = 0;
		for (int j = 0; j < a.getLength() + 1; j++)
		{
			sum = ((unsigned __int64)a.data[j]) * (b.data[i]) + carry;
			if ((i + j) < BNSize)
				temp.data[i + j] = (unsigned int)sum;
			carry = (sum >> 32);
		}
		result = (temp + last);
		last = result;
		temp.Clear();
	}
	if (a.sign == b.sign)
		result.sign = true;
	else
		result.sign = false;
	return result;
}

BigNum operator/ (const BigNum& a, const BigNum& b)
{
	unsigned int mul, low, high;  //mul为当前的商；low、high为二分查找商时所用的低位高位标志
	BigNum dividend, quotient, sub, subsequent;  //dividend为被除数，sub为除数与当前商的积，subsequent为除数与下一商的积，quotient为真正的商
	int lengtha = a.getLength(), lengthb = b.getLength();
	if (a < b)  //如果被除数小于除数,直接返回0
	{
		if (a.sign == b.sign)
			quotient.sign = true;
		else
			quotient.sign = false;
		return quotient;
	}
	int i;
	for (i = 0; i < lengthb; i++)
		dividend.data[i] = a.data[lengtha - lengthb + i];
	for (i = lengtha - lengthb; i >= 0; i--)
	{
		if (dividend < b)  //如果被除数小于除数，往后补位
		{
			for (int j = lengthb; j > 0; j--)
				dividend.data[j] = dividend.data[j - 1];
			dividend.data[0] = a.data[i - 1];
			continue;
		}
		low = 0;
		high = 0xffffffff;
		while (low < high)  //二分查找法查找试商
		{
			mul = (((unsigned __int64)high) + low) / 2;
			sub = (b * mul);
			subsequent = (b * (mul + 1));
			if (((sub < dividend) && (subsequent > dividend)) || (sub == dividend))
				break;
			if (subsequent == dividend)
			{
				mul++;
				sub = subsequent;
				break;
			}
			if ((sub < dividend) && (subsequent < dividend))
			{
				low = mul;
				continue;
			}
			if ((sub > dividend) && (subsequent > dividend))
			{
				high = mul;
				continue;
			}
		}
		quotient.data[i] = mul;  //试商结果保存到商中去
		dividend = dividend - sub;  //被除数变为被除数与商积的差
		if ((i - 1) >= 0)  //临时被除数往后补位
		{
			for (int j = lengthb; j > 0; j--)
				dividend.data[j] = dividend.data[j - 1];
			dividend.data[0] = a.data[i - 1];
		}
	}
	if (a.sign == b.sign)  //判断商的符号
		quotient.sign = true;
	else
		quotient.sign = false;
	return quotient;
}

BigNum operator% (const BigNum& a, const BigNum& b)
{
	unsigned int mul, low, high;
	BigNum dividend, quotient, sub, subsequent;
	int lengtha = a.getLength(), lengthb = b.getLength();
	if (a < b)  //如果被除数小于除数,返回被除数为模
	{
		dividend = a;
		dividend.sign = a.sign;  //余数的商永远与被除数相同
		return dividend;
	}
	int i;
	for (i = 0; i < lengthb; i++)  //进行除法运算
		dividend.data[i] = a.data[lengtha - lengthb + i];
	for (i = lengtha - lengthb; i >= 0; i--)
	{
		if (dividend < b)
		{
			for (int j = lengthb; j > 0; j--)
				dividend.data[j] = dividend.data[j - 1];
			dividend.data[0] = a.data[i - 1];
			continue;
		}
		low = 0;
		high = 0xffffffff;
		while (low <= high)
		{
			mul = (((unsigned __int64)high) + low) / 2;
			sub = (b * mul);
			subsequent = (b * (mul + 1));

			if (((sub < dividend) && (subsequent > dividend)) || (sub == dividend))
				break;
			if (subsequent == dividend)
			{
				mul++;
				sub = subsequent;
				break;
			}
			if ((sub < dividend) && (subsequent < dividend))
			{
				low = mul;
				continue;
			}
			if ((sub > dividend) && (subsequent > dividend))
			{
				high = mul;
				continue;
			}
		}
		quotient.data[i] = mul;
		dividend = dividend - sub;
		if ((i - 1) >= 0)
		{
			for (int j = lengthb; j > 0; j--)
				dividend.data[j] = dividend.data[j - 1];
			dividend.data[0] = a.data[i - 1];
		}
	}
	dividend.sign = a.sign;  //临时被除数即为所求模
	return dividend;
}

void BigNum::Display() const
{
	unsigned int temp, result;
	unsigned int andNum = 0xf0000000;
	int lineNum = 0;
	for (int i = getLength() - 1; i >= 0; i--)
	{
		temp = data[i];
		for (int j = 0; j < 8; j++)  //大数的每一位数字转换成16进制输出
		{
			result = temp & andNum;
			result = (result >> 28);
			temp = (temp << 4);
			if (result >= 0 && result <= 9)
				cout << result;
			else
			{
				switch (result)
				{
				case 10:
					cout << "A";
					break;
				case 11:
					cout << "B";
					break;
				case 12:
					cout << "C";
					break;
				case 13:
					cout << "D";
					break;
				case 14:
					cout << "E";
					break;
				case 15:
					cout << "F";
					break;
				}
			}
		}
		cout << " ";
		lineNum++;
		if (lineNum == 8)
		{
			lineNum = 0;
			cout << endl;
		}
	}
	cout << endl;
}

void BigNum::Output(ostream& out) const
{
	unsigned int temp, result;
	unsigned int andNum = 0xf0000000;
	for (int i = getLength() - 1; i >= 0; i--)
	{
		temp = data[i];
		for (int j = 0; j < 8; j++)  //大数的每一位数字转换成16进制输出
		{
			result = temp & andNum;
			result = (result >> 28);
			temp = (temp << 4);
			if (result >= 0 && result <= 9)
				out << result;
			else
			{
				switch (result)
				{
				case 10:
					out << "A";
					break;
				case 11:
					out << "B";
					break;
				case 12:
					out << "C";
					break;
				case 13:
					out << "D";
					break;
				case 14:
					out << "E";
					break;
				case 15:
					out << "F";
					break;
				}
			}
		}
	}
	out << endl;
}

ostream& operator<< (ostream& out, const BigNum& x)
{
	x.Output(out);
	return out;
}

void BigNum::Clear()
{
	for (int i = 0; i < BNSize; i++)
		data[i] = 0;
}

inline int BigNum::getLength() const
{
	int length = BNSize;
	for (int i = BNSize - 1; i >= 0; i--)
	{
		if (data[i] == 0)  //第一位不为0即为LENGTH
			length--;
		else
			break;
	}
	return length;
}

void BigNum::operator>> (const int& a)
{
	unsigned int bit;
	data[0] = (data[0] >> a);
	for (int i = 1; i < getLength(); i++)
	{
		bit = data[i] & 1;  //先将每一位的低位移到bit中
		bit = bit << (32 - a);  //再把bit移到上一位的高位中
		data[i - 1] = data[i - 1] | bit;
		data[i] = (data[i] >> a);
	}
}

bool operator<= (const BigNum& a, const int& b)
{
	for (int i = 1; i < a.getLength(); i++)
	{
		if (a.data[i] != 0)
			return false;
	}
	if (a.data[0] <= b)
		return true;
	else
		return false;
}

void BigNum::Random()
{
	for (int i = 0; i < (BNSize / 4); i++)
		for (int j = 0; j < 4; j++)
		{
			data[i] = data[i] << 8;
			data[i] += (rand() % 0XFFFFFFFF);
		}
}

BigNum FastPower(const BigNum& n, const BigNum& p, const BigNum& m)
{
	BigNum temp = p;
	BigNum base = n % m;
	BigNum result(1);
	while (temp > 1)  //查看指数p的二进制形式的每一位
	{
		if (temp.IsOdd())  //如果该位为1，则表示该位需要参与模运算
			result = (result * base) % m;
		base = (base * base) % m;
		temp >> 1;
	}
	return (base * result) % m;
}

void SortPrime(BigNum& n)
{
	int i = 0;
	BigNum divisor;
	const int length = sizeof(prime) / sizeof(int);
	while (i != length)
	{
		n.Random();
		while (!n.IsOdd())
			n.Random();
		i = 0;
		for (; i < length; i++)
		{
			divisor = prime[i];
			if ((n % divisor) == 0)
				break;
		}
	}
}

bool MillerRabin(const BigNum& n)  //MillerRabin素性检验
{
	BigNum r, a, y;
	unsigned int s, j;
	r = n - 1;
	s = 0;
	while (!r.IsOdd())
	{
		s++;
		r >> 1;
	}
	a.Random();  //随机产生一个检测数a
	y = FastPower(a, r, n);  //y = a的r次幂模n
	if ((!(y == 1)) && (!(y == (n - 1))))  //检测2至s轮
	{
		j = 1;
		while ((j <= s - 1) && (!(y == (n - 1))))
		{
			y = (y * y) % n;
			if (y == 1)
				return false;
			j++;
		}
		if (!(y == (n - 1)))
			return false;
	}
	return true;
}

BigNum GeneratePrime(int& times)
{
	BigNum n;
	int i = 0;
	while (i < 5)
	{
		times++;
		cout << "第" << times << "次" << "生成大奇数：" << endl;
		SortPrime(n);
		n.Display();
		i = 0;
		for (; i < 5; i++)  //5轮RABINMILLER测试
		{
			cout << "进行第" << i + 1 << "轮MillerRabin素性检验：";
			if (!MillerRabin(n))
			{
				cout << "    结果：失败" << endl << endl;
				break;
			}
			cout << "    第" << i + 1 << "次通过" << endl << endl;
		}
	}
	return n;
}

BigNum Gcd(const BigNum& m, const BigNum& n)
{
	if (n == 0)
		return m;
	else
		return Gcd(n, m % n);
}

BigNum ExtendedGcd(const BigNum& a, const BigNum& b, BigNum& x, BigNum& y)
{
	BigNum t, d;
	if (b == 0)
	{
		x = 1;
		y = 0;
		return a;
	}
	d = ExtendedGcd(b, a % b, x, y);
	t = x;
	x = y;
	y = t - ((a / b) * y);
	return d;
}

BigNum RSAEncrypt(BigNum& m, BigNum& e, BigNum& n)
{
	return FastPower(m, e, n);
}

BigNum RSADecrypt(BigNum& c, BigNum& d, BigNum& n)
{
	return FastPower(c, d, n);
}

int main()
{
	srand((unsigned)time(NULL));
	int time = 0;
	BigNum p = GeneratePrime(time);
	cout << "生成512比特素数p成功！    " << "次数： " << time << "次" << endl;
	cout << "大素数p： " << endl;
	p.Display();
	time = 0;
	BigNum q = GeneratePrime(time);
	cout << "生成512比特素数q成功！    " << "次数： " << time << "次" << endl;
	cout << "大素数q： " << endl;
	q.Display();
	cout << "大素数p： " << endl;
	p.Display();
	cout << "大素数q： " << endl;
	q.Display();
	BigNum n = p * q;
	cout << "公开钥n为： " << endl;
	n.Display();
	BigNum fn = (p - 1) * (q - 1);
	BigNum e;
	BigNum d;
	BigNum y;
	BigNum temp;
	while (1)
	{
		e.Random();
		while (!(Gcd(e, fn) == 1))
			e.Random();
		temp = ExtendedGcd(e, fn, d, y);
		temp = (e * d) % fn;
		if (temp == 1)
			break;
	}
	cout << "公开钥e为： " << endl;
	e.Display();
	cout << "秘密钥d为： " << endl;
	d.Display();
	BigNum m;
	m.Random();
	cout << "明文m为：" << endl;
	m.Display();
	BigNum c = RSAEncrypt(m, e, n);
	cout << "密文c为：" << endl;
	c.Display();
	BigNum m_Decrypt = RSADecrypt(c, d, n);
	cout << "解密得到的明文m'为：" << endl;
	m_Decrypt.Display();
	return 0;
}