#include "validate.hpp"

#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::vector;

const int maxq = 30, oo = 1e9;

int main(int argc, char **argv) {
    init_io(argc, argv);

    int n;
    if (!(judge_in >> n)) judge_error("cant parse judges input n\n");
    cout << n << endl;

    vector<int> a(n + 2, oo);
    for (int i = 1; i <= n; i++) {
        if (!(judge_in >> a[i]))
            judge_error("cant parse judges element #%d\n", i);
    }

    int q = 0;
    while (q++ <= maxq) {
        char type;
        if (!(author_out >> type))
            wrong_answer("cant parse type of query %d\n", q);

        int m;
        if (!(author_out >> m))
            wrong_answer("cant parse nubmer of query %d\n", q);

        if (m < 1 || m > n) {
            wrong_answer("got number %d in query %d, not in range", m, q);
        }

        if (type == '!') {
            if (a[m] < a[m - 1] && a[m] < a[m + 1])
                accept();
            else
                wrong_answer("incorrect answer: solution gave %d", m);
        } else if (type == '?') {
            cout << a[m] << endl;
        } else {
            wrong_answer("got query type '%c'\n", type);
        }
    }

    wrong_answer("requested >%d queries\n", maxq);
}
