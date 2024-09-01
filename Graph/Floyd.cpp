#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using pii = pair<int, int>;

#define pb push_back
#define all(x) (x).begin(), (x).end()
#define fi first
#define se second
#define endl '\n'
#define debug(x) { cerr << #x << " = " << x << endl; }

/*-------------------------------------------*/

#define MAXN 10005

struct edge
{
    int v, w;
};

vector<vector<edge>> e(MAXN);
int dp[MAXN][MAXN];

void Floyd(int n)
{
    memset(dp, 0x3f, sizeof(dp));
    for (int i = 1; i <= n; ++i)
        dp[i][i] = 0;
    for (int i = 1; i <= n; ++i)
        for (auto &x : e[i])
            dp[i][x.v] = x.w;
    for (int k = 1; k <= n; ++k)
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= n; ++j)
                dp[i][j] = min(dp[i][j], dp[i][k] + dp[k][j]);
}