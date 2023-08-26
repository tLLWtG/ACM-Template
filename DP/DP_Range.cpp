#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using pii = pair<int, int>;

#define pb push_back
#define all(x) (x).begin(), (x).end()
#define fi first
#define se second
#define endl '\n'

#define debug(x)                          \
    {                                     \
        cerr << #x << " = " << x << endl; \
    }
#define debugfull(x)                                                      \
    {                                                                     \
        cerr << #x << " = " << x << " (line " << __LINE__ << ")" << endl; \
    }

/*-------------------------------------------*/

// luogu P1880 (max)

int dp(int n)
{
    vector<int> arr(2 * n + 1), sumi(2 * n + 1, 0);
    vector<vector<int>> dp(2 * n + 1, vector<int>(2 * n + 1, 0));
    for (int i = 1; i <= n; ++i)
        cin >> arr[i], arr[i + n] = arr[i];
    for (int i = 1; i <= 2 * n; ++i)
        sumi[i] = sumi[i - 1] + arr[i];
    for (int len = 1; len <= n; ++len)
        for (int i = 1, j = len + 1; j < 2 * n; ++i, ++j)
            for (int k = i; k < j; ++k)
                dp[i][j] = max(dp[i][j], dp[i][k] + dp[k + 1][j] + sumi[j] - sumi[i - 1]);
    int ans = 0;
    for (int i = 1, j = n; j < 2 * n; ++i, ++j)
        ans = max(ans, dp[i][j]);
    return ans;
}