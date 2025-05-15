#!/usr/bin/env python3
import sys
import threading
import math
import bisect
from collections import deque, defaultdict, Counter

# Fast I/O
input = sys.stdin.readline
# If you need even faster output:
# sys.stdout.write

# Increase recursion limit (if you have deep recursion)
sys.setrecursionlimit(10**7)

def read_ints():
    """Read a line of space-separated integers."""
    return list(map(int, input().split()))

def read_int():
    """Read a single integer."""
    return int(input())

def read_strs():
    """Read a line of space-separated strings."""
    return input().split()

def main():
    # Example: multiple test cases
    # t = read_int()
    # for _ in range(t):
    #     solve()
    
    # Single-case template:
    # n = read_int()
    # arr = read_ints()
    #
    # # Your solution here…
    # print(answer)
    pass

# If you're not using threading, you can just call main():
if __name__ == "__main__":
    # Uncomment below to run main() in a separate thread
    # (sometimes helps avoid recursion limits on PC² judges)
    # threading.Thread(target=main).start()
    main()
