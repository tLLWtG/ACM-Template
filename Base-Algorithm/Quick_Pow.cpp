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

ll qpow(ll a, ll t, ll mod)
{
    a %= mod;
    ll res = 1;
    while (t)
    {
        if (t & 1)
            res = res * a % mod;
        a = a * a % mod;
        t >>= 1;
    }
    return res;
}

// if mod is a prime number
// t %= (mod - 1);
// a^(t^tt) == a^(t^tt % (mod - 1))