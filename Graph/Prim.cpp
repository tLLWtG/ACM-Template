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

int k, n, m, cnt, sum, ai, bi, ci, head[MAXN], dis[MAXN], vis[MAXN];

struct Edge
{
    int v, w, next;
} e[MAXN];

void add(int u, int v, int w)
{
    e[++k].v = v;
    e[k].w = w;
    e[k].next = head[u];
    head[u] = k;
}

priority_queue<pii, vector<pii>, greater<pii>> q;

void prim()
{
    memset(dis, 127, sizeof(dis));
    memset(head, -1, sizeof(head));
    cin >> n >> m;
    for (int i = 1; i <= m; ++i)
    {
        cin >> ai >> bi >> ci;
        add(ai, bi, ci);
        add(bi, ai, ci);
    }
    dis[1] = 0;
    q.push(make_pair(0, 1));
    while (!q.empty() && cnt < n)
    {
        int d = q.top().first, u = q.top().second;
        q.pop();
        if (vis[u])
            continue;
        ++cnt;
        sum += d;
        vis[u] = 1;
        for (int i = head[u]; i != -1; i = e[i].next)
            if (e[i].w < dis[e[i].v])
                dis[e[i].v] = e[i].w, q.push(make_pair(dis[e[i].v], e[i].v));
    }
    cout << sum << endl;
}
