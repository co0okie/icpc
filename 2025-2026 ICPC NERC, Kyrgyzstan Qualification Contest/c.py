import math

def scale(x):
    if x < 2**31:
        return 32
    elif x < 2**63:
        return 64
    else:
        return 128

a = int(input())
b = int(input())
ta = scale(a)
tb = scale(b)
tab = scale(a * b)
if ta != tab and tb != tab:
    if a >= b:
        ta = tab
    else:
        tb = tab

print(ta)
print(tb)
print(tab)