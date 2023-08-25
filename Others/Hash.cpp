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

// for unordered_X, e.g. unordered_map<int, int, my_hash>
// link: https://codeforces.com/blog/entry/62393

struct my_hash
{
    static uint64_t splitmix64(uint64_t x)
    {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    size_t operator()(uint64_t x) const
    {
        static const uint64_t FIXED_RANDOM =
            chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }

    size_t operator()(pair<uint64_t, uint64_t> x) const
    {
        static const uint64_t FIXED_RANDOM =
            chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x.first + FIXED_RANDOM) ^
               (splitmix64(x.second + FIXED_RANDOM) >> 1);
    }
};

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

bool cmp(const string &s, const string &t)
{
    return get_hash(s) == get_hash(t);
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

// double hash
// exist when the result of %a and %b is equal
