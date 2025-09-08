xx = int(input())

def root(x, exp):
    lo, hi, ans = 1, int(x+1 ** (1.0/exp)), -1
    while lo <= hi:
        y = lo + hi >> 1
        if y ** exp <= x:
            lo = y + 1
            ans = y
        else:
            hi = y - 1
    return ans

def f(x):
    ans = 1
    i = 2
    while i * i <= x and i <= 1e7:
        if x % i == 0:
            e = 0
            while x % i == 0:
                x //= i
                e += 1
            ans *= (e + 1)
        else:
            i += 1
    
    if x > 1: ans *= 2

    return ans

for fn in range(61, 0, -1):
    n = root(xx, fn)
    if fn == 1:
        if n == 1:
            print(n)
            break
        continue
    if n != -1 and n ** fn == xx and f(n) == fn:
        print(n)
        break
else:
    print(-1)