#include <bits/stdc++.h>
using namespace std;
#define fori(n, i) for (int i = 0; i < n; i++)

const int maxn = 1005, max2n = 2005;
bool row[maxn], col[maxn], sdiag[max2n], ddiag[max2n];
int n, m;

bool valid(int i, int j) {
    int s = i + j, d = i - j + maxn;
    return !row[i] && !col[j] && !sdiag[s] && !ddiag[d];
}

void mark(int i, int j, bool val = true) {
    int s = i + j, d = i - j + maxn;
    row[i] = col[j] = sdiag[s] = ddiag[d] = val;
}

int main() {
    fori(maxn, i) row[i] = col[i] = false;
    fori(max2n, i) sdiag[i] = ddiag[i] = false;

    cin >> n >> m;
    fori(n, i) fori(m, j) {
        char c;
        cin >> c;
        if (c == 'Q') {
            if (!valid(i, j)) return cout << "INVALID" << endl, 0;
            mark(i, j);
        }
    }

    cout << "VALID" << endl;
}
