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

// Min Version

double f(double x) {}
int run(int x) {}

double ternary_search()
{
    const double eps = 1e-6;
    double l, r, mid, lmid, rmid;
    while (r - l > eps)
    {
        mid = (lmid + rmid) / 2;
        lmid = mid - eps;
        rmid = mid + eps;
        if (f(lmid) < f(rmid))
            r = mid; // inaccuracy but ok
        else
            l = mid;
    }
    return l; // ?
}

int ternary_ans()
{
    int l = 0, r = 1e8, mid;
    int ans = 1e9;
    while (l + 1 < r)
    {
        mid = (l + r) / 2;
        int a1 = run(mid - 1), a2 = run(mid + 1);
        if (a1 > a2)
            ans = min(ans, a1), l = mid;
        else
            ans = min(ans, a2), r = mid;
    }
    ans = min(ans, run(l));
    ans = min(ans, run(r));
    return ans;
}