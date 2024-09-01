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

// x == m1 (mod a1)
// x == m2 (mod a2)
// ...

ll exgcd(ll a, ll b, ll &x, ll &y)
{
    if (b == 0)
    {
        x = 1, y = 0;
        return a;
    }
    ll d= exgcd(b, a % b, y, x);
    y -= a / b * x;
    return d;
}

// a1, a2, a3 ... 保证互质

void CRT()
{
    ll n, M = 1, ans = 0;
    cin >> n;
    vector<ll> arr(n + 1), mrr(n + 1);
    for (int i = 1; i <= n; ++i)
    {
        cin >> arr[i] >> mrr[i];
        M *= arr[i];
    }
    for (int i = 1; i <= n; ++i)
    {
        ll Mi = M / arr[i], x, y;
        ll d = exgcd(Mi, arr[i], x, y);
        ans = (ans + mrr[i] * Mi % M * x) % M;
    }
    cout << (ans % M + M) % M << endl;
}

// a1, a2, a3 ... 不保证互质

void exCRT()
{
    int n;
    cin >> n;
    ll a1, m1, a2, m2, k1, k2;
    cin >> a1 >> m1;
    for (int i = 1; i < n; ++i)
    {
        cin >> a2 >> m2;
        ll d = exgcd(a1, a2, k1, k2);
        if ((m2 - m1) % d)
        {
            cout << -1 << endl;
            return;
        }
        k1 *= (m2 - m1) / d;
        ll t = a2 / d;
        k1 = (k1 % t + t) % t;
        m1 = a1 * k1 + m1;
        a1 = a1 / d * a2;
    }
    cout << (m1 % a1 + a1) % a1 << endl;
}