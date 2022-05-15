from __future__ import annotations
import os
from random import randint, choice
import subprocess
from typing import NamedTuple

FOLDER = 'data/secret'
os.makedirs(FOLDER, exist_ok=True)
NEXT_TEST = 4

MAXN = int(2e5)
MAXA = int(1e9)
MINT = int(-1e9)
MAXT = int(1e9)


class Ant(NamedTuple):
    start: int
    direction: int


class TestCase(NamedTuple):
    ants: list[Ant]
    l: int
    t: int


def save_test(test: TestCase, desc: str = None):
    global NEXT_TEST

    assert 1 <= len(test.ants) <= MAXN
    assert len(test.ants) <= test.l <= MAXA
    assert MINT <= test.t <= MAXT

    starts = set()
    for ant in test.ants:
        assert 1 <= ant.start <= MAXA
        assert ant.start not in starts
        starts.add(ant.start)
        assert abs(ant.direction) == 1

    inp = os.path.join(FOLDER, f'{NEXT_TEST:02d}.in')

    with open(inp, 'w') as f:
        print(len(test.ants), test.l, test.t, file=f)
        print(' '.join(str(ant.start) for ant in test.ants), file=f)
        print(' '.join(str(ant.direction) for ant in test.ants), file=f)

    ansp = os.path.join(FOLDER, f'{NEXT_TEST:02d}.ans')

    with open(ansp, 'w') as f, open(inp, 'r') as inpf:
        p = subprocess.run('./a.out', stdin=inpf, stdout=f,
                           stderr=subprocess.STDOUT)
        assert p.returncode == 0

    if desc:
        descp = os.path.join(FOLDER, f'{NEXT_TEST:02d}.desc')
        with open(descp, 'w') as f:
            print(desc, file=f)

    NEXT_TEST += 1


def random_locations(n: int, l: int) -> list[int]:
    locs = set()
    assert n <= l

    for _ in range(n):
        i = randint(1, l)
        while i in locs:
            i = randint(1, l)
        locs.add(i)

    return list(locs)


def random_ants(n: int, l: int) -> list[Ant]:
    return [Ant(s, choice((-1, 1))) for s in random_locations(n, l)]


def main():
    save_test(TestCase([Ant(1, 1)], l=1, t=MAXT),
              desc='single ant, l=1, max t')
    save_test(TestCase([Ant(1, 1)], l=1, t=MINT),
              desc='single ant, l=1, min t')

    for _ in range(3):
        save_test(TestCase(
            random_ants(MAXN, MAXA),
            l=MAXA, t=randint(MINT, MAXT)),
            desc='max ants and length',
        )

    for _ in range(3):
        save_test(TestCase(
            random_ants(randint(1, 100), l=MAXA),
            l=MAXA, t=randint(MINT, MAXT)),
            desc='up to 100 ants',
        )

    for _ in range(3):
        save_test(TestCase(
            [Ant(i, 1) for i in range(1, 11)],
            l=100, t=randint(MINT, MAXT)),
            desc='group of ants going in the same direction'
        )


if __name__ == '__main__':
    main()
