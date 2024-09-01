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

// 矩阵快速幂
namespace MatPow
{
    const ll N = 105, MOD = 1e9 + 7;
    int n = 10;

    struct Mat
    {
        ll v[N][N];
    };

    Mat operator *(const Mat &x, const Mat &y)
    {
        Mat ans;
        ll tmp = 0;
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
            {
                tmp = 0;
                for (int k = 0; k < n; ++k)
                    tmp += x.v[i][k] * y.v[k][j] % MOD;
                ans.v[i][j] = tmp % MOD;
            }
        return ans;
    }

    Mat qpow(Mat a, ll k)
    {
        Mat res;
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                res.v[i][j] = 0;
        for (int i = 0; i < n; ++i)
            res.v[i][i] = 1;

        while(k)
        {
            if (k & 1)
                res = res * a;
            a = a * a;
            k >>= 1;
        }
        return res;
    }
}
