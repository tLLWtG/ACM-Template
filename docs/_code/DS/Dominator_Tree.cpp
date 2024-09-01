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

// index start from 0
// must be connected gragh

class DomTree
{
public:
    vector<vector<int>> dom;
    vector<int> idom, sz;
    void Build(const vector<vector<int>> &G, int entry)
    {
        int n = G.size(), cnt = 0;
        vector<vector<int>> RG(n), S(n);
        for (int u = 0; u < n; ++u)
        {
            for (auto v : G[u])
                RG[v].pb(u);
        }
        idom.assign(n, 0), dom.assign(n, {}), sz.assign(n, 0);
        vector<int> dfn(n, -1), rev(n), par(n);
        function<void(int)> dfs = [&](int x)
        {
            rev[dfn[x] = cnt++] = x;
            for (int y : G[x])
            {
                if (~dfn[y])
                    continue;
                par[y] = x, dfs(y);
            }
        };
        dfs(entry);
        vector<int> semi(n);
        iota(semi.begin(), semi.end(), 0);
        vector<int> mn(semi), f(semi);
        function<int(int)> merge = [&](int x)
        {
            if (x == f[x])
                return x;
            int t = f[x];
            f[x] = merge(f[x]);
            if (dfn[semi[mn[t]]] < dfn[semi[mn[x]]])
                mn[x] = mn[t];
            return f[x];
        };
        for (int i = n - 1; i; --i)
        {
            int tmp = n, u = rev[i];
            for (int j : RG[rev[i]])
            {
                if (dfn[j] < i)
                    tmp = min(tmp, dfn[j]);
                else
                {
                    merge(j);
                    tmp = min(tmp, dfn[semi[mn[j]]]);
                }
            }
            semi[u] = rev[tmp];
            f[u] = par[u];
            S[semi[u]].pb(u);
            for (int j : S[rev[i - 1]])
            {
                merge(j);
                if (semi[mn[j]] == semi[j])
                    idom[j] = semi[j];
                else
                    idom[j] = mn[j];
            }
        }
        for (auto u : rev)
        {
            if (idom[u] != semi[u])
                idom[u] = idom[idom[u]];
        }
        for (int i = 0; i < n; ++i)
        {
            if (i == entry)
                continue;
            dom[idom[i]].pb(i);
        }
        function<void(int, int)> getsize = [&](int u, int fa)
        {
            sz[u] = 1;
            for (int v : dom[u])
            {
                if (v == fa)
                    continue;
                getsize(v, u);
                sz[u] += sz[v];
            }
        };
        getsize(entry, 0);
    }
};

// only for dag
// index start from 1
// work for forest

namespace DomTree_dag
{
    const int MAX = 65536;
    int n, tot;
    int d[MAX], w[MAX], sz[MAX], p[MAX], f[MAX][17];
    vector<int> e[MAX], g[MAX], h[MAX];
    stack<int> s;
    void topo()
    {
        s.push(0);
        for (int i = 1; i <= n; ++i)
        {
            if (!w[i])
            {
                e[0].pb(i);
                g[i].pb(0);
                ++w[i];
            }
        }
        while (!s.empty())
        {
            int x = s.top();
            s.pop();
            p[++tot] = x;
            for (int i : e[x])
            {
                --w[i];
                if (!w[i])
                {
                    s.push(i);
                }
            }
        }
    }
    int lca(int u, int v)
    {
        if (d[u] < d[v])
        {
            swap(u, v);
        }
        for (int i = 15; i >= 0; --i)
        {
            if (d[f[u][i]] >= d[v])
            {
                u = f[u][i];
            }
        }
        if (u == v)
        {
            return u;
        }
        for (int i = 15; i >= 0; --i)
        {
            if (f[u][i] != f[v][i])
            {
                u = f[u][i];
                v = f[v][i];
            }
        }
        return f[u][0];
    }
    void dfs(int x)
    {
        sz[x] = 1;
        for (int i : h[x])
        {
            dfs(i);
            sz[x] += sz[i];
        }
    }
    void build()
    {
        for (int i = 2; i <= n + 1; ++i)
        {
            int x = p[i], y = g[x][0];
            for (int j = 1, q = g[x].size(); j < q; ++j)
            {
                y = lca(y, g[x][j]);
            }
            h[y].pb(x);
            d[x] = d[y] + 1;
            f[x][0] = y;
            for (int i = 1; i <= 15; ++i)
            {
                f[x][i] = f[f[x][i - 1]][i - 1];
            }
        }
    }
    // example

    int main()
    {
        // clock_t st = clock(), ed;
        ios::sync_with_stdio(0);
        cin.tie(0);
        // cout << setprecision(15) << fixed;
        int n, x;
        cin >> n;
        DomTree_dag::n = n;
        for (int i = 1; i <= n; ++i)
        {
            while (true)
            {
                cin >> x;
                if (!x)
                {
                    break;
                }
                DomTree_dag::e[x].pb(i);
                DomTree_dag::g[i].pb(x);
                ++DomTree_dag::w[i];
            }
        }
        DomTree_dag::topo();
        DomTree_dag::build();
        DomTree_dag::dfs(0);
        for (int i = 1; i <= n; ++i)
            cout << DomTree_dag::sz[i] - 1 << endl;
        // ed = clock();
        // double endtime = (double)(ed - st) / CLOCKS_PER_SEC;
        // cout << "Total time: " << endtime << endl;
        return 0;
    }
}