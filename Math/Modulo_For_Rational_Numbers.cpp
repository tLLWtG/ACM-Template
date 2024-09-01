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

// a / b

ll exgcd(ll a, ll b, ll &x, ll &y)
{
    if (b == 0)
    {
        x = 1;
        y = 0;
        return a;
    }
    ll d = exgcd(b, a % b, x, y);
    ll t = x;
    x = y;
    y = t - a / b * y;
    return d;
}

ll mod(ll a, ll b, ll p)
{
    ll x, y;
    ll d = exgcd(b, p, x, y);
    x = (x % p + p) % p;
    return x * a % p;
}

// for big numbers

ll getint(ll p)
{
    ll res = 0, ch = getchar();
    while (!isdigit(ch) && ch != EOF)
        ch = getchar();
    while (isdigit(ch))
    {
        res = (res << 3) + (res << 1) + (ch - '0');
        res %= p;
        ch = getchar();
    }
    return res;
}