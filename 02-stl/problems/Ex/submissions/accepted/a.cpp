#include <bits/stdc++.h>
using namespace std;
#define int long long
#define fori(n, i) for (int i = 0; i < n; i++)
#define all(x) x.begin(), x.end()
typedef vector<int> vi;

signed main() {
    // 1 <= n <= 2e5
    // 1 <= l <= 1e9
    // -1e9 <= t <= 1e9
    int n, l, t;
    cin >> n >> l >> t;
    vi s(n), d(n);
    fori(n, i) cin >> s[n];  // 1 <= si <= l
    fori(n, i) cin >> d[i];  // -1 <= di <= 1
    t %= 2 * (l - 1);

    vi f(n);
    fori(n, i) {
        int v = s[i] + (t * d[i]);
        while (v < 1 || v > l) {
            if (v > l)
                v -= v - l;
            else
                v = -v + 1;
        }
        f.push_back(v);
    }

    vi p(n);
    fori(n, i) p[i] = i;
    sort(all(p), [&s](int i, int j) { return s[i] < s[j]; });
    sort(all(f));

    vi ans(n);
    fori(n, i) ans[p[i]] = f[i];
    fori(n, i) cout << ans[i] << ' ';
    cout << endl;
}
