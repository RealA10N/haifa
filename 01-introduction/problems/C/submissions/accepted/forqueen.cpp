#include <bits/stdc++.h>
using namespace std;
#define fori(n, i) for (int i = 0; i < n; i++)
const int maxn = 1005;
bool b[maxn][maxn];
int n, m;

bool safecheck(int x, int y) {
    for (int i = 0; i < n; i++) {
        if (i == x) continue;
        int j1 = y - x + i, j2 = y + x - i;
        if (0 <= j1 && j1 < m && b[i][j1]) return false;
        if (0 <= j2 && j2 < m && b[i][j2]) return false;
        if (b[i][y]) return false;
    }
    for (int j = 0; j < m; j++) {
        if (j != y && b[x][j]) return false;
    }
    return true;
}

int main() {
    cin >> n >> m;
    fori(n, i) fori(m, j) {
        char c;
        cin >> c;
        b[i][j] = c == 'Q';
    }

    fori(n, i) fori(m, j) {
        if (b[i][j] && !safecheck(i, j)) {
            cout << "INVALID" << endl;
            return 0;
        }
    }

    cout << "VALID" << endl;
}
