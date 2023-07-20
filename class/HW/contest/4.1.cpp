#include <iostream>
#include <vector>

using namespace std;

const int MOD = 1000000007;

int main() {
    int n;
    cin >> n;

    vector<vector<int>> dp(4, vector<int>(n+1, 0));

    // 读取lws的势力状态
    vector<string> lws(3);
    for (int i = 0; i < 3; i++) {
        cin >> lws[i];
    }

    // 初始化边界条件
    dp[0][1] = 1;

    // 动态规划计算
    for (int i = 1; i <= 3; i++) {
        for (int j = 1; j <= n; j++) {
            if (lws[i-1][j-1] == 'o') {
                dp[i][j] = (dp[i-1][j] + dp[i][j-1]) % MOD;
            }
        }
    }

    cout << dp[3][n] << endl;

    return 0;
}
