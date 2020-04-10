<div markdown="1" class="lang-en">

Problem Statement
---------

You are given a non-negative integer sequence $A = (a_0, a_1, \ldots, a_{N-1})$ with the length $N$. Process the following $Q$ queries in order:

- You are given integers $l_i$ and $r_i$. Print $\sum_{k=l_i}^{r_i-1} a_k$.

</div>
<div markdown="1" class="lang-ja">

問題文
---------

長さ $N$ の非負整数列 $A = (a_0, a_1, \ldots, a_{N-1})$ が与えられます。以下で説明されるクエリを順に $Q$ 回処理してください。

- 整数 $l_i, r_i$ が与えられるので、$\sum_{k=l_i}^{r_i-1} a_k$ を出力する。

</div>

Constraints / 制約
---------

- $1 \leq N \leq {{param MAX_N}}$
- $1 \leq Q \leq {{param MAX_Q}}$
- $0 \leq a_i \leq {{param MAX_A}}$
- $0 \leq l_i < r_i \leq N$

Input / 入力
---------

```
$N$ $Q$
$a_0$ $a_1$ $\ldots$ $a_{N-1}$
$l_1$ $r_1$
$\vdots$
$l_Q$ $r_Q$
```

Sample / サンプル
---------

{{example example_00}}

