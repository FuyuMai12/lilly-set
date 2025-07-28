# re:Re::set ~ [homu]lilly::set

import sys
input = sys.stdin.readline

s = input()
rev_s = s[::-1]
n = len(s)

a = s.index('A')
z = n - 1 - rev_s.index('Z')

print(z - a + 1)