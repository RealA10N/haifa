from __future__ import annotations
from cmath import inf
import queue
from random import randint
import os

LETTERS = ord('z') - ord('a') + 1
testcase = 3


def num_to_string(n: int) -> str:
    if not n:
        return ''
    last = chr(((n - 1) % LETTERS) + ord('a'))
    first = num_to_string((n - 1) // LETTERS)
    return first + last


def test_num_to_string():
    assert num_to_string(1) == 'a'
    assert num_to_string(LETTERS) == 'z'
    assert num_to_string(LETTERS + 1) == 'aa'
    assert num_to_string(LETTERS + 2) == 'ab'
    assert num_to_string(703) == 'aaa'
    assert num_to_string(703 + LETTERS) == 'aba'


def generate_testcase(
        size: tuple[int, int],
        fails_until_stop: int = 10,
        max_queens: int = int(5e5),
        valid: bool = True,
) -> list[tuple[int, int]]:
    rows = [False] * size[0]
    cols = [False] * size[1]
    main_diag = [False] * (size[0] + size[1])
    sec_diag = [False] * (size[0] + size[1])

    queens = list()

    for _ in range(max_queens):
        for _ in range(fails_until_stop):
            x, y = randint(1, size[0]), randint(1, size[1])

            if rows[x - 1] or cols[y - 1]:
                continue

            main, sec = x - y + size[1], x + y - 2
            if main_diag[main] or sec_diag[sec]:
                continue

            rows[x - 1] = cols[y - 1] = True
            main_diag[main] = sec_diag[sec] = True
            queens.append((x, y))
            break  # reset fail count

        else:
            break  # if reached max fails, exit and return queens

    if not valid:
        while True:
            x, y = randint(1, size[0]), randint(1, size[1])
            if (x, y) in queens:
                continue

            main, sec = x - y + size[1], x + y - 2
            if rows[x - 1] or cols[y - 1] or main_diag[main] or sec_diag[sec]:
                queens.append((x, y))
                break

    return queens


def greedy(n: int) -> list[tuple[int, int]]:
    h2 = n // 2
    h1 = n - h2
    if h1 % 2 == 0:
        h1 -= 1
        h2 += 1

    queens = list()

    for i in range(h1):
        queens.append((i + 1, (i * 2) + 1))

    for i in range(h2):
        queens.append((i + 1, (i + 1) * 2))

    return queens


def save_testcase(
        queens: list[tuple[int, int]],
        name: str,
        valid: bool,
        desc: str = None,
        folder: str = 'data/secret'
) -> None:
    os.makedirs(folder, exist_ok=True)

    name = f'{save_testcase.counter:02d}-{name}'
    save_testcase.counter += 1

    print(f'saving testscase {name}...', end='\r')

    in_path = os.path.join(folder, f'{name}.in')
    with open(in_path, 'w') as f:
        print(len(queens), file=f)
        for i, j in queens:
            assert i >= 1 and i <= 2e5
            assert j >= 1 and j <= 2e5
            print(f'{num_to_string(i)}{j}', end=' ', file=f)

    ans_path = os.path.join(folder, f'{name}.ans')
    with open(ans_path, 'w') as f:
        print("VALID" if valid else "INVALID", file=f)

    if desc:
        desc_path = os.path.join(folder, f'{name}.desc')
        with open(desc_path, 'w') as f:
            print(desc, file=f)

    print(f'saved testscase {name}!')


save_testcase.counter = 3


def main() -> int:
    test_num_to_string()

    save_testcase([(1, 1)], 'single', valid=True, desc='A single queen')
    save_testcase([(1, 2), (2, 3)], 'main-diag', valid=False,
                  desc='Two queens on the main diagonal')
    save_testcase([(1, 2), (2, 1)], 'sec-diag', valid=False,
                  desc='Two queens on the secondary diagonal')
    save_testcase([(1, 1), (1, 2)], 'row', valid=False,
                  desc='Two queens on the same row')
    save_testcase([(1, 1), (2, 1)], 'col', valid=False,
                  desc='Two queens on the same column')

    for _ in range(3):
        queens = generate_testcase((200_000, 200_000), fails_until_stop=10000)
        save_testcase(
            queens, 'stress-valid', valid=True,
            desc=f'dense: {len(queens)} queens - valid',
        )

    for _ in range(1, 4):
        queens = generate_testcase(
            (200_000, 200_000), fails_until_stop=10000, valid=False)
        save_testcase(
            queens, 'stress-invalid', valid=False,
            desc=f'dense: {len(queens)} queens - invalid',
        )

    for _ in range(15):
        queens = generate_testcase(
            (10_000, 10_000), fails_until_stop=10, max_queens=1000)
        save_testcase(
            queens, 'medium-valid', valid=True,
            desc=f'medium: {len(queens)} queens, 10.000 x 10.000 grid - valid',
        )

    for _ in range(15):
        queens = generate_testcase(
            (10_000, 10_000), fails_until_stop=10, max_queens=1000, valid=False)
        save_testcase(
            queens, 'medium-invalid', valid=False,
            desc=f'medium: {len(queens)} queens, 10.000 x 10.000 grid - invalid',
        )

    return 0


if __name__ == '__main__':
    raise SystemExit(main())
