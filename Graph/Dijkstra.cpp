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

class Dij
{
public:
    Dij(int _n): n(_n)
    {
        e.resize(n + 5);
        dis.resize(n + 5, 0x3f3f3f3f);
        vis.resize(n + 5, 0);
    }

    struct edge
    {
        int v, w;
    };
    struct node
    {
        int dis, u;
        bool operator>(const node &b) const { return dis > b.dis; }
    };
    vector<vector<edge>> e;
    vector<int> dis, vis;
    priority_queue<node, vector<node>, greater<node>> q;

    void dij(int s)
    {
        dis[s] = 0;
        q.push({0, s});
        while (!q.empty())
        {
            int u = q.top().u;
            q.pop();
            if (vis[u])
                continue;
            vis[u] = 1;
            for (auto x : e[u])
            {
                int v = x.v, w = x.w;
                if (dis[v] > dis[u] + w)
                {
                    dis[v] = dis[u] + w;
                    q.push({dis[v], v});
                }
            }
        }
    }

private:
    int n;
};

// m >> n

class Dij_2
{
public:
    Dij_2(int _n): n(_n)
    {
        e.resize(n + 5);
        dis.resize(n + 5, 0x3f3f3f3f);
        vis.resize(n + 5, 0);
    }

    struct edge
    {
        int v, w;
    };
    struct node
    {
        int dis, u;
        bool operator>(const node &b) const { return dis > b.dis; }
    };
    vector<vector<edge>> e;
    vector<int> dis, vis;

    void dij2(int s)
    {
        dis.resize(n + 5, 0x3f3f3f3f);
        dis[s] = 0;
        for (int i = 1; i <= n; i++)
        {
            int u = 0, mind = 0x3f3f3f3f;
            for (int j = 1; j <= n; j++)
                if (!vis[j] && dis[j] < mind)
                    u = j, mind = dis[j];
            vis[u] = 1;
            for (auto x : e[u])
            {
                int v = x.v, w = x.w;
                if (dis[v] > dis[u] + w)
                    dis[v] = dis[u] + w;
            }
        }
    }

private:
    int n;
};




