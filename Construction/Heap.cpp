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

#define MAXN 1000005

class heap
{
    private:
        int h[MAXN];
        void up(int pos);
        void down(int pos);
    public:
        int sz;
        heap(): sz(0){}
        heap(const vector<int> &arr);
        void push(int x);
        void pop();
        int top();
};

void heap::up(int pos)
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

void heap::down(int pos)
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

int heap::top()
{
    if (sz == 0)
        return 0;
    return h[1];
}

void heap::push(int x)
{
    h[++sz] = x;
    up(sz);
}

void heap::pop()
{
    if (sz == 0)
        return;
    h[1] = h[sz--];
    down(1);
}

heap::heap(const vector<int> &arr)
{
    sz = arr.size();
    for (int i = 0; i < sz; ++i)
        h[i + 1] = arr[i];
    for (int i = sz; i >= 1; --i)
        down(i);
}

// 2. kth element

class kth_heap
{
    priority_queue<int, vector<int>, greater<int>> q1;
    priority_queue<int, vector<int>, less<int>> q2;
    public:
        int sz, k;
        kth_heap(int x): sz(0), k(x){}
        bool isok();
        void push(int x);
        void pop();
        int top();
};

bool kth_heap::isok()
{
    return sz >= k;
}

int kth_heap::top()
{
    return q1.top();
}

void kth_heap::push(int x)
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

void kth_heap::pop()
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