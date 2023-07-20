/*
Description

经过选拔，你成功进入了hws，接下来你分配到了n个工作，我们要求第i个任务必须在第i个时刻完成，
对于你的工作我们可以认为工作一瞬间就能完成，但是对于第i个音符你需要准备
个单位时间，那么如果你选择完成第i个工作，那么你就没办法完成所有完成时刻在 )的工作，
 为了尽可能地获得更高的效益，对于每个工作你计算了这个工作的性价比，
 一个工作的性价比为这个工作得到的收益除以完成它需要的准备时间

你并不指望全部完成所有工作，但是你希望尽可能地最大化工作收益

Input
第一行一个正整数n
第二行n个正整数，第i个正整数表示
第三行n个正整数，第i个正整数表示第i个工作的性价比

Output
一行一个正整数，表示你可能达到的最大收益
*/

#include <bits/stdc++.h>
using namespace std;

int main(){
    int n;
    cin >> n;
    vector<int> t(n);
    vector<int> p(n);
    vector<int> profit(n);
    for (int i = 0; i < n; i++) cin >> t[i];
    for (int i = 0; i < n; i++) {
        cin >> p[i];
        profit[i] = p[i] * t[i];
    }
    int ans = 0;
    vector<int> dp(n);
    for (int i = 0; i < n; i++) {
        dp[i] = profit[i];
        for (int j = 0; j < i; j++) {
            if (t[i] >= t[j]) {
                dp[i] = max(dp[i], dp[j] + profit[i]);
            }
        }
        ans = max(ans, dp[i]);
    }
    cout << ans << endl;
}