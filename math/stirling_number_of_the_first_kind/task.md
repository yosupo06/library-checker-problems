Problem Statement / 問題文
---------

The signed Stirling numbers of the first kind $s(n, k)$ are defined as the coefficients in the identity
$$x (x - 1) \cdots (x - (n - 1)) = \sum_{k=0}^n s(n, k) x^k.$$

You are given an integer $N$.
Calculate $s(N, k) \bmod {{param MOD}}$ for $0 \le k \le N$.

Constraints / 制約
---------

- ${{param N_MIN}} \le N \le {{param N_MAX}}$

Input / 入力
---------

~~~
$N$
~~~

Output / 出力
---------

~~~
$s(N, 0)$ $\cdots$ $s(N, N)$
~~~

Sample / サンプル
---------

{{example example_00}}
