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

#define MAXN 100005

int pa[MAXN]; // parant
int rk[MAXN]; // rank

void init(int n)
{
    for (int i = 1; i <= n; ++i)
    {
        pa[i] = i;
        rk[i] = 1;
    }
}

int find(int x)
{
    if (pa[x] == x)
        return x;
    else
    {
        // reset pa
        pa[x] = find(pa[x]);
        return pa[x];
    }
}

void merge(int x, int y)
{
    if (x == y)
        return;
    int xpa = find(x), ypa = find(y);
    // merge according to rank
    if (rk[xpa] <= rk[ypa])
        pa[xpa] = ypa;
    else
        pa[ypa] = xpa;
    if (rk[xpa] == rk[ypa])
        ++rk[ypa];
}