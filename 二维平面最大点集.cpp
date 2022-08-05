#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

bool cmp(const vector<int>& a, const vector<int>& b)
{
    return a.back() > b.back();
}

int main()
{
    vector<vector<int>> a;
    int n;
    cin >> n;
    int x;
    int y;
    for (int i = 0; i < n; i++)
    {
        cin >> x >> y;
        a.push_back({ x,y });
    }
    sort(a.begin(), a.end(), cmp);
    int maxx = -1;
    for (int j = 0; j < n; j++)
    {
        if (a[j][0] > maxx)
        {
            maxx = a[j][0];
            cout << a[j][0] << " " << a[j][1] << endl;
        }
    }
    return 0;
}