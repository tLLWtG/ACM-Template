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

int Euler_phi(int n)
{
    ll ans = n;
    for (ll i = 2; i * i <= n; ++i)
        if (n % i == 0)
        {
            ans = ans / i * (i - 1);
            while (n % i == 0)
                n /= i;
        }
    if (n > 1)
        ans = ans / n * (n - 1);
    return ans;
}


vector<int> primes, phi;
vector<bool> nop;
void Euler(int n)
{
    phi.resize(n + 10, 0);
    nop.resize(n + 10, 0);
    phi[1] = 1;
    for (int i = 2; i <= n; ++i)
    {
        if (!nop[i])
        {
            primes.pb(i);
            phi[i] = i - 1;
        }
        for (auto x: primes)
        {
            if (x * i > n)
                break;
            nop[i * x] = true;
            if (i % x == 0)
            {
                phi[i * x] = phi[i] * x;
                break;
            }
            phi[i * x] = phi[i] * (x - 1);
        }
    }
}
