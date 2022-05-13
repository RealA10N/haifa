#include <bits/stdc++.h>
using namespace std;

int n;
const int oo = 1e9 + 5;

int query(int i) {
    // 1 : \/ .
    // 2 : \\ .
    // 3 : // .
    // 4 : /\ .

    int a = oo, b = oo, c = oo;
    cout << "?" << i << endl;
    cin >> b;

    if (i > 1) {
        cout << "?" << (i - 1) << endl;
        cin >> a;
    }
    if (i < n) {
        cout << "?" << (i + 1) << endl;
        cin >> c;
    }

    int r = 1;
    if (a < b) r += 2;
    if (b > c) r++;
    return r;
}

int main() {
    cin >> n;
    int lo = 1, hi = n;
    while (lo < hi) {
        int mi = (lo + hi) / 2;
        int r = query(mi);
        if (r == 1)
            return cout << "!" << mi << endl, 0;
        else if (r == 2)
            lo = mi + 1;
        else
            hi = mi - 1;
    }
    cout << "!" << lo << endl;
}
