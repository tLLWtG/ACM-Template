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

// index starts from 1: s, p

namespace KMP
{
    const int N = 100010, M = 1000010;

    int n, m;
    int ne[N];
    char s[M], p[N];

    void get_next()
    {
        for (int i = 2, j = 0; i <= n; ++i)
        {
            while (j && p[i] != p[j + 1])
                j = ne[j];
            if (p[i] == p[j + 1])
                ++j;
            ne[i] = j;
        }
    }

    void match()
    {
        for (int i = 1, j = 0; i <= m; ++i)
        {
            while (j && s[i] != p[j + 1])
                j = ne[j];
            if (s[i] == p[j + 1])
                ++j;
            if (j == n)
            {
                printf("%d ", i - n);
                j = ne[j];
            }
        }
    }
}
