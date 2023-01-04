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

int arr[MAXN], k;
deque<int> q;

void func()
{
    for (int i = 1; i <= MAXN; ++i)
    {
        if (!q.empty() && i - q.front() >= k)
            q.pop_front();
        while (!q.empty() && arr[q.back()] < arr[i])
            q.pop_back();
        q.push_back(i);
        if (i >= k)
            cout << q.front() << endl;
    }
}