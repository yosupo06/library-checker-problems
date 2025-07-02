## @{keyword.statement}

@{lang.en}
Given a size $N$ sequence $a_0, a_1, \dots, a _ {N - 1}$. Process the following $Q$ queries in order:

- `$l$ $r$ $x$`: Print the number and the sum of the elements among $a_l,a_{l+1},...,a_{r-1}$ that are not greater than $x$
@{lang.ja}
長さ $N$ の数列 $a_0, a_1, \dots, a _ {N - 1}$ が与えられます。以下の $Q$ 個のクエリの答えをそれぞれ出力してください。

- `$l$ $r$ $x$`: $a_l,a_{l+1},...,a_{r-1}$ のうち $x$ 以下の要素の個数と総和を出力してください。
@{lang.end}


## @{keyword.constraints}

@{lang.en}

- $1 \leq N, Q \leq @{param.MAX_N_Q}$
- $0 \leq a_i \leq @{param.MAX_A_X}$
- $0 \leq l \leq r \leq N$
- $0 \leq x \leq @{param.MAX_A_X}$

@{lang.ja}

- $1 \leq N, Q \leq @{param.MAX_N_Q}$
- $0 \leq a_i \leq @{param.MAX_A_X}$
- $0 \leq l \leq r \leq N$
- $0 \leq x \leq @{param.MAX_A_X}$

@{lang.end}

## @{keyword.input}

~~~
$N$ $Q$
$a_0$ $a_1$ ... $a_{N - 1}$
$l_0$ $r_0$ $x_0$
$l_1$ $r_1$ $x_1$
:
$l_{Q-1}$ $r_{Q-1}$ $x_{Q-1}$
~~~

@{example.example_00}
