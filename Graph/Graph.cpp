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

//

struct edge
{
    int v, w;
};

vector<vector<edge>> e1(MAXN);

//

int e2[MAXN][MAXN];

// star

int n, m, cnt = 0;

struct Edge
{
    int to;
    int w;
    int nxt;
};

vector<Edge> e(m * 2 + 10);
vector<int> head(n + 1, 0);

function<void(int u, int v, int w)> add = [&](int u, int v, int w)
{
    ++cnt;
    e[cnt].to = v;
    e[cnt].w = w;
    e[cnt].nxt = head[u];
    head[u] = cnt;
}; 

bool find_edge(int u, int v)
{
    for (int eg = head[u]; eg; eg = e[eg].nxt)
        if (e[eg].to == v)
            return true;
    return false;
}
