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

// index starts from 1
// only save oriented graph

// match: n2 part to n1 part

void solve()
{
    const int maxn = 505;
    int n1, n2, m, u, v, ans = 0;
    cin >> n1 >> n2 >> m;
    vector<vector<int>> to(maxn);
    vector<int> match(maxn, 0), st(maxn, 0);
    for (int i = 1; i <= m; ++i)
    {
        cin >> u >> v;
        to[u].pb(v);
    }
    function<bool(int x)> find = [&](int x)->bool
    {
        for (auto v: to[x])
        {
            if (st[v])
                continue;
            st[v] = true;
            if (match[v] == 0 || find(match[v]))
            {
                match[v] = x;
                return true;
            }
        }
        return false;
    };
    for (int i = 1; i <= n1; ++i)
    {
        fill(all(st), 0);
        if (find(i))
            ++ans;
    }
    cout << ans << endl;
}