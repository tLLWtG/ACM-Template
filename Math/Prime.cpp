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

// 1. the Sieve of Eratosthenes

#define MAXN 100005

vector<bool> nop(MAXN, false);

void init1()
{
    nop[0] = true;
    nop[1] = true;
    for (int i = 2; i * i < MAXN; ++i)
    {
        if (!nop[i])
        {
            for (int j = i * i; j < MAXN; j += i)
                nop[j] = true;
        }
    }
}

// 2. Euler sieve

bool isnp[MAXN];
vector<int> primes;
void init2()
{
    isnp[0] = isnp[1] = 1;
    for (int i = 2; i < MAXN; i++)
    {
        if (!isnp[i])
            primes.push_back(i);
        for (int p : primes)
        {
            if (p * i > MAXN)
                break;
            isnp[p * i] = 1;
            if (i % p == 0)
                break;
        }
    }
}

// 3. Deterministic Miller–Rabin primality test

// for 1 ~ (1 << 64)

namespace millerRabin
{
    ll qpow(ll a, ll t, ll mod)
    {
        a %= mod;
        ll res = 1;
        while (t)
        {
            if (t & 1)
                res = (__int128)res * a % mod;
            a = (__int128)a * a % mod;
            t >>= 1;
        }
        return res;
    }

    const int primebook[12] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};

    bool isPrime(ll n)
    {
        if (n < 3 || n % 2 == 0)
            return n == 2;
        if (n <= 40)
        {
            for (ll a : primebook)
                if (a == n)
                    return 1;
            return 0;
        }
        ll u = n - 1, t = 0;
        while (u % 2 == 0)
            u /= 2, ++t;
        for (ll a : primebook)
        {
            ll v = qpow(a, u, n);
            if (v == 1)
                continue;
            ll s;
            for (s = 0; s < t; ++s)
            {
                if (v == n - 1)
                    break;
                v = (__int128)v * v % n;
            }
            if (s == t)
                return 0;
        }
        return 1;
    }
}

// prime factorization

void prime_factor(int x)
{
    for (int i = 2; i <= x / i; ++i)
    {
        while (x % i == 0)
        {
            // do sth.
            x /= i;
        }
    }
    if (x > 1)
    {
        // do sth.
    }
}