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

typedef long long ll;
typedef unsigned long long ull;
typedef vector<int> poly;

const int FFTN = 1 << 22, mod = 998244353; // FFTN最大值(1 << 23), mod-1 = 119 * (1 << 23)

int qpow(int a, int t)
{
    int s = 1;
    for (; t; t >>= 1, a = (ll)a * a % mod)
        if (t & 1)
            s = (ll)s * a % mod;
    return s;
}

// FNNT

namespace FFT
{
    int w[FFTN + 5], W[FFTN + 5], R[FFTN + 5];

    // 初始化单位根的幂
    void FFTinit()
    {
        W[0] = 1;
        W[1] = qpow(3, (mod - 1) / FFTN); // 3为原根, 若更换模数需要注意
        for (int i = 2; i <= FFTN; ++i)
            W[i] = (ll)W[i - 1] * W[1] % mod;
    }
    int FFTinit(int n)
    {
        int L = 1;
        for (; L <= n; L <<= 1)
            ;
        for (int i = 0; i <= L - 1; ++i)
            R[i] = (R[i >> 1] >> 1) | ((i & 1) ? (L >> 1) : 0);
        return L;
    }

    ull p[FFTN + 5];
    int A[FFTN + 5], B[FFTN + 5];

    // DFT和IDFT过程
    void DFT(int *a, int n)
    {
        for (int i = 0; i < n; ++i)
            p[R[i]] = a[i];
        for (int d = 1; d < n; d <<= 1)
        {
            int len = FFTN / (d << 1);
            for (int i = 0, j = 0; i < d; ++i, j += len)
                w[i] = W[j];
            for (int i = 0; i < n; i += (d << 1))
                for (int j = 0; j < d; ++j)
                {
                    int y = p[i + j + d] * w[j] % mod;
                    p[i + j + d] = p[i + j] + mod - y;
                    p[i + j] += y;
                }
            if (d == (1 << 15))
                for (int i = 0; i < n; ++i)
                    p[i] %= mod;
        }
        for (int i = 0; i < n; ++i)
            a[i] = p[i] % mod;
    }
    void IDFT(int *a, int n)
    {
        for (int i = 0; i < n; ++i)
            p[R[i]] = a[i];
        for (int d = 1; d < n; d <<= 1)
        {
            int len = FFTN / (d << 1);
            for (int i = 0, j = FFTN; i < d; ++i, j -= len)
                w[i] = W[j];
            for (int i = 0; i < n; i += (d << 1))
                for (int j = 0; j < d; ++j)
                {
                    int y = p[i + j + d] * w[j] % mod;
                    p[i + j + d] = p[i + j] + mod - y;
                    p[i + j] += y;
                }
            if (d == (1 << 15))
                for (int i = 0; i < n; ++i)
                    p[i] %= mod;
        }
        int val = qpow(n, mod - 2);
        for (int i = 0; i < n; ++i)
            a[i] = p[i] * val % mod;
    }

    // 多项式加法, Plus(poly a , poly b)返回a+b
    poly Plus(const poly &a, const poly &b)
    {
        int sza = a.size() - 1, szb = b.size() - 1;
        poly ans(std::max(sza, szb) + 1);
        for (int i = 0; i <= sza; ++i)
            ans[i] = a[i];
        for (int i = 0; i <= szb; ++i)
            ans[i] = (ans[i] + b[i]) % mod;
        return ans;
    }

    // 多项式减法, Minus(poly a , poly b)返回a-b
    poly Minus(const poly &a, const poly &b)
    {
        int sza = a.size() - 1, szb = b.size() - 1;
        poly ans(std::max(sza, szb) + 1);
        for (int i = 0; i <= sza; ++i)
            ans[i] = a[i];
        for (int i = 0; i <= szb; ++i)
            ans[i] = (ans[i] + mod - b[i]) % mod;
        return ans;
    }

