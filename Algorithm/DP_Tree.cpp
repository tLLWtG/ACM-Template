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

// CF 1822F

// max distance

vector<vector<int>> e(2e5 + 5);
vector<ll> dep(2e5 + 5, 0), down(2e5 + 5), up(2e5 + 5);

ll n;

void predfs(int u, int fa)
{
    dep[u] = dep[fa] + 1;
    down[u] = up[u] = 0;
    for (auto &x : e[u])
    {
        if (x == fa)
            continue;
        predfs(x, u);
        down[u] = max(down[u], down[x] + 1);
    }
}

void dfs(int u, int fa)
{
    ll max1 = -n - 1, max2 = -n - 1;
    for (auto &x : e[u])
    {
        if (x == fa)
            continue;
        if (down[x] > max1)
        {
            max2 = max1;
            max1 = down[x];
        }
        else
        {
            max2 = max(max2, down[x]);
        }
    }
    for (auto &x : e[u])
    {
        if (x == fa)
            continue;
        up[x] = max(up[u] + 1, (down[x] == max1 ? (max2 + 2) : (max1 + 2)));
        dfs(x, u);
    }
}

int main()
{
    // clock_t st = clock(), ed;
    ios::sync_with_stdio(0);
    cin.tie(0);
    // cout << setprecision(15) << fixed;
    ll T, n, k, c, u, v;
    dep[0] = -1;
    cin >> T;
    while (T--)
    {
        cin >> n >> k >> c;
        for (int i = 1; i < n; ++i)
        {
            cin >> u >> v;
            e[u].pb(v);
            e[v].pb(u);
        }
        predfs(1, 0);
        ll ans = -1;
        dfs(1, 0);
        for (int i = 1; i <= n; ++i)
            ans = max(ans, k * max(down[i], up[i]) - c * dep[i]);
        cout << ans << endl;
        for (int i = 1; i <= n; i++)
            e[i].clear();
    }
    // ed = clock();
    // double endtime = (double)(ed - st) / CLOCKS_PER_SEC;
    // cout << "Total time: " << endtime << endl;
    return 0;
}
