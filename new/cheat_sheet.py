#!/usr/bin/env python3
"""
Python Cheat Sheet: Useful built-ins and modules with advantages over C++ STL

Sections:
 1. Sequence Utilities
 2. Heaps & Binary Search
 3. Itertools & Functional Tools
 4. Collections Module
 5. Math & Stats
 6. String Processing & Regex
 7. Quick I/O
"""

# 1. Sequence Utilities
# ---------------------
# Sorting with key:
#   sorted(a, key=lambda x: x.score, reverse=True)
# Stable sort (default in Python):
#   sorted(a)
# Reversal:
#   list(reversed(a)) or a[::-1]
# Slicing with strides:
#   a[i:j:k]
# Enumerate:
#   for i, x in enumerate(a): ...
# Zip:
#   for x, y in zip(a, b): ...
# Unpacking swap:
#   a, b = b, a

# 2. Heaps & Binary Search
# ------------------------
import heapq
import bisect

# Min-heap operations:
#   heap = []
#   heapq.heappush(heap, x)
#   x = heapq.heappop(heap)
# Max-heap by negating values or heapq._heapify_max:
#   heapq._heapify_max(heap)
# Bisect (binary search insertion index):
#   idx = bisect.bisect_left(a, x)

# 3. Itertools & Functional Tools
# --------------------------------
import itertools
from functools import lru_cache, reduce
from operator import itemgetter, mul

# Permutations, combinations, product:
#   list(itertools.permutations(a, r))
#   list(itertools.combinations(a, r))
#   list(itertools.product(a, b))
# Accumulate (prefix sums or custom op):
#   list(itertools.accumulate(a))
#   list(itertools.accumulate(a, mul))
# Group by consecutive keys:
#   for key, grp in itertools.groupby(sorted(a)):
#       process(list(grp))
# Chain to flatten:
#   list(itertools.chain.from_iterable(list_of_lists))
# LRU cache for memoization:
#   @lru_cache(None)
#   def f(...): ...

# 4. Collections Module
# ---------------------
import collections

# deque: O(1) pops/appends both ends
#   dq = collections.deque([1,2,3])
#   dq.appendleft(0); dq.popleft()
# defaultdict: default factory avoids key errors
#   dd = collections.defaultdict(int); dd[x] += 1
# Counter: frequency counts + common()
#   cnt = collections.Counter(a); cnt.most_common(3)
# namedtuple: lightweight struct
#   Point = collections.namedtuple('Point', ['x','y']); p = Point(1,2)

# 5. Math & Stats
# ----------------
import math
import random
import statistics

# GCD:
#   math.gcd(a, b)
# Combinations/permutations count:
#   math.comb(n, k), math.perm(n, k)
# Floating comparison:
#   math.isclose(a, b, rel_tol=1e-9)
# Mean/median/std:
#   statistics.mean(a), statistics.median(a), statistics.pstdev(a)

# 6. String Processing & Regex
# ----------------------------
import re

# Split/join:
#   words = s.split()
#   s2 = ' '.join(words)
# Regex match/groups:
#   m = re.match(r'(\d+)-(\d+)', s)
#   if m: a, b = map(int, m.groups())

# 7. Quick I/O
# ------------
import sys

# Fast input:
#   input = sys.stdin.readline
# Bulk read tokens:
#   data = sys.stdin.read().split(); it = iter(data)
#   nxt = lambda: next(it)
# Fast output:
#   sys.stdout.write(str(x) + '\n')

# Example I/O helper functions

def read_int():
    """Read a single integer."""
    return int(sys.stdin.readline())


def read_ints():
    """Read a line of space-separated integers."""
    return list(map(int, sys.stdin.readline().split()))


def read_strs():
    """Read a line of space-separated strings."""
    return sys.stdin.readline().split()


if __name__ == '__main__':
    # Demo usage:
    # arr = [3,1,2]
    # print(sorted(arr))
    # print(read_ints())
    pass
