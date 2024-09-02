### Tricks

> A collection of useful tricks

---

* integer floor
    ```cpp
    a / b
    ```

* integer ceil
    ```cpp
    (a + b - 1) / b
    ```

* integer sqrt
    ```cpp
    ll r = sqrtl(x) + 1;
    while (r * r > x)
        r--;
    ```
* new line
    ```cpp
    for(i = 1; i <= n; i++)
        for(j = 1; j <= m; j++)
        cout << a[i][j] << " \n"[j == m];
    ```

* rm the same element
    ```cpp
    sort(all(vec));
    vec.resize(unique(all(vec)) - vec.begin());
    ```

* count how many segments covering the range
    ```cpp
    vector<pii> arr(n);
    vector<int> node(2 * n), cnt(2 * n, 0);
    for (int i = 0; i < n; ++i)
    {
        cin >> arr[i].fi >> arr[i].se;
        node[k++] = arr[i].fi;
        node[k++] = arr[i].se;
    }
    sort(all(node));
    int N = unique(all(node)) - node.begin();
    for (int i = 0; i < n; ++i)
    {
        cnt[lower_bound(node.begin(), node.begin() + N, arr[i].fi) - node.begin()]++;
        cnt[lower_bound(node.begin(), node.begin() + N, arr[i].se) - node.begin()]--;
    }
    int cur = 0;
    for (int i = 0; i < N - 1; ++i)
    {
        cur += cnt[i];
        // cur is the number
        int len = node[i + 1] - node[i];
    }
    ```

* two rectangles cross
    ```cpp
    bool cross(Rec A, Rec B)
    {
        return max(A.x1, B.x1) <= min(A.x2, B.x2) && max(A.y1, B.y1) <= min(A.y2, B.y2);
    }
    ```

* tie and tuple
    ```cpp
    tuple<int, int, int, char> t(3, 4, 5, 'g');
    int a, b;
    tie(b, ignore, a, ignore) = t;
    ```

* raw string
    ```cpp
    string r_str = R"(Hello\tWorld\n)";
    // output: Hello\tWorld\n
    ```

* regex
    ```cpp
    regex email_pattern(R"(^[a-zA-Z0-9_.+-]+@[a-zA-Z0-9-]+\.[a-zA-Z0-9-.]+$)");
    string valid_email("swift@codeforces.com"), invalid_email("hello world");

    if (regex_match(valid_email, email_pattern))
        cout << valid_email << " is valid" << endl;
    if (!regex_match(invalid_email, email_pattern))
        cout << invalid_email << " is invalid" << endl;
    ```
* hash
    ```cpp
    // for unordered_X, e.g. unordered_map<int, int, my_hash>
    // link: https://codeforces.com/blog/entry/62393
    struct my_hash
    {
        static uint64_t splitmix64(uint64_t x)
        {
            x += 0x9e3779b97f4a7c15;
            x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
            x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
            return x ^ (x >> 31);
        }

        size_t operator()(uint64_t x) const
        {
            static const uint64_t FIXED_RANDOM =
                chrono::steady_clock::now().time_since_epoch().count();
            return splitmix64(x + FIXED_RANDOM);
        }

        size_t operator()(pair<uint64_t, uint64_t> x) const
        {
            static const uint64_t FIXED_RANDOM =
                chrono::steady_clock::now().time_since_epoch().count();
            return splitmix64(x.first + FIXED_RANDOM) ^
                (splitmix64(x.second + FIXED_RANDOM) >> 1);
        }
    };
    ```