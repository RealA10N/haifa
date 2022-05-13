#include <bits/stdc++.h>
using namespace std;
#define fori(n, i) for (int i = 0; i < n; i++)

const int maxn = 1005;
bool b[maxn][maxn];
int n, m;

bool can_place_row(int i) {
    fori(m, j) if (b[i][j]) return false;
    return true;
}

bool can_place_col(int j) {
    fori(n, i) if (b[i][j]) return false;
    return true;
}

bool can_place_diag(int i0, int j0) {
    int d = i0 - j0;
    int s = i0 + j0;
    fori(n, i) {
        int j1 = s - i;
        int j2 = i - d;
        if (0 <= j1 && j1 < m && b[i][j1]) return false;
        if (0 <= j2 && j2 < m && b[i][j2]) return false;
    }
    return true;
}

bool valid(int i, int j) {
    return can_place_row(i) && can_place_col(j) && can_place_diag(i, j);
}

int main() {
    cin >> n >> m;
    fori(n, i) fori(m, j) {
        char c;
        cin >> c;
        b[i][j] = c == 'Q';
    }

    fori(n, i) fori(m, j) {
        if (!b[i][j]) continue;
        b[i][j] = false;
        if (!valid(i, j)) return cout << "INVALID" << endl, 0;
        b[i][j] = true;
    }

    cout << "VALID" << endl;
}
