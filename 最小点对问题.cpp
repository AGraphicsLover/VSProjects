#include<iostream>
#include<cmath>
#include<algorithm>
#include<limits.h>
#include<iomanip>
using namespace std;
int s[30000];
struct point
{
	double x;
	double y;
}points[30000];
double distance(int p1, int p2)
{
	return ((points[p1].x - points[p2].x) * (points[p1].x - points[p2].x) + (points[p1].y - points[p2].y) * (points[p1].y - points[p2].y));
}
bool cmp1(const point& p1, const point& p2)
{
	if (p1.x == p2.x)
		return (p1.y < p2.y);
	else
		return (p1.x < p2.x);
}
bool cmp2(const int& p1, const int& p2)
{
	return (points[p1].y < points[p2].y);
}
double min_distance(int first, int last)
{
    int num = 0;
    int middle = (first + last) / 2;
    double d_min = INT_MAX;
    double d_left = 0, d_right = 0;
    if (first == last || first + 1 == last)
    {
        return d_min;
    }
    d_left = min_distance(first, middle);
    d_right = min_distance(middle + 1, last);
    d_min = min(d_left, d_right);
    for (int i = first; i <= last; i++)
    {
        if (d_min >= fabs(points[i].x - points[middle].x))
        {
            s[num] = i;
            num++;
        }
    }
    sort(s, s + num, cmp2);
    for (int i = 0; i < num; i++)
    {
        int j = i + 1;
        while (j < num && j < i + 15)
        {
            if (points[s[j]].y - points[s[i]].y < d_min)
            {
                d_min = min(d_min, distance(s[i], s[j]));
            }
            j++;
        }
    }
    return d_min;
}
int main()
{
    cout << setiosflags(ios::fixed) << setprecision(2);
    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> points[i].x >> points[i].y;
    }
    sort(points, points + n, cmp1);
    cout << min_distance(0, n - 1) << endl;
    return 0;
}