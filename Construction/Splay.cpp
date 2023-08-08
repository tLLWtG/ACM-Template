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

const int N = 100005;

class Splay
{
private:
    int rt, tot, fa[N], ch[N][2], val[N], cnt[N], sz[N];

    void maintain(int x) { sz[x] = sz[ch[x][0]] + sz[ch[x][1]] + cnt[x]; }

    bool get(int x) { return x == ch[fa[x]][1]; }

    void clear(int x)
    {
        ch[x][0] = ch[x][1] = fa[x] = val[x] = sz[x] = cnt[x] = 0;
    }

    void rotate(int x)
    {
        int y = fa[x], z = fa[y], chk = get(x);
        ch[y][chk] = ch[x][chk ^ 1];
        if (ch[x][chk ^ 1])
            fa[ch[x][chk ^ 1]] = y;
        ch[x][chk ^ 1] = y;
        fa[y] = x;
        fa[x] = z;
        if (z)
            ch[z][y == ch[z][1]] = x;
        maintain(y);
        maintain(x);
    }

    void splay(int x)
    {
        for (int f = fa[x]; f = fa[x], f; rotate(x))
            if (fa[f])
                rotate(get(x) == get(f) ? f : x);
        rt = x;
    }

    int lower()
    {
        int cur = ch[rt][0];
        if (!cur)
            return cur;
        while (ch[cur][1])
            cur = ch[cur][1];
        splay(cur);
        return cur;
    }

    int upper()
    {
        int cur = ch[rt][1];
        if (!cur)
            return cur;
        while (ch[cur][0])
            cur = ch[cur][0];
        splay(cur);
        return cur;
    }

public:
    void insert(int k)
    {
        if (!rt)
        {
            val[++tot] = k;
            cnt[tot]++;
            rt = tot;
            maintain(rt);
            return;
        }
        int cur = rt, f = 0;
        while (1)
        {
            if (val[cur] == k)
            {
                cnt[cur]++;
                maintain(cur);
                maintain(f);
                splay(cur);
                break;
            }
            f = cur;
            cur = ch[cur][val[cur] < k];
            if (!cur)
            {
                val[++tot] = k;
                cnt[tot]++;
                fa[tot] = f;
                ch[f][val[f] < k] = tot;
                maintain(tot);
                maintain(f);
                splay(tot);
                break;
            }
        }
    }

    int rank(int k)
    {
        int res = 0, cur = rt;
        while (1)
        {
            if (k < val[cur])
            {
                cur = ch[cur][0];
            }
            else
            {
                res += sz[ch[cur][0]];
                if (k == val[cur])
                {
                    splay(cur);
                    return res + 1;
                }
                res += cnt[cur];
                cur = ch[cur][1];
            }
        }
    }

    int kth(int k)
    {
        int cur = rt;
        while (1)
        {
            if (ch[cur][0] && k <= sz[ch[cur][0]])
            {
                cur = ch[cur][0];
            }
            else
            {
                k -= cnt[cur] + sz[ch[cur][0]];
                if (k <= 0)
                {
                    splay(cur);
                    return val[cur];
                }
                cur = ch[cur][1];
            }
        }
    }

    int lower(int x)
    {
        insert(x);
        int res = val[lower()];
        erase(x);
        return res;
    }

    int upper(int x)
    {
        insert(x);
        int res = val[upper()];
        erase(x);
        return res;
    }

    void erase(int k)
    {
        rank(k);
        if (cnt[rt] > 1)
        {
            cnt[rt]--;
            maintain(rt);
            return;
        }
        if (!ch[rt][0] && !ch[rt][1])
        {
            clear(rt);
            rt = 0;
            return;
        }
        if (!ch[rt][0])
        {
            int cur = rt;
            rt = ch[rt][1];
            fa[rt] = 0;
            clear(cur);
            return;
        }
        if (!ch[rt][1])
        {
            int cur = rt;
            rt = ch[rt][0];
            fa[rt] = 0;
            clear(cur);
            return;
        }
        int cur = rt;
        int x = lower();
        fa[ch[cur][1]] = x;
        ch[x][1] = ch[cur][1];
        clear(cur);
        maintain(rt);
    }
};