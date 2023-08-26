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

int arr[MAXN];
int ans[MAXN];
stack<int> st;

void func()
{
    for (int i = 1; i <= MAXN; ++i)
    {
        while (!st.empty() && arr[i] > arr[st.top()])
        {
            ans[st.top()] = i;
            st.pop();
        }
        st.push(i);
    }
}
