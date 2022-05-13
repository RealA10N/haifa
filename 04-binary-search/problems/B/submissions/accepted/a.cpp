#include <bits/stdc++.h>
using namespace std;
#define int long long
#define fori(n, i) for (int i = 0; i < n; i++)
#define all(x) x.begin(), x.end()
typedef vector<int> vi;

signed main() {
    int n;
    cin >> n;
    vi a(n);
    fori(n, i) cin >> a[i];
    sort(all(a));
    int r = 0;
    for (int v : a) {
        if (r + 1 < v) return cout << r + 1 << endl, 0;
        r += v;
    }
    cout << r + 1 << endl;
}
