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

ll inv(ll a, ll b)
{
    ll x = 1, y = 0, mod = b;
    while (b)
    {
        ll t = a / b;
        a -= t * b;
        x -= t * y;
        swap(a, b);
        swap(x, y);
    }
    return (x % mod + mod) % mod;
}

ll CRT(int k, const vector<ll> &arr, const vector<ll> &nrr)
{
    ll n = 1, ans = 0;
    for (int i = 0; i < k; ++i)
        n *= nrr[i];
    for (int i = 0; i < k; ++i)
    {
        ll m = n / nrr[i];
        ans = (ans + arr[i] * m % n * inv(m, nrr[i])) % n;
    }
    return (ans % n + n) % n;
}