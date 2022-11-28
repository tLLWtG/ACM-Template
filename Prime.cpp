#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using pii = pair<int, int>;

#define pb push_back
#define mp make_pair
#define all(x) (x).begin(), (x).end()
#define fi first
#define se second
#define endl '\n'

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
    for (int i = 2; i <= MAXN; i++)
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