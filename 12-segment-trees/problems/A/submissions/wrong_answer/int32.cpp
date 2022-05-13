#include <bits/stdc++.h>
using namespace std;

typedef struct seg {
    seg *left = NULL, *right = NULL;
    int lo, hi, mi, v = 0;

    seg(int lo, int hi) : lo(lo), hi(hi), mi((lo + hi) / 2) {}

    void push() {
        if (left == NULL) left = new seg(lo, mi);
        if (right == NULL) right = new seg(mi + 1, hi);
    }

    void add(int i, int d = 1) {
        if (lo == hi && lo == i) return v += d, void();
        push();
        (i <= mi ? left : right)->add(i, d);
        v = left->v + right->v;
    }

    int get(int a, int b) {
        if (b < lo || hi < a) return 0;
        if (a <= lo && hi <= b) return v;
        push();
        return left->get(a, b) + right->get(a, b);
    }
} seg;

signed main() {
    int n;
    cin >> n;
    seg seg(1, 1e9);
    int ans = 0;
    while (n--) {
        int a;
        cin >> a;
        ans += seg.get(a + 1, 1e9);
        seg.add(a);
    }
    cout << ans << endl;
}
