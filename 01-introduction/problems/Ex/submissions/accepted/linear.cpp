#include <bits/stdc++.h>
using namespace std;

#define fori(n, i) for (int i = 0; i < n; i++)
typedef pair<int, int> ii;

const int maxn = 2e5 + 10;
bool row[maxn], col[maxn], sdiag[2 * maxn], ddiag[2 * maxn];

const int ltrs = 'z' - 'a' + 1;
ii tocords(const string& s) {
    int i = 0, j = 0;
    for (char c : s) {
        if (isdigit(c))
            j *= 10, j += c - '0';
        else
            i *= ltrs, i += c - 'a' + 1;
    }
    return {i, j};
}

bool process(int i, int j) {
    int s = i + j, d = i - j + maxn;
    if (row[i] || col[j] || sdiag[s] || ddiag[d]) return false;
    return row[i] = col[j] = sdiag[s] = ddiag[d] = true;
}

int main() {
    fori(maxn, i) row[i] = col[i] = false;
    fori(2 * maxn, i) sdiag[i] = ddiag[i] = false;

    int q;
    cin >> q;
    while (q--) {
        string s;
        cin >> s;
        int i, j;
        tie(i, j) = tocords(s);
        if (!process(i, j)) return cout << "INVALID" << endl, 0;
    }

    cout << "VALID" << endl;
}
