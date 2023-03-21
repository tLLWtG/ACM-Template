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

#define MAXN 100005

vector<vector<int>> v(MAXN);

int fa[MAXN][31], dep[MAXN];

int n, m, a, b, c;

// Binary Lifting

void dfs(int cur, int fanode)
{
    fa[cur][0] = fanode;
    dep[cur] = dep[fanode] + 1;
    for (int i = 1; i < 31; ++i)
        fa[cur][i] = fa[fa[cur][i - 1]][i - 1];
    for (int i = 0; i < v[cur].size(); ++i)
    {
        if (v[cur][i] == fanode)
            continue;
        dfs(v[cur][i], cur);
    }
}

int lca(int x, int y)
{
    if (dep[x] > dep[y])
        swap(x, y);
    int tmp = dep[y] - dep[x];
    for (int j = 0; tmp; ++j, tmp >>= 1)
        if (tmp & 1)
            y = fa[y][j];
    if (y == x)
        return x;
    for (int j = 30; j >= 0 && y != x; --j)
    {
        if (fa[x][j] != fa[y][j])
        {
            x = fa[x][j];
            y = fa[y][j];
        }
    }
    return fa[x][0];
}