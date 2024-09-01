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

// 不要求顺序

namespace RC
{
    const int maxn = 1e6 + 5;
    const long double eps=1e-11;
    int n;
     
    int dcmp(long double x){
        return (fabs(x)<=eps)?0:(x<0?-1:1);
    }
    struct Point{
        long double x,y;
        Point(long double X=0,long double Y=0){x=X,y=Y;}
    };
    struct Vector{
        long double x,y;
        Vector(long double X=0,long double Y=0){x=X,y=Y;}
    };
    inline Vector operator-(Point x,Point y){// 点-点=向量
        return Vector(x.x-y.x,x.y-y.y);
    }
    inline long double cross(Vector x,Vector y){ // 向量叉积
        return x.x*y.y-x.y*y.x;
    }
    inline long double operator*(Vector x,Vector y){ // 向量叉积
        return cross(x,y);
    }
    inline long double len(Vector x){ // 向量模长
        return sqrt(x.x*x.x+x.y*x.y);
    }
 
    int stk[maxn];
    bool used[maxn];
    Point poly[1000005];
 
    vector<Point> ConvexHull(Point* poly, int n){ // Andrew算法求凸包
        int top=0;
        sort(poly+1,poly+n+1,[&](Point x,Point y){
            return (x.x==y.x)?(x.y<y.y):(x.x<y.x);
        });
        stk[++top]=1;
        for(int i=2;i<=n;i++){
            while(top>1&&dcmp((poly[stk[top]]-poly[stk[top-1]])*(poly[i]-poly[stk[top]]))<=0){
                used[stk[top--]]=0;
            }
            used[i]=1;
            stk[++top]=i;
        }
        int tmp=top;
        for(int i=n-1;i;i--){
            if(used[i]) continue;
            while(top>tmp&&dcmp((poly[stk[top]]-poly[stk[top-1]])*(poly[i]-poly[stk[top]]))<=0){
                used[stk[top--]]=0;
            }
            used[i]=1;
            stk[++top]=i;
        }
        vector<Point> a;
        for(int i=1;i<=top;i++){
            a.push_back(poly[stk[i]]);
        }
        return a;
    }
 
    struct Line{
        Point x;Vector y;
        Line(Point X,Vector Y){x=X,y=Y;}
        Line(Point X,Point Y){x=X,y=Y-X;}
    };
 
    inline long double DistanceToLine(Point P,Line x){// 点到直线的距离
        Vector v1=x.y, v2=P-x.x;
        return fabs(cross(v1,v2))/len(v1);
    }
 
    long double RoatingCalipers(vector<Point> poly){// 旋转卡壳
        if(poly.size()==3) return len(poly[1]-poly[0]);
        int cur=0;
        long double ans=0;
        for(int i=0;i<poly.size()-1;i++){
            Line line(poly[i],poly[i+1]);
            while(DistanceToLine(poly[cur], line) <= DistanceToLine(poly[(cur+1)%poly.size()], line)){
                cur=(cur+1)%poly.size();
            }
            ans=max(ans, max(len(poly[i]-poly[cur]), len(poly[i+1]-poly[cur])));
        }
        return ans;
    }
 
    long double solve()
    {
        cin >> n;
        for(int i = 1; i <= n; ++i)
            cin >> poly[i].x >> poly[i].y;
        long double v = RoatingCalipers(ConvexHull(poly, n));
        return v;
    }
}
