#include "validate.h"

#include <string>
#include <vector>
using namespace std;

Judge *judge = NULL;
int testcase;
int n, m;

void testans(const string &ans, int a, int b, int mi) {
    int as = 0, bs = 0;
    for (int i = 0; i < a + b - 1; i++) {
        if (ans[i] == 'A')
            as++;
        else
            bs++;
    }

    for (int i = a + b - 1; i < n; i++) {
        if (ans[i] == 'A')
            as++;
        else
            bs++;
        if (as == a && bs == b) return;  // nice!
        if (ans[i - a - b + 1] == 'A')
            as--;
        else
            bs--;
    }

    judge->wrong_answer("testcase %d: person %d isn't covered\n", testcase, mi);
}

void checkcase() {
    if (!(judge->judge_in >> n))
        judge->judge_error("testcase %d: can't parse n\n", testcase);
    if (!(judge->judge_in >> m))
        judge->judge_error("testcase %d: can't parse m\n", testcase);

    vector<int> a(m), b(m);
    for (int i = 0; i < m; i++) {
        if (!(judge->judge_in >> a[i]))
            judge->judge_error("testcase %d: can't parse A of person #%d\n",
                               testcase, i + 1);
        if (!(judge->judge_in >> b[i]))
            judge->judge_error("testcase %d: can't parse b of person #%d\n",
                               testcase, i + 1);
    }

    string judgeans, ans;
    if (!(judge->judge_ans >> judgeans))
        judge->judge_error("testcase %d: can't parse judges answer\n",
                           testcase);
    if (!(judge->author_out >> ans))
        judge->judge_error("testcase %d: can't parse answer\n", testcase);

    if (judgeans == "IMPOSSIBLE") {
        if (ans == "IMPOSSIBLE") return;
        judge->wrong_answer(
            "testcase %d: contestent says POSSIBLE, judge says IMPOSSIBLE\n",
            testcase);
    }

    if (ans == "IMPOSSIBLE")
        judge->wrong_answer(
            "testcase %d: contestent says IMPOSSIBLE, judge says POSSIBLE\n",
            testcase);

    if (ans.size() != n)
        judge->wrong_answer("testcase %d: expected string size %d, got %d",
                            testcase, int(judgeans.size()), int(ans.size()));

    for (char c : ans) {
        if (c != 'A' && c != 'B') {
            judge->wrong_answer("testcase %d: invalid output char %c\n",
                                testcase, c);
        }
    }

    for (int i = 0; i < m; i++) testans(ans, a[i], b[i], i + 1);
}

int main(int argc, char **argv) {
    Judge j(argc, argv);
    judge = &j;

    int t;
    if (!(judge->judge_in >> t))
        judge->judge_error("can't parse amount of tests t\n");

    for (int i = 1; i <= t; i++) {
        testcase = i;
        checkcase();
    }

    string trash;
    if (judge->author_out >> trash) judge->wrong_answer("Trailing output\n");

    judge->accept();
}
