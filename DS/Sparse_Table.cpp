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

class ST
{
private:
    int n, MAXN;
    vector<vector<int>> stable;

public:
    vector<int> arr;
    ST(int _n) : n(_n), MAXN(_n + 5)
    {
        arr.resize(MAXN);
        stable = vector<vector<int>>(__lg(MAXN) + 1, vector<int>(MAXN));
    }
    void init()
    {
        for (int i = 1; i <= n; ++i)
            stable[0][i] = arr[i];
        for (int i = 1; i <= __lg(MAXN); ++i)
            for (int j = 1; j + (1 << i) - 1 <= n; ++j)
                stable[i][j] = max(stable[i - 1][j], stable[i - 1][j + (1 << (i - 1))]);
    }
    int query(int l, int r)
    {
        int s = __lg(r - l + 1);
        return max(stable[s][l], stable[s][r - (1 << s) + 1]);
    }
};