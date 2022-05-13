#include <bits/stdc++.h>
using namespace std;
#define fori(n, i) for (int i = 0; i < n; i++)

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n, m;
        cin >> n >> m;
        int ma = 0, mb = 0;
        while (m--) {
            int a, b;
            cin >> a >> b;
            ma = max(ma, a), mb = max(mb, b);
        }

        if (ma + mb > n)
            cout << "IMPOSSIBLE" << endl;
        else {
            fori(ma, i) cout << "A";
            fori(n - ma, i) cout << "B";
            cout << endl;
        }
    }
}
