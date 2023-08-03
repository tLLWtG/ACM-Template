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

class DSU
{
public:
    DSU(int _n): n(_n)
    {
        fa.resize(n + 1);
        sz.resize(n + 1);
        for (int i = 1; i <= n; ++i)
        {
            fa[i] = i;
            sz[i] = 1;
        }
    }

    int find(int x)
    {
        if (fa[x] == x)
            return x;
        else
        {
            fa[x] = find(fa[x]);
            return fa[x];
        }
    }

    void merge(int x, int y)
    {
        if (x == y)
            return;
        int xfa = find(x), yfa = find(y);
        if (sz[xfa] <= sz[yfa])
        {
            sz[yfa] += sz[xfa];
            fa[xfa] = yfa;
        }
        else
        {
            sz[xfa] += sz[yfa];
            fa[yfa] = xfa;
        }
    }

    int get_size(int x)
    {
        return sz[find(x)];
    }
private:
    int n;
    vector<int> fa, sz;
};
