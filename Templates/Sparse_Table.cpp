#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using pii = pair<int, int>;

#define pb push_back
#define all(x) (x).begin(), (x).end()
#define fi first
#define se second
#define endl '\n'

/*-------------------------------------------*/

#define MAXN 100005

int arr[MAXN], ST[__lg(MAXN) + 1][MAXN], n;

void init(int n)
{
    for (int i = 1; i <= n; ++i)
        ST[0][i] = arr[i];
    for (int i = 1; i <= __lg(MAXN); ++i)
        for (int j = 1; j + (1 << i) - 1 <= n; ++j)
            ST[i][j] = max(ST[i - 1][j], ST[i - 1][j + (1 << (i - 1))]);
}

int query(int l, int r)
{
    int s = __lg(r - l + 1);
    return max(ST[s][l], ST[s][r - (1 << s) + 1]);
}