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

// string hash

const int M = 1e9 + 7;
const int B = 233;

int get_hash(const string &s)
{
    int res = s[0], sz = s.size();
    for (int i = 1; i < sz; ++i)
        res = (ll(res) * B + s[i]) % M;
    return res;
}

// double hash

const int mod1 = 19260817;
const int mod2 = 1e9 + 7;

pii get_hash(string &s)
{
    ll r1 = 0, r2 = 0;
    for (int i = 0; i < s.size(); ++i)
    {
        r1 = (r1 * 131 + s[i]) % mod1;
        r2 = (r2 * 233 + s[i]) % mod2;
    }
    return {r1, r2};
}

// substring hash(with prefix)

const int N = 1e5 + 5, P = 133;
unsigned long long h[N], p[N];

unsigned long long query(int l, int r)
{
    return h[r] - h[l - 1] * p[r - l + 1];
}

void prepro(string &str)
{
    // index start from 1
    p[0] = 1;
    h[0] = 0;
    int sz = str.size();
    for (int i = 0; i < sz; i++)
    {
        p[i + 1] = p[i] * P;
        h[i + 1] = h[i] * P + str[i];
    }
}
