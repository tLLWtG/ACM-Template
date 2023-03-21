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

// luogu P1352

int dp[10005][2], isnhead[10005], vis[10005];

vector<vector<int>> v(10005);

void dfs(int x)
{
    vis[x] = 1;
    for (auto &vv : v[x])
    {
        if (vis[vv])
            continue;
        dfs(vv);
        dp[x][1] += dp[vv][0];
        dp[x][0] += max(dp[vv][0], dp[vv][1]);
    }
}

void dp_tree()
{
    int n, x, y;
    cin >> n;
    for (int i = 1; i <= n; ++i)
        cin >> dp[i][1];
    for (int i = 1; i <= n - 1; ++i)
    {
        cin >> y >> x;
        v[x].pb(y);
        isnhead[y] = 1;
    }
    for (int i = 1; i <= n; ++i)
    {
        if (!isnhead[i])
        {
            dfs(i);
            cout << max(dp[i][0], dp[i][1]) << endl;
            break;
        }
    }
}

// P3478 preprocess tree dp

vector<vector<ll>> v2(1e6 + 5);

vector<ll> dp2(1e6 + 5, 0), sz2(1e6 + 5, 0), dep2(1e6 + 5, 0);
ll n, x, y;
void dfs1(int u, int fa)
{
    dep2[u] = dep2[fa] + 1;
    sz2[u] = 1;
    for (auto &x : v[u])
    {
        if (x == fa)
            continue;
        dfs1(x, u);
        sz2[u] += sz2[x];
    }
}

void dfs2(int u, int fa)
{
    for (auto &x : v[u])
    {
        if (x == fa)
            continue;
        dp2[x] = dp2[u] + n - 2 * sz2[x];
        dfs2(x, u);
    }
}

void dp_tree2()
{
    cin >> n;
    for (int i = 1; i <= n - 1; ++i)
    {
        cin >> x >> y;
        v[x].pb(y);
        v[y].pb(x);
    }
    dfs1(1, 1);
    ll ans = -1e9, id = -1;
    for (int i = 1; i <= n; ++i)
        dp2[1] += dep2[i];
    dfs2(1, 1);

    for (int i = 1; i <= n; ++i)
        if (dp2[i] > ans)
        {
            ans = dp2[i];
            id = i;
        }
    cout << id << endl;
}