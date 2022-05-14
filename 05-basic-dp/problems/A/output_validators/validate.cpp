#include "validate.hpp"

#include <cmath>
#include <string>
#include <vector>

typedef void report_error_func(const std::string& msg, ...);

#define delta(x, y) std::abs(x - y)
#define square(x) ((x) * (x))

int validate_ans(std::vector<int> h, std::vector<int> ans,
                 report_error_func* err) {
    for (size_t i = 0; i < ans.size(); i++) {
        if (ans[i] < 1 || ans[i] > h.size())
            (*err)("solutions element %d is out of range (=%d)\n", i + 1,
                   ans[i]);
        if (i > 0 && ans[i - 1] >= ans[i])
            (*err)("frog can't go backwards (from %d to %d)\n", ans[i - 1],
                   ans[i]);
    }

    int p = 0;
    for (size_t i = 1; i <= ans.size(); i++)
        p += delta(ans[i], ans[i - 1]) +
             square(delta(h[ans[i] - 1], h[ans[i - 1] - 1]));
    return p;
}

int main(int argv, char** argc) {
    init_io(argv, argc);

    int n;
    if (!(judge_in >> n)) judge_error("can't parse judges n\n");

    std::vector<int> h(n);
    for (int i = 0; i < n; i++)
        if (!(judge_in >> h[i])) judge_error("can't parse judges h[%d]\n", i);

    int jm;
    if (!(judge_ans >> jm)) judge_error("can't parse judges solution length\n");

    std::vector<int> jans(jm);
    for (int i = 0; i < n; i++)
        if (!(judge_ans >> jans[i]))
            judge_error("can't parse judges answer element %d\n", i + 1);

    int m;
    if (!(author_out >> m)) wrong_answer("can't parse length of solution\n");

    std::vector<int> ans(m);
    for (int i = 0; i < n; i++)
        if (!(author_out >> ans[i]))
            wrong_answer("can't parse solutions element %d\n", i + 1);

    int judge_power = validate_ans(h, ans, wrong_answer);
    int author_power = validate_ans(h, jans, &judge_error);
    if (judge_power != author_power) {
        wrong_answer("given solution uses %d power, optimal uses %d\n",
                     author_power, judge_power);
    }

    std::string s;
    if (author_out >> s) wrong_answer("output overflow\n");

    accept();
}
