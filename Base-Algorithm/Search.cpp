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

// 1. Meet in the middle(BFS version)
//
// (a). one queue and 2 different marks
//
// (b). two queues and two maps(marks)
//      each time search the smaller size part for 1 level
//      (more optimized)


// 2. IDS(iterative deepening depth-first search)
//
// for (int limit = 1; ; ++limit)
//      search
//      if found:
//          break;
//          


// 3. A* search algorithm
//
//      each time search the smallest f(x) = g(x) + h(x)
//      with open set and closed set (?)