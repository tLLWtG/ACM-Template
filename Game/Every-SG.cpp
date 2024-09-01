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

// Every-SG 游戏
// 对于还没有结束的单一游戏，游戏者必须对该游戏进行一步决策。
// 其他规则与普通 SG 游戏相同。
// (由很多单一游戏组成，每次每个玩家需要在每一个能够操作的单一游戏上进行操作，最后结束的那个单一游戏的胜负决定整个游戏的胜负。)
// 那么对于每个玩家来说，都希望自己必胜的游戏玩得尽量长，自己必败的游戏玩的尽量短。
// 对于 SG 值为 0 的点，我们需要知道最少需要多少步才能走到结束，对于 SG 值不为 0 的点，我们需要知道最多需要多少步结束。

//              0               (v 为终止状态)
//  step(v)=    max{step(u)}+1  (SG(v)>0 且 u 为 v 的后继状态 且 SG(u)=0)
//              min{step(u)}+1  (SG(v)=0 且 u 为 v 的后继状态)

// 先手必胜当且仅当单一游戏中最大的 step 为奇数。
