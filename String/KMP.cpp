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

class KMP
{
private:
    vector<int> pmt;
    string p;

public:
    KMP(const string &_p) : p(_p)
    {
        pmt.resize(p.length() + 5, 0);
        for (int i = 1, j = 0; i < p.length(); ++i)
        {
            while (j && p[i] != p[j])
                j = pmt[j - 1];
            if (p[i] == p[j])
                j++;
            pmt[i] = j;
        }
    }
    void find(const string &s)
    {
        for (int i = 0, j = 0; i < s.length(); ++i)
        {
            while (j && s[i] != p[j])
                j = pmt[j - 1];
            if (s[i] == p[j])
                j++;
            if (j == p.length())
            {
                cout << i - j + 2 << endl;
                j = pmt[j - 1];
            }
        }
    }
};