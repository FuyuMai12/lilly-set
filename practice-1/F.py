# re:Re::set ~ [homu]lilly::set

import sys
input = sys.stdin.readline

T = int(input())
for _ in range(T):
    a = int(input())
    b = int(input())

    if a < b: a, b = b, a

    while b > 0:
        sub_a = a % b
        a, b = b, sub_a
    
    print(a)
