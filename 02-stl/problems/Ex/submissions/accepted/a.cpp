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
    if (l <= 1) return cout << 1 << endl, 0;
    t %= 2 * (l - 1);

    vi s(n), d(n);
    fori(n, i) cin >> s[i];  // 1 <= si <= l
    fori(n, i) cin >> d[i];  // -1 <= di <= 1

    vi f(n);
    fori(n, i) {
        f[i] = s[i] + (t * d[i]);
        while (f[i] < 1 || f[i] > l) {
            if (f[i] > l)
                f[i] -= 2 * (f[i] - l);
            else
                f[i] = -f[i] + 1;
        }
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
