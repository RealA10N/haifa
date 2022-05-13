from __future__ import annotations

import os
from random import randint
from random import shuffle
from itertools import permutations

import matplotlib.pyplot as plt  # pip install matplotlib

MAXN = int(2e5)
MAXA = int(1e9)

DIR = 'data/secret'
os.makedirs(DIR, exist_ok=True)


def tree_depth(n: int) -> int:
    depth = 0
    max_elems = 0
    while max_elems < n:
        max_elems += 1
        max_elems *= 2
        max_elems -= 1
        depth += 1
    return depth


def save_testcase(arr: list[int], name: str, desc: str = None) -> None:
    name = f'{save_testcase.testcase:03d}-{name}'
    save_testcase.testcase += 1

    print(f'saving {name}...')

    assert len(arr) <= MAXN
    for i in arr:
        assert i > 0 and i <= MAXA

    in_path = os.path.join(DIR, f'{name}.in')
    with open(in_path, 'w') as f:
        print(len(arr), file=f)
        for i in arr:
            print(i, end=' ', file=f)
        print(file=f)

    ans_path = os.path.join(DIR, f'{name}.ans')
    with open(ans_path, 'w') as f:
        print(tree_depth(len(arr)), file=f)

    pltpath = os.path.join(DIR, f'{name}.png')

    x = [i + 1 for i in range(len(arr))]
    plt.plot(x, arr, marker='.')
    plt.savefig(pltpath)
    plt.clf()

    if desc is not None:
        desc_path = os.path.join(DIR, f'{name}.desc')
        with open(desc_path, 'w') as f:
            print(desc, file=f)

    print(f'saved {name}!')


save_testcase.testcase = 1


def random_list(n: int) -> list[int]:
    return [randint(1, MAXA) for _ in range(n)]


def shuffled_lists(arr: list[int], times: int) -> list[tuple[str]]:
    have = set()
    ans = list()
    for _ in range(times):
        while tuple(arr) in have:
            shuffle(arr)
        ans.append(tuple(arr))
        have.add(tuple(arr))
    return ans


if __name__ == '__main__':

    save_testcase([1], 'single')
    save_testcase([1, 2], 'two-up', desc='[1, 2]')
    save_testcase([2, 1], 'two-down', desc='[2, 1]')

    for a in permutations([1, 2, 3]):
        save_testcase(a, 'three-permutation',
                      desc=f'permutation of 1, 2, 3: {list(a)!r}')

    # shuffles of 1...8
    for a in shuffled_lists(list(range(1, 9)), 20):
        save_testcase(a, '8shuffle', desc=f'shuffle of 1..8: {list(a)!r}')

    # shuffles of 1...7
    for a in shuffled_lists(list(range(1, 8)), 20):
        save_testcase(a, '7shuffle', desc=f'shuffle of 1..7: {list(a)!r}')

    # shuffles of 1...2^15
    for a in shuffled_lists(list(range(1, (2**15) + 1)), 10):
        save_testcase(a, '215shuffle', desc='shuffle of 1..2^15')

    # shuffles of 1...2^15-1
    for a in shuffled_lists(list(range(1, (2**15))), 10):
        save_testcase(a, '215shuffle', desc='shuffle of 1..2^15-1')

    for a in shuffled_lists(([1] * 100) + [2], 3):
        save_testcase(a, 'almost-same', desc='suffled [1,1,1,...,1,1,2]')

    for a in shuffled_lists(([1] * 100) + [2] + ([3] * 50), 3):
        save_testcase(a, 'aaabccc', desc='suffled [1,1,...,1,1,2,3,3,...,3,3]')

    save_testcase([1] * MAXN, 'same-max-length', desc='[1] * maxn')
    save_testcase(list(range(1, MAXN + 1)), 'up', desc='[1, 2, 3, ..., maxn]')
    save_testcase(list(range(MAXN, 0, -1)), 'down',
                  desc='[maxn, ...., 3, 2, 1]')

    # short randoms
    for i in range(1, 30):
        save_testcase(random_list(randint(2, 256)), 'random', desc='random')

    # max randoms
    for i in range(1, 3):
        save_testcase(random_list(MAXN), 'max-random', desc='max sized random')
