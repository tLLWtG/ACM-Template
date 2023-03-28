#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using pii = pair<int, int>;

#define eb emplace_back
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

// a * x === 1 (mod b)   =>   a * x + b * y == 1

ll exgcd(ll a, ll b, ll &x, ll &y)
{
    if (!b)
    {
        x = 1;
        y = 0;
        return a;
    }
    ll d = exgcd(b, a % b, x, y);
    ll t = x;
    x = y;
    y = t - (a / b) * y;
    return d;
}

ll inv1(ll a, ll b)
{
    ll x, y;
    ll d = exgcd(a, b, x, y);
    // smallest x
    if (d == 1)
        return (x % b + b) % b;
    return -1;
}

// application:
// ans = (a * b * c) % p;
// to get rid of a
// ans = ans * x % p;

// if b is prime
// according to Fermat's little theorem

ll inv2(ll a, ll b)
{
    ll ans = 1;
    b -= 2;
    while (b)
    {
        if (b & 1)
            ans = (a * ans) % b;
        a = (a * a) % b;
    }
    return ans;
}