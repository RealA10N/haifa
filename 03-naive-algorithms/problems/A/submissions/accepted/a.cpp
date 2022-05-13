#include <bits/stdc++.h>
using namespace std;

#define fori(n, i) for (int i = 0; i < n; i++)
const int maxn = 9;
int n, board[maxn];

bool canplace(int x, int y) {
    fori(n, i) {
        if (i == x) continue;
        if (board[i] == y) return false;
        if (board[i] != -1 && i + board[i] == x + y) return false;
        if (board[i] != -1 && i - board[i] == x - y) return false;
    }
    return true;
}

bool backtrack(int i) {
    if (i == n) return true;
    if (board[i] != -1) return backtrack(i + 1);
    fori(n, j) {
        if (canplace(i, j)) {
            board[i] = j;
            if (backtrack(i + 1)) return true;
            board[i] = -1;
        }
    }
    return false;
}

int main() {
    cin >> n;
    fori(n, i) {
        board[i] = -1;
        fori(n, j) {
            char c;
            cin >> c;
            if (c == 'Q') {
                if (board[i] != -1) return cout << "NO SOLUTION" << endl, 0;
                board[i] = j;
            }
        }
    }

    if (backtrack(0)) {
        fori(n, i) {
            fori(n, j) cout << (board[i] == j ? 'Q' : '.');
            cout << endl;
        }
    } else {
        cout << "NO SOLUTION" << endl;
    }
}
