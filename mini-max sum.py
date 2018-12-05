#!/bin/python3

import math
import os
import random
import re
import sys

# Complete the miniMaxSum function below.
def miniMaxSum(arr):
    sumv = sum(arr)
    maxv = sumv - min(arr)
    minv = sumv - max(arr)
    print(f"{minv} {maxv}")

if __name__ == '__main__':
    arr = list(map(int, input().rstrip().split()))

    miniMaxSum(arr)
