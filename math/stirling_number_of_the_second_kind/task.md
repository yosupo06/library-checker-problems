Problem Statement / 問題文
---------

The Stirling numbers of the second kind $S(n, k)$ are defined as the coefficients in the identity
$$x^n = \sum_{k=0}^n S(n, k) x (x - 1) \cdots (x - (k - 1)).$$

You are given an integer $N$.
Calculate $S(N, k) \bmod {{param MOD}}$ for $0 \le k \le N$.

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
$S(N, 0)$ $\cdots$ $S(N, N)$
~~~

Sample / サンプル
---------

{{example example_00}}
