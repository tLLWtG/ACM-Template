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

// 1.

ll comb(ll n, ll k)
{
    ll res = 1;
    for (ll i = 1; i <= k; ++i)
    {
        res *= n - i + 1;
        res /= i;
        // use inverse if you need modulo
    }
    return res;
}

// 2. O(n)

namespace comb
{
    int n, p;
    vector<int> inv, fac, finv;
    void Preprocess(int _n, int _p)
    {
        n = _n;
        p = _p;
        inv.resize(n + 5);
        fac.resize(n + 5);
        finv.resize(n + 5);
        inv[1] = 1;
        for (int i = 2; i <= n + 1; ++i)
            inv[i] = (ll)(p - p / i) * inv[p % i] % p;
        fac[0] = 1;
        for (int i = 1; i <= n + 1; ++i)
            fac[i] = (ll)fac[i - 1] * i % p;
        finv[0] = 1;
        for (int i = 1; i <= n + 1; ++i)
            finv[i] = (ll)finv[i - 1] * inv[i] % p;
    }
    int C(int x, int y) { return (ll)fac[x] * finv[y] % p * finv[x - y] % p; }
}
// (x)
// (y)

// 3. Yanghui triangle

int c[2005][2005];

void build(int p)
{
    c[1][1] = 1;
    for (int i = 0; i <= 2000; i++)
        c[i][0] = 1;
    for (int i = 2; i <= 2000; i++)
        for (int j = 1; j <= i; j++)
            c[i][j] = (c[i - 1][j] + c[i - 1][j - 1]) % p;
}