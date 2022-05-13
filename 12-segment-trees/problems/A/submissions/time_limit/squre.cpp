#include <bits/stdc++.h>
using namespace std;

#define int long long
#define fori(n, i) for (int i = 0; i < n; i++)
typedef vector<int> vi;

signed main() {
    int n;
    cin >> n;
    vi a(n);
    fori(n, i) cin >> a[i];
    int ans = 0;
    for (int i = 0; i < n - 1; i++)
        for (int j = i + 1; j < n; j++)
            if (a[i] > a[j]) ans++;
    cout << ans << endl;
}
