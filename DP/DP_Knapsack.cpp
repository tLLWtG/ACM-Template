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

#define MAXN 1005

int dp[MAXN], v[MAXN], w[MAXN], W;

// 1. 01

void dp1(int n)
{
    for (int i = 1; i <= n; ++i)
        for (int j = W; j >= w[i]; --j)
            dp[j] = max(dp[j], dp[j - w[i]] + v[i]);
}

// 2. inf

void dp2(int n)
{
    for (int i = 1; i <= n; ++i)
        for (int j = w[i]; j <= W; ++j)
            dp[j] = max(dp[j], dp[j - w[i]] + v[i]);
}

// 3. n kinds but k things

void dp3(int m)
{
    // preprocess
    int index = 0;
    for (int i = 1; i <= m; i++)
    {
        int c = 1, p, h, k;
        cin >> p >> h >> k;
        while (k > c)
        {
            k -= c;
            w[++index] = c * p;
            v[index] = c * h;
            c *= 2;
        }
        w[++index] = p * k;
        v[index] = h * k;
    }
    for (int i = 1; i <= index; ++i)
        for (int j = W; j >= w[i]; --j)
            dp[j] = max(dp[j], dp[j - w[i]] + v[i]);
}

// 4. combined
// if ... else if ... else ...

// 5. 2 dimensions

int dpdp[MAXN][MAXN], c[MAXN], C;

void dp5(int n)
{
    for (int i = 1; i <= n; ++i)
        for (int j = W; j >= w[i]; --j)
            for (int k = C; k >= c[i]; --k)
                dpdp[j][k] = max(dpdp[j][k], dpdp[j - w[i]][k - c[i]] + w[i]);
}

// 6. groups

int t[MAXN][MAXN], cnt[MAXN], tsz;

void dp6(int n)
{
    for (int k = 1; k <= tsz; ++k)
        for (int j = W; j >= 0; --j)
            for (int i = 1; i <= cnt[k]; ++i)
                if (j >= w[t[k][j]])
                    dp[j] = max(dp[j], dp[j - w[t[k][i]]] + v[t[k][i]]);
}

// record for 01
// int g[MAXN][MAXN] 0 for fi, 1 for se
// int w = W;
// loop from last to first
// if choose, w -= w[i]; and record  that

// 可行性 01 背包问题可以用 bitset 优化
// bitset<MAXN> dp;
// dp[0] = 1;
// dp |= dp << v[i];
// if (dp.test[v[i]]) ...
// example: v[1] = 2, v[2] = 3
// 00000001
// 00000101
// 00101101