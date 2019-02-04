import re

#!/bin/python3

import math
import os
import random
import re
import sys



if __name__ == '__main__':
    N = int(input())
    Names = []
    for N_itr in range(N):
        firstNameEmailID = input().split()

        firstName = firstNameEmailID[0]

        emailID = firstNameEmailID[1]
        lastName = re.findall("([a-zA-Z0-9].+(?=@))", emailID)
        Names.append(firstName,lastName)
    set(Names)
    for Name in Names:
        print(Name)