    // 多项式乘法, Mul(poly a , poly b)返回a*b
    poly Mul(const poly &a, const poly &b)
    {
        int sza = a.size() - 1, szb = b.size() - 1;
        poly ans(sza + szb + 1);
        if (sza <= 30 || szb <= 30)
        {
            for (int i = 0; i <= sza; ++i)
                for (int j = 0; j <= szb; ++j)
                    ans[i + j] = (ans[i + j] + (ll)a[i] * b[j]) % mod;
            return ans;
        }
        int L = FFTinit(sza + szb);
        for (int i = 0; i < L; ++i)
            A[i] = (i <= sza ? a[i] : 0);
        for (int i = 0; i < L; ++i)
            B[i] = (i <= szb ? b[i] : 0);
        DFT(A, L), DFT(B, L);
        for (int i = 0; i < L; ++i)
            A[i] = (ll)A[i] * B[i] % mod;
        IDFT(A, L);
        for (int i = 0; i <= sza + szb; ++i)
            ans[i] = A[i];

        return ans;
    }

    // 多项式快速幂, PolyPow(poly a , b)返回a^b
    // 注意次数为(a.size()-1)*b
    poly PolyPow(const poly &a, int b)
    {
        int sza = a.size() - 1;
        poly ans(sza * b + 1);
        int L = FFTinit(sza * b + 1);
        for (int i = 0; i < L; ++i)
            A[i] = (i <= sza ? a[i] : 0);
        DFT(A, L);
        for (int i = 0; i < L; ++i)
            A[i] = qpow(A[i], b);
        IDFT(A, L);
        for (int i = 0; i <= sza * b; ++i)
            ans[i] = A[i];

        return ans;
    }

    // 多项式求逆, getinv(poly a , n)返回a^(-1) mod x^n
    void Getinv(int *a, int *b, int n)
    {
        if (n == 1)
        {
            b[0] = qpow(a[0], mod - 2);
            return;
        }
        int nn = (n + 1) >> 1;
        Getinv(a, b, nn);
        int L = FFTinit(n << 1);
        for (int i = 0; i < L; ++i)
            A[i] = (i < n ? a[i] : 0);
        for (int i = 0; i < L; ++i)
            B[i] = (i < nn ? b[i] : 0);
        DFT(A, L);
        DFT(B, L);
        for (int i = 0; i < L; ++i)
            A[i] = (ll)B[i] * (2 + mod - (ll)A[i] * B[i] % mod) % mod;
        IDFT(A, L);
        for (int i = 0; i < n; ++i)
            b[i] = A[i];
    }
    poly getinv(poly a, int n)
    {
        int *b = new int[n], *c = new int[n], sz = a.size();
        for (int i = 0; i < n; ++i)
            b[i] = (i < sz ? a[i] : 0);
        for (int i = 0; i < n; ++i)
            c[i] = 0;

        poly ans(n);
        Getinv(b, c, n);
        for (int i = 0; i < n; ++i)
            ans[i] = c[i];
        delete[] b;
        delete[] c;
        return ans;
    }
};

// example

int main()
{
    // clock_t st = clock(), ed;
    ios::sync_with_stdio(0);
    cin.tie(0);
    // cout << setprecision(15) << fixed;

    FFT::FFTinit(); // 必需
    int n, m, k;
    cin >> n >> m >> k;
    poly f(k + 1);
    ll C = 1;
    for (int i = 0; i <= k; ++i)
    {
        // debug(C);
        if (i % 2 == 0)
            f[i] = C;
        C = C * (n - i) % mod;
        C = C * qpow(i + 1, mod - 2) % mod;
    }
    poly g(1, 1);
    int ans = qpow(2, m);
    while (m)
    {
        f.resize(k + 1);
        if (m & 1)
        {
            g = FFT::Mul(g, f);
            g.resize(k + 1);
        }
        f = FFT::Mul(f, f);
        m >>= 1;
    }
    ans = 1ll * g[k] * ans % mod;
    cout << ans << endl;

    // ed = clock();
    // double endtime = (double)(ed - st) / CLOCKS_PER_SEC;
    // cout << "Total time: " << endtime << endl;
    return 0;
}
