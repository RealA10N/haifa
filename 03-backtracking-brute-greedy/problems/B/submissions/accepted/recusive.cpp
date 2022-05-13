#include <bits/stdc++.h>
using namespace std;
#define int long long
#define fori(n, i) for (int i = 0; i < n; i++)
#define all(x) x.begin(), x.end()
typedef vector<int> vi;

const int maxn = 2e5 + 5;
int leftc[maxn], rightc[maxn];

int buildtree(vi &p, int lo, int hi) {
    if (lo > hi) return 0;
    int mi = (lo + hi) / 2;
    leftc[p[mi]] = buildtree(p, lo, mi - 1);
    rightc[p[mi]] = buildtree(p, mi + 1, hi);
    return p[mi];
}

signed main() {
    int n;
    cin >> n;
    vi a(n), p(n);
    fori(n, i) cin >> a[i];
    fori(n, i) p[i] = i + 1;
    sort(all(p),
         [&a](const int &f, const int &s) { return a[f - 1] < a[s - 1]; });
    buildtree(p, 0, n - 1);
    for (int i = 1; i <= n; i++) cout << leftc[i] << ' ' << rightc[i] << endl;
}
