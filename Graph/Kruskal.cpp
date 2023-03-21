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

struct edge
{
    int u, v, w;
};

bool cmp(edge a, edge b)
{
    return a.w < b.w;
}

vector<edge> e(MAXN);

int fa[MAXN];

void init(int n)
{
    for (int i = 1; i <= n; ++i)
        fa[i] = i;
}

int find(int x)
{
    if (fa[x] == x)
        return x;
    int xfa = find(fa[x]);
    return fa[x] = xfa;
}

void merge(int x, int y)
{
    int xfa = find(x);
    int yfa = find(y);
    fa[xfa] = yfa;
}

void Kruskal(int n, int m)
{
    init(n);
    sort(e.begin() + 1, e.begin() + 1 + m, cmp);
    for (int i = 1; i <= m; ++i)
    {
        if (find(e[i].u) == find(e[i].v))
            continue;
        else
        {
            merge(e[i].u, e[i].v);
            cout << e[i].u << " " << e[i].v << " " << e[i].w << endl;
        }
    }
}