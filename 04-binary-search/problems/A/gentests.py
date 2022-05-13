from __future__ import annotations

import os
from random import randint
import matplotlib.pyplot as plt  # pip install matplotlib

MAXN = int(1e4)
MAXA = int(1e9)
HALF2 = MAXN // 2
HALF1 = MAXN - HALF2

DIR = 'data/secret'
os.makedirs(DIR, exist_ok=True)


def save_testcase(arr: list[int], name: str) -> None:
    assert len(arr) <= MAXN
    for i, j in zip(arr[1:], arr[:-1]):
        assert i != j

    for i in arr:
        assert i > 0 and i <= MAXA

    inpath = os.path.join(DIR, f'{name}.in')
    with open(inpath, 'w') as f:
        print(len(arr), file=f)
        for i in arr:
            print(i, end=' ', file=f)
        print(file=f)

    anspath = os.path.join(DIR, f'{name}.ans')
    with open(anspath, 'w') as f:
        pass

    pltpath = os.path.join(DIR, f'{name}.png')

    x = [i + 1 for i in range(len(arr))]
    plt.plot(x, arr, marker='.')
    plt.savefig(pltpath)
    plt.clf()


def pyramid() -> list[int]:
    return list(range(1, HALF1)) + [HALF1 + 1] + [HALF2 - i for i in range(HALF2)]


def hole() -> list[int]:
    return list(range(HALF1, 1, -1)) + [1] + list(range(2, HALF2))


def peak() -> list[int]:
    return list(range(HALF1, 1, -1)) + [MAXN] + list(range(2, HALF2))


def single() -> list[int]:
    return [1]


def updown() -> list[int]:
    return [1, 2] * (MAXN // 2)


def upupdown() -> list[int]:
    return [1, 2, 3] * (MAXN // 3)


def up() -> list[int]:
    return list(range(1, MAXN + 1))


def down() -> list[int]:
    return list(reversed(up()))


def almost_up() -> list[int]:
    return [2] + up()[:-1]


def almost_down() -> list[int]:
    return down()[1:] + [2]


def random(n: int) -> list[int]:
    return [randint(0, 1e9) for i in range(n)]


if __name__ == '__main__':
    save_testcase(pyramid(), 'pyramid')
    save_testcase(hole(), 'hole')
    save_testcase(peak(), 'peak')
    save_testcase(single(), 'single')
    save_testcase(updown(), 'updown')
    save_testcase(upupdown(), 'upupdown')
    save_testcase(up(), 'up')
    save_testcase(down(), 'down')
    save_testcase(almost_up(), 'almost_up')
    save_testcase(almost_down(), 'almost_down')

    # short randoms
    for i in range(1, 30):
        n = randint(2, 35)
        save_testcase(random(n), f'short-random-{i:02d}')

    # medium randoms
    for i in range(1, 5):
        n = randint(1e2, 1e4)
        save_testcase(random(n), f'random-{i:02d}')

    # max randoms
    for i in range(1, 10):
        save_testcase(random(MAXN), f'max-random-{i:02d}')
