#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

int threeSumClosest(vector<int>& nums, int target) {
    sort(nums.begin(), nums.end());
    int j;
    int k;
    int ans = 0;
    int m = INT_MAX;
    for (int i = 0; i < nums.size() - 2; i++)
    {
        j = i + 1;
        k = nums.size() - 1;
        while (j < k)
        {
            int tmp = nums[i] + nums[j] + nums[k];
            if (abs(tmp - target) < m) {
                ans = tmp;
                m = abs(tmp - target);
            }
            if (tmp == target) {
                return target;
            }
            else if (tmp < target) {
                j++;
            }
            else if (tmp > target) {
                k--;
            }
        }
    }
    return ans;
}
int main()
{
    vector<int> a = { 0,0,0 };
    cout << threeSumClosest(a, 1) << endl;
    return 0;
}