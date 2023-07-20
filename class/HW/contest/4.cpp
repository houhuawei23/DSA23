#include <iostream>
#include <vector>

using namespace std;

const int MOD = 1000000007;

int main() {
    int n;
    cin >> n;

    vector<vector<int>> grid(3, vector<int>(n));
    for (int i = 0; i < 3; i++) {
        string line;
        cin >> line;
        for (int j = 0; j < n; j++) {
            if (line[j] == 'o') {
                grid[i][j] = 0;
            }
            else {
                grid[i][j] = 1;
            }
        }
    }
    // // print
    // for (int i = 0; i < 3; i++) {
    //     for (int j = 0; j < n; j++) {
    //         cout << grid[i][j] << " ";
    //     }
    //     cout << endl;
    // }

    vector<vector<int>> dp(3, vector<int>(n, 0));

    for (int i = 2; i >= 0; i--) {
        for (int j = 0; j < n; j++) {
            if (grid[i][j] == 0) {
                if (i == 2) {
                    dp[i][j] = 1;
                }
                else {
                    for (int k = 0; k < n; k++) {
                        if (grid[i + 1][k] == 0) {
                            dp[i][j] = (dp[i][j] + dp[i + 1][k]) % MOD;
                        }
                    }
                }
            }
        }
    }

    int ans = 0;
    for (int j = 0; j < n; j++) {
        ans = (ans + dp[0][j]) % MOD;
    }

    cout << ans << endl;

    return 0;
}
