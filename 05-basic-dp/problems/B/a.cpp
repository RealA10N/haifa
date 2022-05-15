#include <bits/stdc++.h>
using namespace std;
#define int long long
const int MOD = 1e9 + 7;
inline int mod(int a) { return a %= MOD, a + (a < 0 ? a : 0); };
signed main() {
    int n;
    cin >> n;
    int ans = 1;
    for (int k = 2; k <= n; k++) ans = mod(mod(ans * ans) * 16);
    cout << mod(ans * 6) << endl;
}
