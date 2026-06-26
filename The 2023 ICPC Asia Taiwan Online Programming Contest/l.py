n = int(input())
xs = []
ys = []
for i in range(n):
    x, y = [int(x) for x in input().split()]
    xs.append(x)
    ys.append(y)

xs.sort()
ys.sort()

print(xs[(n - 1) // 2], ys[(n - 1) // 2])