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

// from luogu

#define MAXN 10005
const ll inf = 1e9;

struct edge
{
    ll v, w, next;
};

struct node
{
    ll dis, id;
    bool operator>(const node &b) const { return dis > b.dis; }
};

vector<edge> e(MAXN);
ll head[5005], vis[5005], t[5005];
ll cnt;
ll h[5005], dis[5005];

void addedge(ll u, ll v, ll w)
{
    e[++cnt].v = v;
    e[cnt].w = w;
    e[cnt].next = head[u];
    head[u] = cnt;
}

bool spfa(ll n, ll s)
{
    queue<ll> q;
    memset(h, 63, sizeof(h));
    h[s] = 0, vis[s] = 1;
    q.push(s);
    while (!q.empty())
    {
        ll u = q.front();
        q.pop();
        vis[u] = 0;
        for (int i = head[u]; i; i = e[i].next)
        {
            ll v = e[i].v;
            if (h[v] > h[u] + e[i].w)
            {
                h[v] = h[u] + e[i].w;
                if (!vis[v])
                {
                    vis[v] = 1;
                    q.push(v);
                    t[v]++;
                    if (t[v] == n + 1)
                        return false;
                }
            }
        }
    }
    return true;
}

void dijkstra(ll n, ll s)
{
    priority_queue<node, vector<node>, greater<node>> q;
    for (int i = 1; i <= n; i++)
        dis[i] = inf;
    memset(vis, 0, sizeof(vis));
    dis[s] = 0;
    q.push({0, s});
    while (!q.empty())
    {
        ll u = q.top().id;
        q.pop();
        if (vis[u])
            continue;
        vis[u] = 1;
        for (int i = head[u]; i; i = e[i].next)
        {
            ll v = e[i].v;
            if (dis[v] > dis[u] + e[i].w)
            {
                dis[v] = dis[u] + e[i].w;
                if (!vis[v])
                    q.push({dis[v], v});
            }
        }
    }
}

int main()
{
    // clock_t st = clock(), ed;
    ios::sync_with_stdio(0);
    cin.tie(0);
    // cout << setprecision(15) << fixed;
    ll n, m;
    cin >> n >> m;
    for (int i = 1; i <= m; i++)
    {
        ll u, v, w;
        cin >> u >> v >> w;
        addedge(u, v, w);
    }
    for (int i = 1; i <= n; i++)
        addedge(0, i, 0);
    if (!spfa(n, 0))
    {
        cout << -1 << endl;
        return 0;
    }
    for (int u = 1; u <= n; u++)
        for (int i = head[u]; i; i = e[i].next)
            e[i].w += h[u] - h[e[i].v];
    for (int i = 1; i <= n; i++)
    {
        dijkstra(n, i);
        ll ans = 0;
        for (int j = 1; j <= n; j++)
        {
            if (dis[j] == inf)
                ans += j * inf;
            else
                ans += j * (dis[j] + h[j] - h[i]);
        }
        cout << ans << endl;
    }
    // ed = clock();
    // double endtime = (double)(ed - st) / CLOCKS_PER_SEC;
    // cout << "Total time: " << endtime << endl;
    return 0;
}
