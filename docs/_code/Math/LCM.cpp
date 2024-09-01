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

// lcm

ll lcm1(ll a, ll b)
{
    return a / gcd(a, b) * b;
}

// lcm for multiple numbers

ll lcm2(vector<ll> a)
{
    ll res = 1;
    for (auto x : a)
        res = lcm1(res, x);
    return res;
}
