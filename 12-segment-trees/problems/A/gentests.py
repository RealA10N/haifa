from __future__ import annotations
import os
from random import randint, shuffle
import subprocess

FOLDER = 'data/secret'
os.makedirs(FOLDER, exist_ok=True)
NEXT_TEST = 4
MAXN = int(2e5)
MAXA = int(1e9)


def save_test(lst: list[int], name: str, desc: str = None):
    global NEXT_TEST

    assert len(lst) <= MAXN
    for v in lst:
        assert 1 <= v <= MAXA

    inp = os.path.join(FOLDER, f'{NEXT_TEST:02d}-{name}.in')

    with open(inp, 'w') as f:
        print(len(lst), file=f)
        print(' '.join(str(i) for i in lst), file=f)

    ansp = os.path.join(FOLDER, f'{NEXT_TEST:02d}-{name}.ans')

    with open(ansp, 'w') as f, open(inp, 'r') as inpf:
        p = subprocess.run('./a.out', stdin=inpf, stdout=f)
        assert p.returncode == 0

    if desc:
        descp = os.path.join(FOLDER, f'{NEXT_TEST:02d}-{name}.desc')
        with open(descp, 'w') as f:
            print(desc, file=f)

    NEXT_TEST += 1


def random_list(n: int = MAXN, maxa: int = MAXA) -> list[int]:
    lst = list()
    for _ in range(n):
        lst.append(randint(1, maxa))
    return lst


save_test([1] * MAXN, 'same', desc='1,1,1,...')
ordered = list(range(1, MAXN + 1))
save_test(ordered, 'up', desc='1,2,...maxn')
save_test(list(reversed(ordered)), 'down', desc='maxn,...,2,1')

shuffle(ordered)
save_test(ordered, 'shuffle', desc='maxn,...,2,1')

for _ in range(10):
    save_test(random_list(randint(2, 20), maxa=20), 'short-random',
              desc='random values in [1,20], length is in [1,20]')

for _ in range(3):
    save_test(random_list(), 'max-random', desc='random max length')

save_test(random_list(maxa=20), 'random',
          desc='random, max length, max a_i is 20')

for _ in range(10):
    save_test(random_list(randint(1, 10_000)), 'random', desc='randoms')
