q = int(input())
d = {}

for _ in range(q):
    query = list(map(int,input().split()))
    if query[0] == 0:
        k = query[1]
        v = query[2]
        d[k] = v
    else:
        k = query[1]
        if k not in d:
            print(0)
        else:
            print(d[k])