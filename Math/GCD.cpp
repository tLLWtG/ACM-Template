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

// minus, for big numbers

ll gcd1(ll a, ll b)
{
    // if (a == 1 || b == 1)
    //     return 1;
    // if (a == b)
    //     return a;
    // if (a > b)
    //     return gcd(a - b, b);
    // return gcd(a, b - a);
    while (a != b)
    {
        if (a == 1 || b == 1)
            return 1;
        if (a > b)
            a -= b;
        else
            b -= a;
    }
    return a;
}

// Euclid

ll gcd2(ll a, ll b)
{
    while (b != 0)
    {
        ll tmp = a;
        a = b;
        b = tmp % b;
    }
    return a;
}

// Euclid for multiple numbers

ll gcd3(vector<ll> &v)
{
    ll res = v[0];
    for (int i = 1; i < v.size(); i++)
        res = gcd2(res, v[i]);
    return res;
}