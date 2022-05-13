#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    int a = 1e9 + 2, b = 1e9 + 1;
    for (int i = 1; i <= n; i++) {
        int c;
        cout << "?" << i << endl;
        cin >> c;
        if (a > b && b < c) return cout << "!" << (i - 1) << endl, 0;
        a = b, b = c;
    }
    cout << "!" << n << endl;
}
