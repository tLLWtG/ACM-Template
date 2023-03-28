# A collection of useful tricks

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