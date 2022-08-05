#include<iostream>
#include<string>
using namespace std;

int lengthOfLongestSubstring(string s) {
    int n = s.length();
    string sc;
    int count = 0;
    if (n == 1)
        return 1;
    for (int i = 0; i < n; i++)
    {
        sc += s[i];
        if (sc.find(s[i + 1]) != string::npos)
        {
            if (sc.size() > count)
                count = sc.size();
            sc.erase(0, sc.find(s[i + 1]) + 1);
        }
        else if (i == n - 1)
        {
            if (sc.size() > count)
                count = sc.size();
        }
    }
    if (count == 0)
        count = sc.size();
    return count;
}

int main()
{
    string s("aab");
    cout << lengthOfLongestSubstring(s) << endl;
    return 0;
}