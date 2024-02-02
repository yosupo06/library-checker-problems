import sys

sys.set_int_max_str_digits(0)
inp = sys.stdin.read().split()

ps = 1
for _ in range(int(inp[0])):
    a = int(inp[ps], 16)
    b = int(inp[ps + 1], 16)
    ps += 2
    q, r = divmod(a, b)
    print(f"{q:x} {r:x}")
