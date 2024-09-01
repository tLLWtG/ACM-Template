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

// nD Prefix Sum

// 1. with Principle of inclusion-exclusion

// s[i]=a[i]+s[i−1]
// s[i][j]=a[i][j]+s[i−1][j]+s[i][j−1]−s[i−1][j−1]
// s[i][j][k]=a[i][j][k]+s[i−1][j][k]+s[i][j−1][k]+s[i][j][k−1]−s[i−1][j−1][k]−s[i−1][j][k−1]−s[i][j−1][j−1]+s[i−1][j−1][k−1]
// ......

// 2. DP
#define MAXN 1005

void prefix_2D()
{
    int a[MAXN][MAXN], n, m;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
            a[i][j] = a[i][j] + a[i][j - 1];
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
            a[i][j] = a[i][j] + a[i - 1][j];
}

void prefix_3D()
{
    int a[MAXN][MAXN][MAXN], n, m, p;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
            for (int k = 1; k <= p; ++k)
                a[i][j][k] += a[i - 1][j][k];
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
            for (int k = 1; k <= p; ++k)
                a[i][j][k] += a[i][j - 1][k];
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
            for (int k = 1; k <= p; ++k)
                a[i][j][k] += a[i][j][k - 1];
}