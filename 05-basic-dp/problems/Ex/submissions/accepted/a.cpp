#include <bits/stdc++.h>
using namespace std;
#define fori(n, i) for (int i = 0; i < n; i++)

typedef vector<double> vd;

int main() {
    int n;
    cin >> n;
    vd p(n);
    fori(n, i) cin >> p[i];

    // s[i] is the probability that exactly i coins are stars
    vd s(n + 1, 0);
    s[0] = 1;

    for (int k = 1; k <= n; k++) {
        double &cp = p[k - 1];
        for (int i = k; i > 0; i--) {
            s[i] = (s[i - 1] * cp) + (s[i] * (1 - cp));
        }
        s[0] *= 1 - cp;
    }

    double stars = 0, lights = 0;
    for (int i = 0; i < (n + 1) / 2; i++) lights += s[i];
    for (int i = (n / 2) + 1; i <= n; i++) stars += s[i];
    cout << fixed << setprecision(10) << stars << ' ' << lights << endl;
}
