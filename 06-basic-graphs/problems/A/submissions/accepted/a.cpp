#include <bits/stdc++.h>
using namespace std;
#define int long long
typedef vector<int> vi;

const int maxn = 2e5;
vi g[maxn], ds[maxn];
int mad = 0;

void dfs(int u, int d) {
    ds[d].push_back(u);
    mad = max(mad, d);
    for (int v : g[u]) dfs(v, d + 1);
}

signed main() {
    int n;
    cin >> n;
    for (int i = 2; i <= n; i++) {
        int j;
        cin >> j;
        g[j].push_back(i);
    }

    dfs(1, 0);
    cout << mad << endl;
    for (int i = 1; i <= mad; i++) {
        cout << ds[i].size() << ' ';
        for (int v : ds[i]) cout << v << ' ';
        cout << endl;
    }
}
