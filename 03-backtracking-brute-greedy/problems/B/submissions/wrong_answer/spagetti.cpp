#include <bits/stdc++.h>
using namespace std;
#define int long long
#define fori(n, i) for (int i = 0; i < n; i++)
#define all(x) x.begin(), x.end()
typedef vector<int> vi;

signed main() {
    int n;
    cin >> n;
    vi a(n), p(n);
    fori(n, i) cin >> a[i];
    fori(n, i) p[i] = i;
    sort(all(p), [a](const int &f, const int &s) { return a[f] < a[s]; });
    vi ans(n, 0);
    fori(n - 1, i) ans[p[i]] = p[i + 1] + 1;
    for (int i : ans) cout << 0 << ' ' << i << endl;
}
