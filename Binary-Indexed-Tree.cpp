#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using pii = pair<int, int>;

#define pb push_back
#define mp make_pair
#define all(x) (x).begin(), (x).end()
#define fi first
#define se second
#define endl '\n'

/*-------------------------------------------*/

// 前缀和版本
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
ll query(ll a, ll b)
{
    return query(b) - query(a);
}