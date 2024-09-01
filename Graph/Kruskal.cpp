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

class DSU
{
private:
    int n;
    vector<int> fa, sz;

public:
    DSU(int _n) : n(_n)
    {
        fa.resize(n + 1);
        sz.resize(n + 1);
        for (int i = 1; i <= n; ++i)
        {
            fa[i] = i;
            sz[i] = 1;
        }
    }
    int find(int x)
    {
        if (fa[x] == x)
            return x;
        else
        {
            fa[x] = find(fa[x]);
            return fa[x];
        }
    }
    void merge(int x, int y)
    {
        int xfa = find(x), yfa = find(y);
        if (xfa == yfa)
            return;
        if (sz[xfa] <= sz[yfa])
        {
            sz[yfa] += sz[xfa];
            fa[xfa] = yfa;
        }
        else
        {
            sz[xfa] += sz[yfa];
            fa[yfa] = xfa;
        }
    }
    int get_size(int x)
    {
        return sz[find(x)];
    }
};

class Kruskal
{
private:
    int n, m;
    DSU dsu;

public:
    struct edge
    {
        int u, v, w;
    };
    static bool cmp(edge a, edge b)
    {
        return a.w < b.w;
    }
    vector<edge> e;
    Kruskal(int _n, int _m) : n(_n), m(_m), dsu(_n)
    {
        e.resize(m + 5);
    }
    void solve()
    {
        sort(e.begin() + 1, e.begin() + 1 + m, cmp);
        for (int i = 1; i <= m; ++i)
        {
            if (dsu.find(e[i].u) == dsu.find(e[i].v))
                continue;
            else
            {
                dsu.merge(e[i].u, e[i].v);
                cout << e[i].u << " " << e[i].v << " " << e[i].w << endl;
            }
        }
    }
};