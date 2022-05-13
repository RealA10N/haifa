#include <bits/stdc++.h>
using namespace std;
#define fori(n, i) for (int i = 0; i < n; i++)
#define all(x) x.begin(), x.end()
typedef vector<int> vi;

int n, nxt;

void inorder(vi &t, int u, vi &p) {
    if (2 * u < n) inorder(t, u * 2, p);
    t[u] = p[nxt++] + 1;
    if ((2 * u) + 1 < n) inorder(t, (2 * u) + 1, p);
}

signed main() {
    cin >> n;
    vi a(n), p(n);
    fori(n, i) cin >> a[i];
    fori(n, i) p[i] = i;

    sort(all(p), [&a](int x, int y) { return a[x] < a[y]; });

    n++, nxt = 0;
    vi t(n);
    inorder(t, 1, p);
    vi m(n);
    fori(n, i) m[t[i]] = i;

    for (int i = 1; i < n; i++) {
        int x = 0, y = 0;
        if (2 * m[i] < n) x = t[2 * m[i]];
        if ((2 * m[i]) + 1 < n) y = t[(2 * m[i]) + 1];
        cout << x << ' ' << y << endl;
    }
}
