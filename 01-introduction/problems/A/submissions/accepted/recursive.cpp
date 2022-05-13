#include <bits/stdc++.h>
using namespace std;
#define int long long

int fact(int n) {
    if (n < 2) return 1;
    return n * fact(n - 1);
}

signed main() {
    int n;
    cin >> n;
    cout << fact(n) << endl;
}
