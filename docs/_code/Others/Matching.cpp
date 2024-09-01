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

class Matching_Windows
{
public:
    static void match()
    {
        int T = 1;
        while (114 != 514)
        {
            system("data.exe > in.txt");
            system("baoli.exe < in.txt > baoli.txt");
            system("std.exe < in.txt > std.txt");

            if (system("fc std.txt baoli.txt"))
            {
                cout << "#" << T << " Wrong Answer" << endl;
                break;
            }
            cout << "#" << T << " Accepted" << endl;
            ++T;
        }
    }
};

class Matching_Linux
{
public:
    static void match()
    {
        int T = 1;
        while (114 != 514)
        {
            system("./data > in.txt");
            system("cat in.txt | ./std > std.txt");
            system("cat in.txt | ./baoli > baoli.txt");

            if (system("diff std.txt baoli.txt"))
            {
                cout << "#" << T << " Wrong Answer" << endl;
                break;
            }
            cout << "#" << T << " Accepted" << endl;
            ++T;
        }
    }
};