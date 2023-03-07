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

// prefix sum version
// also able to update range with difference

#define MAXN 100005

ll tree[MAXN];

ll lowbit(ll x)
{
    return x & (-x);
}

void update(ll index, ll x)
{
    for (ll pos = index; pos < MAXN; pos += lowbit(pos))
        tree[pos] += x;
}
ll query(ll n)
{
    ll sum = 0;
    for (ll i = n; i; i -= lowbit(i))
        sum += tree[i];
    return sum;
}

// (a, b]
ll query(ll a, ll b)
{
    return query(b) - query(a);
}