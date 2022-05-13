#include "validate.hpp"

#include <algorithm>
#include <string>
#include <utility>
#include <vector>

using std::string;
using std::vector;

const string NO_SOLUTION = "NO SOLUTION";

int main(int argc, char** argv) {
    init_io(argc, argv);

    int n;
    if (!(judge_in >> n)) judge_error("can't parse judges n\n");

    string s;
    getline(judge_ans, s);
    if (s == NO_SOLUTION) {
        string ans;
        if (!(author_out >> ans)) wrong_answer("can't parse output string\n");
        if (ans == NO_SOLUTION)
            accept();
        else
            wrong_answer("expected no solution, found %s\n", ans.c_str());
    }

    vector<int> original(n, -1);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            char c;
            if (!(judge_in >> c))
                judge_error("can't parse judges char at (%d, %d)\n", i + 1,
                            j + 1);
            if (c != 'Q' && c != '.')
                judge_error("format error: judges input contains char '%c'\n",
                            c);
            if (c == 'Q') original[i] = j;
        }
    }

    vector<int> board(n, -1);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            char c;
            if (!(author_out >> c))
                wrong_answer("can't parse char at (%d, %d)\n", i + 1, j + 1);

            if (c != 'Q' && c != '.')
                wrong_answer("format error: caught output char '%c'\n", c);

            if (c == 'Q') {
                if (board[i] != -1)
                    wrong_answer("two queens on row %d\n", i + 1);
                board[i] = j;
            }
        }
    }

    for (int i = 0; i < n; i++) {
        if (board[i] < 0 || board[i] >= n)
            wrong_answer("wrong on row %d\n", i + 1);
    }

    for (int x = 0; x < n; x++) {
        int y = board[x];
        for (int i = 0; i < n; i++) {
            if (i == x) continue;
            if (board[i] == y) wrong_answer("two queens on column %d\n", y + 1);
            if (i + board[i] == x + y)
                wrong_answer("two queens on sum diag %d\n", x + y + 2);
            if (i - board[i] == x - y)
                wrong_answer("two queens on diff diag %d\n", x - y);
        }
    }

    for (int i = 0; i < n; i++) {
        if (original[i] != -1 && board[i] != original[i]) {
            wrong_answer(
                "input contains queen at (%d, %d) which isn't present in the "
                "solution.\n",
                i + 1, 1 + original[i]);
        }
    }

    accept();
}
