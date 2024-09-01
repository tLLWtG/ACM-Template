### Calculation_3D

```cpp
// kuangbin

namespace D3
{

    const double eps = 1e-8;
    int sgn(double x)
    {
        if (fabs(x) < eps)
            return 0;
        if (x < 0)
            return -1;
        else
            return 1;
    }
    struct Point3
    {
        double x, y, z;
        Point3(double _x = 0, double _y = 0, double _z = 0)
        {
            x = _x;
            y = _y;
            z = _z;
        }
        void input()
        {
            cin >> x >> y >> z;
        }
        void output()
        {
            cout << x << " " << y << " " << z << endl;
        }
        bool operator==(const Point3 &b) const
        {
            return sgn(x - b.x) == 0 && sgn(y - b.y) == 0 && sgn(z - b.z) == 0;
        }
        bool operator<(const Point3 &b) const
        {
            return sgn(x - b.x) == 0 ? (sgn(y - b.y) == 0 ? sgn(z - b.z) < 0 : y < b.y) : x < b.x;
        }
        double len()
        {
            return sqrt(x * x + y * y + z * z);
        }
        double len2()
        {
            return x * x + y * y + z * z;
        }
        double distance(const Point3 &b) const
        {
            return sqrt((x - b.x) * (x - b.x) + (y - b.y) * (y - b.y) + (z - b.z) * (z - b.z));
        }
        Point3 operator-(const Point3 &b) const
        {
            return Point3(x - b.x, y - b.y, z - b.z);
        }
        Point3 operator+(const Point3 &b) const
        {
            return Point3(x + b.x, y + b.y, z + b.z);
        }
        Point3 operator*(const double &k) const
        {
            return Point3(x * k, y * k, z * k);
        }
        Point3 operator/(const double &k) const
        {
            return Point3(x / k, y / k, z / k);
        }
        // 点乘
        double operator*(const Point3 &b) const
        {
            return x * b.x + y * b.y + z * b.z;
        }
        // 叉乘
        Point3 operator^(const Point3 &b) const
        {
            return Point3(y * b.z - z * b.y, z * b.x - x * b.z, x * b.y - y * b.x);
        }
        double rad(Point3 a, Point3 b)
        {
            Point3 p = (*this);
            return acos(((a - p) * (b - p)) / (a.distance(p) * b.distance(p)));
        }
        // 变换长度
        Point3 trunc(double r)
        {
            double l = len();
            if (!sgn(l))
                return *this;
            r /= l;
            return Point3(x * r, y * r, z * r);
        }
    };
    struct Line3
    {
        Point3 s, e;
        Line3() {}
        Line3(Point3 _s, Point3 _e)
        {
            s = _s;
            e = _e;
        }
        bool operator==(const Line3 v)
        {
            return (s == v.s) && (e == v.e);
        }
        void input()
        {
            s.input();
            e.input();
        }
        double length()
        {
            return s.distance(e);
        }
        // 点到直线距离
        double dispointtoline(Point3 p)
        {
            return ((e - s) ^ (p - s)).len() / s.distance(e);
        }
        // 点到线段距离
        double dispointtoseg(Point3 p)
        {
            if (sgn((p - s) * (e - s)) < 0 || sgn((p - e) * (s - e)) < 0)
                return min(p.distance(s), e.distance(p));
            return dispointtoline(p);
        }
        // 返回点p在直线上的投影
        Point3 lineprog(Point3 p)
        {
            return s + (((e - s) * ((e - s) * (p - s))) / ((e - s).len2()));
        }
        // p绕此向量逆时针arg角度
        Point3 rotate(Point3 p, double ang)
        {
            if (sgn(((s - p) ^ (e - p)).len()) == 0)
                return p;
            Point3 f1 = (e - s) ^ (p - s);
            Point3 f2 = (e - s) ^ (f1);
            double len = ((s - p) ^ (e - p)).len() / s.distance(e);
            f1 = f1.trunc(len);
            f2 = f2.trunc(len);
            Point3 h = p + f2;
            Point3 pp = h + f1;
            return h + ((p - h) * cos(ang)) + ((pp - h) * sin(ang));
        }
        // 点在直线上
        bool pointonseg(Point3 p)
        {
            return sgn(((s - p) ^ (e - p)).len()) == 0 && sgn((s - p) * (e - p)) == 0;
        }
    };
    struct Plane
    {
        Point3 a, b, c, o; // 平面上的三个点，以及法向量
        Plane() {}
        Plane(Point3 _a, Point3 _b, Point3 _c)
        {
            a = _a;
            b = _b;
            c = _c;
            o = pvec();
        }
        Point3 pvec()
        {
            return (b - a) ^ (c - a);
        }
        // ax+by+cz+d = 0
        Plane(double _a, double _b, double _c, double _d)
        {
            o = Point3(_a, _b, _c);
            if (sgn(_a) != 0)
                a = Point3((-_d - _c - _b) / _a, 1, 1);
            else if (sgn(_b) != 0)
                a = Point3(1, (-_d - _c - _a) / _b, 1);
            else if (sgn(_c) != 0)
                a = Point3(1, 1, (-_d - _a - _b) / _c);
        }
        // 点在平面上的判断
        bool pointonplane(Point3 p)
        {
            return sgn((p - a) * o) == 0;
        }
        // 两平面夹角
        double angleplane(Plane f)
        {
            return acos(o * f.o) / (o.len() * f.o.len());
        }
        // 平面和直线的交点，返回值是交点个数
        int crossline(Line3 u, Point3 &p)
        {
            double x = o * (u.e - a);
            double y = o * (u.s - a);
            double d = x - y;
            if (sgn(d) == 0)
                return 0;
            p = ((u.s * x) - (u.e * y)) / d;
            return 1;
        }
        // 点到平面最近点(也就是投影)
        Point3 pointtoplane(Point3 p)
        {
            Line3 u = Line3(p, p + o);
            crossline(u, p);
            return p;
        }
        // 平面和平面的交线
        int crossplane(Plane f, Line3 &u)
        {
            Point3 oo = o ^ f.o;
            Point3 v = o ^ oo;
            double d = fabs(f.o * v);
            if (sgn(d) == 0)
                return 0;
            Point3 q = a + (v * (f.o * (f.a - a)) / d);
            u = Line3(q, q + oo);
            return 1;
        }
    };
}

// 三维凸包
namespace convexHull
{
    const double eps = 1e-8;
    const int MAXN = 550;
    int sgn(double x)
    {
        if (fabs(x) < eps)
            return 0;
        if (x < 0)
            return -1;
        else
            return 1;
    }
    struct Point3
    {
        double x, y, z;
        Point3(double _x = 0, double _y = 0, double _z = 0)
        {
            x = _x;
            y = _y;
            z = _z;
        }
        void input()
        {
            cin >> x >> y >> z;
        }
        bool operator==(const Point3 &b) const
        {
            return sgn(x - b.x) == 0 && sgn(y - b.y) == 0 && sgn(z - b.z) == 0;
        }
        double len()
        {
            return sqrt(x * x + y * y + z * z);
        }
        double len2()
        {
            return x * x + y * y + z * z;
        }
        double distance(const Point3 &b) const
        {
            return sqrt((x - b.x) * (x - b.x) + (y - b.y) * (y - b.y) + (z - b.z) * (z - b.z));
        }
        Point3 operator-(const Point3 &b) const
        {
            return Point3(x - b.x, y - b.y, z - b.z);
        }
        Point3 operator+(const Point3 &b) const
        {
            return Point3(x + b.x, y + b.y, z + b.z);
        }
        Point3 operator*(const double &k) const
        {
            return Point3(x * k, y * k, z * k);
        }
        Point3 operator/(const double &k) const
        {
            return Point3(x / k, y / k, z / k);
        }
        // 点乘
        double operator*(const Point3 &b) const
        {
            return x * b.x + y * b.y + z * b.z;
        }
        // 叉乘
        Point3 operator^(const Point3 &b) const
        {
            return Point3(y * b.z - z * b.y, z * b.x - x * b.z, x * b.y - y * b.x);
        }
    };
    struct CH3D
    {
        struct face
        {
            // 表示凸包一个面上的三个点的编号
            int a, b, c;
            // 表示该面是否属于最终的凸包上的面
            bool ok;
        };
        // 初始顶点数
        int n;
        Point3 P[MAXN];
        // 凸包表面的三角形数
        int num;
        // 凸包表面的三角形
        face F[8 * MAXN];
        int g[MAXN][MAXN];
        // 叉乘
        Point3 cross(const Point3 &a, const Point3 &b, const Point3 &c)
        {
            return (b - a) ^ (c - a);
        }
        // 三角形面积*2
        double area(Point3 a, Point3 b, Point3 c)
        {
            return ((b - a) ^ (c - a)).len();
        }
        // 四面体有向面积*6
        double volume(Point3 a, Point3 b, Point3 c, Point3 d)
        {
            return ((b - a) ^ (c - a)) * (d - a);
        }
        // 正：点在面同向
        double dblcmp(Point3 &p, face &f)
        {
            Point3 p1 = P[f.b] - P[f.a];
            Point3 p2 = P[f.c] - P[f.a];
            Point3 p3 = p - P[f.a];
            return (p1 ^ p2) * p3;
        }
        void deal(int p, int a, int b)
        {
            int f = g[a][b];
            face add;
            if (F[f].ok)
            {
                if (dblcmp(P[p], F[f]) > eps)
                    dfs(p, f);
                else
                {
                    add.a = b;
                    add.b = a;
                    add.c = p;
                    add.ok = true;
                    g[p][b] = g[a][p] = g[b][a] = num;
                    F[num++] = add;
                }
            }
        }
        // 递归搜索所有应该从凸包内删除的面
        void dfs(int p, int now)
        {
            F[now].ok = false;
            deal(p, F[now].b, F[now].a);
            deal(p, F[now].c, F[now].b);
            deal(p, F[now].a, F[now].c);
        }
        bool same(int s, int t)
        {
            Point3 &a = P[F[s].a];
            Point3 &b = P[F[s].b];
            Point3 &c = P[F[s].c];
            return fabs(volume(a, b, c, P[F[t].a])) < eps &&
                   fabs(volume(a, b, c, P[F[t].b])) < eps &&
                   fabs(volume(a, b, c, P[F[t].c])) < eps;
        }
        // 构建三维凸包
        void create()
        {
            num = 0;
            face add;

            //***********************************
            // 此段是为了保证前四个点不共面
            bool flag = true;
            for (int i = 1; i < n; i++)
            {
                if (!(P[0] == P[i]))
                {
                    swap(P[1], P[i]);
                    flag = false;
                    break;
                }
            }
            if (flag)
                return;
            flag = true;
            for (int i = 2; i < n; i++)
            {
                if (((P[1] - P[0]) ^ (P[i] - P[0])).len() > eps)
                {
                    swap(P[2], P[i]);
                    flag = false;
                    break;
                }
            }
            if (flag)
                return;
            flag = true;
            for (int i = 3; i < n; i++)
            {
                if (fabs(((P[1] - P[0]) ^ (P[2] - P[0])) * (P[i] - P[0])) > eps)
                {
                    swap(P[3], P[i]);
                    flag = false;
                    break;
                }
            }
            if (flag)
                return;
            //**********************************

            for (int i = 0; i < 4; i++)
            {
                add.a = (i + 1) % 4;
                add.b = (i + 2) % 4;
                add.c = (i + 3) % 4;
                add.ok = true;
                if (dblcmp(P[i], add) > 0)
                    swap(add.b, add.c);
                g[add.a][add.b] = g[add.b][add.c] = g[add.c][add.a] = num;
                F[num++] = add;
            }
            for (int i = 4; i < n; i++)
                for (int j = 0; j < num; j++)
                    if (F[j].ok && dblcmp(P[i], F[j]) > eps)
                    {
                        dfs(i, j);
                        break;
                    }
            int tmp = num;
            num = 0;
            for (int i = 0; i < tmp; i++)
                if (F[i].ok)
                    F[num++] = F[i];
        }
        // 表面积
        // 测试：HDU3528
        double area()
        {
            double res = 0;
            if (n == 3)
            {
                Point3 p = cross(P[0], P[1], P[2]);
                return p.len() / 2;
            }
            for (int i = 0; i < num; i++)
                res += area(P[F[i].a], P[F[i].b], P[F[i].c]);
            return res / 2.0;
        }
        double volume()
        {
            double res = 0;
            Point3 tmp = Point3(0, 0, 0);
            for (int i = 0; i < num; i++)
                res += volume(tmp, P[F[i].a], P[F[i].b], P[F[i].c]);
            return fabs(res / 6);
        }
        // 表面三角形个数
        int triangle()
        {
            return num;
        }
        // 表面多边形个数
        // 测试：HDU3662
        int polygon()
        {
            int res = 0;
            for (int i = 0; i < num; i++)
            {
                bool flag = true;
                for (int j = 0; j < i; j++)
                    if (same(i, j))
                    {
                        flag = 0;
                        break;
                    }
                res += flag;
            }
            return res;
        }
        // 重心
        // 测试：HDU4273
        Point3 barycenter()
        {
            Point3 ans = Point3(0, 0, 0);
            Point3 o = Point3(0, 0, 0);
            double all = 0;
            for (int i = 0; i < num; i++)
            {
                double vol = volume(o, P[F[i].a], P[F[i].b], P[F[i].c]);
                ans = ans + (((o + P[F[i].a] + P[F[i].b] + P[F[i].c]) / 4.0) * vol);
                all += vol;
            }
            ans = ans / all;
            return ans;
        }
        // 点到面的距离
        // 测试：HDU4273
        double ptoface(Point3 p, int i)
        {
            double tmp1 = fabs(volume(P[F[i].a], P[F[i].b], P[F[i].c], p));
            double tmp2 = ((P[F[i].b] - P[F[i].a]) ^ (P[F[i].c] - P[F[i].a])).len();
            return tmp1 / tmp2;
        }
    };
    CH3D hull;
    int main()
    {
        while (cin >> hull.n)
        {
            for (int i = 0; i < hull.n; i++)
                hull.P[i].input();
            hull.create();
            Point3 p = hull.barycenter();
            double ans = 1e20;
            for (int i = 0; i < hull.num; i++)
                ans = min(ans, hull.ptoface(p, i));
            cout << ans << endl;
        }
        return 0;
    }
}
```

