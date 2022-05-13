#include "validate.hpp"

#include <algorithm>
#include <string>
#include <utility>
#include <vector>

using std::vector, std::pair, std::string, std::max;

const int maxn = 2e5;

int verify_dfs(int u, vector<pair<int, int>>& tree, vector<int>& arr,
               vector<bool>& vis) {
    // dfs the graph, assert that it is a tree (no cycles)
    // return max depth

    if (vis[u]) wrong_answer("authors graph contains a cycle\n");
    vis[u] = true;

    //   a
    //  b c

    int a = arr[u], b = tree[u].first, c = tree[u].second;
    int d = 1;

    if (b != -1) {
        if (arr[b] > a)
            wrong_answer("invalid left child of #%d (%d) : #%d (%d)\n", u + 1,
                         a, b, arr[b]);
        d = max(d, 1 + verify_dfs(b, tree, arr, vis));
    }

    if (c != -1) {
        if (a > arr[c])
            wrong_answer("invalid right child of #%d (%d) : %d (%d)\n", u + 1,
                         a, c, arr[c]);
        d = max(d, 1 + verify_dfs(c, tree, arr, vis));
    }

    return d;
}

int main(int argc, char** argv) {
    init_io(argc, argv);

    int n;
    if (!(judge_in >> n)) judge_error("can't parse judges n\n");

    vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        if (!(judge_in >> arr[i]))
            judge_error("can't parse judges element #%d", i + 1);
    }

    vector<pair<int, int>> tree(n);
    vector<bool> ins(n, false);

    for (int i = 0; i < n; i++) {
        if (!(author_out >> tree[i].first))
            wrong_answer("can't parse first of element #%d\n", i + 1);
        if (tree[i].first < 0 || tree[i].first > n)
            wrong_answer(
                "got %d as first of element #%d, not in range [0, %d]\n",
                tree[i].first, i + 1, n);

        tree[i].first--;
        if (tree[i].first != -1) {
            if (ins[tree[i].first])
                wrong_answer("at least two parents to #%d\n",
                             tree[i].first + 1);
            ins[tree[i].first] = true;
        }

        if (!(author_out >> tree[i].second))
            wrong_answer("can't parse second of element #%d\n", i + 1);
        if (tree[i].second < 0 || tree[i].second > n)
            wrong_answer(
                "got %d as second of element #%d, not in range [0, %d]\n",
                tree[i].second, i + 1, n);

        tree[i].second--;
        if (tree[i].second != -1) {
            if (ins[tree[i].second])
                wrong_answer("at least two parents to #%d\n",
                             tree[i].second + 1);
            ins[tree[i].second] = true;
        }
    }

    string s;
    if (author_out >> s) wrong_answer("output overflow\n");

    int root = -1;
    for (int i = 0; i < n; i++) {
        if (!ins[i]) {
            if (root != -1)
                wrong_answer("at least two roots #%d, #%d found\n", root + 1,
                             i + 1);
            root = i;
        }
    }

    if (root == -1) wrong_answer("no root found\n");
    vector<bool> vis(n, false);
    int depth = verify_dfs(root, tree, arr, vis);

    int right_depth = 0;
    for (int i = 1; (i - 1) < n; i *= 2, right_depth++)
        ;

    if (depth != right_depth)
        wrong_answer("got tree with depth %d, right depth is %d\n", depth,
                     right_depth);

    for (bool b : vis)
        if (!b) wrong_answer("got forest instead of a tree\n");

    accept();  // yay!
}
