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
#define MAXN 100005

int pa[MAXN]; // 父母
int rk[MAXN]; // 秩

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
        //路径压缩
        pa[x] = find(pa[x]);
        return pa[x];
    }
}

void merge(int x, int y)
{
    if (x == y)
        return;
    int xpa = find(x), ypa = find(y);
    //按秩合并
    if (rk[x] <= rk[y])
        pa[x] = ypa;
    else
        pa[y] = xpa;
    if (rk[x] == rk[y])
        ++rk[y];
}