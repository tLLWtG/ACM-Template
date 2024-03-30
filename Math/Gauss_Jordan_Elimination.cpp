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

// 0: OK
// 1: Infinite group solutions
// 2: No solution

const double eps = 1e-6;

int Guass(int n, vector<vector<double>> &mat)
{
    int r = 1, c = 1;
    for (; c <= n; ++c)
    {
        int maxi = r;
        for (int i = r; i <= n; ++i)
            if (fabs(mat[i][c]) > fabs(mat[maxi][c]))
                maxi = i;
        if (fabs(mat[maxi][c]) < eps)
            continue;
        for (int j = c; j <= n + 1; ++j)
            swap(mat[r][j], mat[maxi][j]);
        for (int j = n + 1; j >= c; --j)
            mat[r][j] /= mat[r][c];
        for (int i = r + 1; i <= n; ++i)
            if (fabs(mat[i][c]) > eps)
                for (int j = n + 1; j >= c; --j)
                    mat[i][j] -= mat[i][c] * mat[r][j];
        ++r;
    }
    if (r <= n)
    {
        for (int i = r; i <= n; ++i)
            if (fabs(mat[i][n + 1]) > eps)
                return 2;
        return 1;
    }
    for (int i = n - 1; i >= 1; --i)
        for (int j = i + 1; j <= n; ++j)
            mat[i][n + 1] -= mat[i][j] * mat[j][n + 1];
    return 0;
}
