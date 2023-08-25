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

// index starts from 0

class Augment_path
{
private:
    int n, m;
    int dfn;
    vector<int> vis;
    vector<vector<int>> g;

    bool dfs(int v)
    {
        vis[v] = dfn;
        for (int u : g[v])
        {
            if (pb[u] == -1)
            {
                pb[u] = v;
                pa[v] = u;
                return true;
            }
        }
        for (int u : g[v])
        {
            if (vis[pb[u]] != dfn && dfs(pb[u]))
            {
                pa[v] = u;
                pb[u] = v;
                return true;
            }
        }
        return false;
    }

public:
    int res;
    vector<int> pa;
    vector<int> pb;

    Augment_path(int _n, int _m) : n(_n), m(_m)
    {
        pa = vector<int>(n, -1);
        pb = vector<int>(m, -1);
        vis = vector<int>(n);
        g.resize(n);
        res = 0;
        dfn = 0;
    }

    // only add n -> m
    void add(int from, int to)
    {
        g[from].push_back(to);
    }

    int solve()
    {
        while (true)
        {
            dfn++;
            int cnt = 0;
            for (int i = 0; i < n; i++)
                if (pa[i] == -1 && dfs(i))
                    cnt++;

            if (cnt == 0)
                break;
            res += cnt;
        }
        return res;
    }
};
