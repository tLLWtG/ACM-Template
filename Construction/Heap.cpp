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

// 1. normal heap

class heap
{
private:
    vector<int> h;
    void up(int pos)
    {
        while (pos > 1)
        {
            if (h[pos >> 1] < h[pos])
            {
                swap(h[pos >> 1], h[pos]);
                pos /= 2;
            }
            else
                break;
        }
    }
    void down(int pos)
    {
        while (true)
        {
            int tpos = pos;
            int ls = pos * 2, rs = pos * 2 + 1;
            if (ls <= sz && h[ls] > h[tpos])
                tpos = ls;
            if (rs <= sz && h[rs] > h[tpos])
                tpos = rs;
            if (tpos == pos)
                break;
            swap(h[pos], h[tpos]);
            pos = tpos;
        }
    }

public:
    int sz;
    heap(int MAXN = 1000005) : sz(0)
    {
        h.resize(MAXN);
    }
    heap(const vector<int> &arr, int MAXN = 1000005)
    {
        h.resize(MAXN);
        sz = arr.size();
        for (int i = 0; i < sz; ++i)
            h[i + 1] = arr[i];
        for (int i = sz; i >= 1; --i)
            down(i);
    }
    void push(int x)
    {
        h[++sz] = x;
        up(sz);
    }
    void pop()
    {
        if (sz == 0)
            return;
        h[1] = h[sz--];
        down(1);
    }
    int top()
    {
        if (sz == 0)
            return 0;
        return h[1];
    }
};

// 2. kth element

class kth_heap
{
private:
    priority_queue<int, vector<int>, greater<int>> q1;
    priority_queue<int, vector<int>, less<int>> q2;

public:
    int sz, k;
    kth_heap(int x) : sz(0), k(x) {}
    bool isok()
    {
        return sz >= k;
    }
    void push(int x)
    {
        if (sz < k)
        {
            q1.push(x);
            ++sz;
            return;
        }
        ++sz;
        q2.push(x);
        while (q1.top() < q2.top())
        {
            int temp = q1.top();
            q1.pop();
            q2.push(temp);
            q1.push(q2.top());
            q2.pop();
        }
    }
    void pop()
    {
        if (sz == 0)
            return;
        --sz;
        q1.pop();
        if (q2.empty())
            return;
        q1.push(q2.top());
        q2.pop();
    }
    int top()
    {
        return q1.top();
    }
};
