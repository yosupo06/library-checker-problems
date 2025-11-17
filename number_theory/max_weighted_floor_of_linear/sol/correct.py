"""
implementation of max weighted floor of linear function
"""
#pylint: disable=too-many-arguments
#pylint: disable=too-many-positional-arguments
def mwf(l: int, r: int, m: int, a: int, b: int, c: int, d: int) -> int:
    """
    Computes ReturnValue = max{ a*x + b*floor((c*x + d)/m) | l <= x < r }
    for integers l, r, m, a, b, c, d with l < r and m > 0
    """
    assert l < r and 0 < m
    n = r - l
    qd0, d = divmod(c * l + d, m)
    max_acc = sum_acc = a * l + b * qd0
    while True:
        qc, c = divmod(c, m)
        a += b * qc
        qd, d = divmod(d, m)
        sum_acc += b * qd
        y_max = (c * (n - 1) + d) // m
        max_acc = max(max_acc, sum_acc, sum_acc + a * (n - 1) + b * y_max)
        if y_max == 0 or (a >= 0 and b >= 0) or (a <= 0 and b <= 0):
            return max_acc
        if a < 0:
            sum_acc += a + b
        n, m, a, b, c, d = y_max, c, b, a, m, (m - d - 1)


if __name__ == "__main__":
    import sys
    T = int(sys.stdin.readline())
    for _ in range(T):
        N, M, A, B, C, D = map(int, sys.stdin.readline().split())
        assert 0 < N and 0 < M
        ans = mwf(0, N, M, A, B, C, D)
        print(ans)
