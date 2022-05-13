#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    int lo = 1, hi = n;
    while (lo < hi) {
        int mi = (lo + hi - 1) / 2;
        cout << "?" << mi << endl;
        cout << "?" << (mi + 1) << endl;
        int a, b;
        cin >> a >> b;
        if (a < b)
            hi = mi;
        else
            lo = mi + 1;
    }
    cout << "!" << lo << endl;
}
