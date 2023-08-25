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

class Gauss_Jordan
{
private:
    int n;
    vector<double> ans;
    vector<vector<double>> Mat;

public:
    bool success;

    Gauss_Jordan(int _n, vector<vector<double>> &_Mat) : n(_n), Mat(_Mat), success(true)
    {
        ans.resize(n);
    }
    void solve()
    {
        for (int i = 0; i < n; i++)
        {
            int r = i;
            for (int j = i + 1; j < n; j++)
                if (fabs(Mat[j][i]) > fabs(Mat[r][i]))
                    r = j;
            if (r != i)
                for (int j = 0; j <= n; j++)
                    swap(Mat[r][j], Mat[i][j]);
            if (fabs(Mat[i][i]) < 1e-6)
            {
                success = false;
                return;
            }
            for (int j = n; j >= i; j--)
            {
                for (int k = i + 1; k < n; k++)
                    Mat[k][j] -= Mat[k][i] / Mat[i][i] * Mat[i][j];
            }
        }
        for (int i = n - 1; i >= 0; i--)
        {
            for (int j = i + 1; j < n; j++)
                Mat[i][n] -= Mat[j][n] * Mat[i][j];
            Mat[i][n] /= Mat[i][i];
        }
        for (int i = 0; i < n; ++i)
            ans[i] = Mat[i][n];
    }
    vector<double> &get_ans()
    {
        return ans;
    }
};
