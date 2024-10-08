#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using pii = pair<int, int>;

#define pb push_back
#define all(x) (x).begin(), (x).end()
#define fi first
#define se second
#define endl '\n'
#define debug(x) { cerr << #x << " = " << x << endl; }

/*-------------------------------------------*/

// 1. 卡特兰数（Catalan）

// H_n（下标从 0 开始）: 1,1,2,5,14,42,132 ...

// H_n = H_{n-1}*(4*n-2)/(n+1)

// 在圆上选择 2n 个点，将这些点成对连接起来使得所得到的 n 条线段不相交的方法数？
// 对角线不相交的情况下，将一个凸多边形区域分成三角形区域的方法数？
// n 个结点可构造多少个不同的二叉树？
// 有一个大小为 n * n 的方格图左下角为 (0, 0) 右上角为 (n, n)，从左下角开始每次都只能向右或者向上走一单位，
// 不走到对角线 y=x 上方（但可以触碰）的情况下到达右上角有多少可能的路径？


// 2. 第二类斯特林数（Stirling Number）

//  S(n,k)，表示将 n 个两两不同的元素，划分为 k 个互不区分的非空子集的方案数。
/*
n/k 0   1   2   3   4   5 
0   1
1   0   1
2   0   1   1
3   0   2   3   1
4   0   6   11  6   1
5   0   24  50  35  10  1
*/
// S(n, k) = S(n-1,k-1)+k*S(n-1,k)

// 3. 错位排列（derangement）

// D_n（下标从 0 开始）: 0,1,2,9,44,265 ...
// D_n=(n-1)*(D_{n-1}+D_{n-2})

// 4. 斐波那契数列

// F_n（下标从 0 开始）: 0,1,1,2,3,5,8,13 ...
// F_n=F_{n-1}+F_{n-2}
// 使用矩阵快速幂计算
// 由 [F_{n-1}, F_n]=[F_{n-2}, F_{n-1}]*((0,1)T,(1,1)T)
// 得 [F_n, F_{n+1}]=[F_0, F_1]*P^n