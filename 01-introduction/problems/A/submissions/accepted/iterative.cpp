#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
signed main() {
    ll n;
    cin >> n;
    ll res = 1;
    for (ll i = 1; i <= n; i++) res *= i;
    cout << res << endl;
}
