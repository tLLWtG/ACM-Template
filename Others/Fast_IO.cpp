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

namespace IO
{
    char buf[1 << 15], *S, *T;
    inline char gc()
    {
        if (S == T)
        {
            T = (S = buf) + fread(buf, 1, 1 << 15, stdin);
            if (S == T)
                return EOF;
        }
        return *S++;
    }
    inline int read()
    {
        int x;
        bool f;
        char c;
        for (f = 0; (c = gc()) < '0' || c > '9'; f = c == '-')
            ;
        for (x = c ^ '0'; (c = gc()) >= '0' && c <= '9'; x = x * 10 + (c ^ '0'))
            ;
        return f ? -x : x;
    }
    const int olim = 1 << 20;
    char obuf[olim + 5], *OS;
    inline void print()
    {
        fwrite(obuf, 1, OS - obuf, stdout);
        OS = obuf;
    }
    inline void pc(char c)
    {
        *OS++ = c;
        if (OS == obuf + olim)
            print();
    }
    inline void write(const char *s, char c = '\n')
    {
        for (const char *i = s; *i != ' '; ++i)
            pc(*i);
        pc(c);
    }
    inline void write(int x, char c = '\n')
    {
        if (x < 0)
            pc('-'), x = -x;
        char temp[20], cnt;
        for (temp[cnt = 0] = x % 10; x /= 10; temp[++cnt] = x % 10)
            ;
        for (; ~cnt; --cnt)
            pc(temp[cnt] ^ '0');
        pc(c);
    }
    struct flusher
    {
        flusher() { OS = obuf; }
        ~flusher() { print(); }
    } __flusher__;
} // namespace IO

namespace IO_old // pay attention to overflowing case
{
    inline void read(int &x)
    {
        x = 0;
        bool flag(0);
        char ch = getchar();
        while (!isdigit(ch))
            flag = ch == '-', ch = getchar();
        while (isdigit(ch))
            x = (x << 1) + (x << 3) + (ch ^ 48), ch = getchar();
        flag ? x = -x : 0;
    }

    inline void write(int x, char c = '\n')
    {
        x < 0 ? x = -x, putchar('-') : 0;
        static short Stack[50], top(0);
        do
            Stack[++top] = x % 10, x /= 10;
        while (x);
        while (top)
            putchar(Stack[top--] | 48);
        putchar(c);
    }
} // namespace IO