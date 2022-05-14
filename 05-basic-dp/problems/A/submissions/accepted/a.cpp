#include <bits/stdc++.h>
using namespace std;
#define int long long
typedef vector<int> vi;
#define fori(n, i) for (int i = 0; i < n; i++)
const int oo = 4e18;
#define square(x) ((x) * (x))
#define delta(x, y) abs(x - y)
signed main() {
    int n;
    cin >> n;
    vi h(n), dp(n, oo), from(n, -1);
    fori(n, i) cin >> h[i];
    dp[0] = 0;
    fori(n, i) fori(i, j) {
        int c = dp[j] + delta(i, j) + square(delta(h[j], h[i]));
        if (c < dp[i]) dp[i] = c, from[i] = j;
    }

    stack<int> s;
    int i = n - 1;
    while (i != -1) s.push(i), i = from[i];
    cout << s.size() << endl;
    while (s.size()) cout << s.top() + 1 << ' ', s.pop();
    cout << endl;
}
