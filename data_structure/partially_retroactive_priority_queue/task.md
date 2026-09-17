## @{keyword.statement}

@{lang.en}

You are given a sequence of $N$ ordered pairs $(t_0, x_0), (t_1, x_1), \dots, (t_{N-1}, x_{N-1})$.

Let $M$ be the multiset obtained by applying the following operations:

- Initially, $M$ is empty.
- For $i=0, 1, \dots, N-1$:
    - If $t_i=0$, insert $x_i$ into $M$.
    - If $t_i=1$ and $M$ is non-empty, remove one occurrence of the minimum element of $M$.
    - If $t_i=1$ and $M$ is empty, do nothing.
    - If $t_i=2$, do nothing.

You are given $Q$ queries. Process each query $q=0, 1, \dots, Q-1$ as follows:

- You are given integers $k_q, a_q, b_q$.
Replace $t_{k_q}\leftarrow a_q$ and $x_{k_q}\leftarrow b_q$. Consider the multiset $M$ obtained from the updated sequence. Print the number of elements in $M$, and the sum of elements in $M$.

@{lang.ja}

$N$ 個の順序対 $(t_0, x_0), (t_1, x_1), \dots, (t_{N-1}, x_{N-1})$ からなる列が与えられます。

以下の操作を適用して得られる多重集合を $M$ とします。

- $M$ を空の多重集合で初期化する。
- $i=0, 1, \dots, N-1$ について：
    - $t_i=0$ の場合、$x_i$ を $M$ に挿入する。
    - $t_i=1$ かつ $M$ が空でない場合、$M$ の最小要素を $1$ つ削除する。
    - $t_i=1$ かつ $M$ が空集合の場合、何もしない。
    - $t_i=2$ の場合、何もしない。

$Q$ 個のクエリが与えられます。各クエリ $q=0, 1, \dots, Q-1$ を処理してください。

- 整数 $k_q, a_q, b_q$ が与えられる。$t_{k_q}\leftarrow a_q$ および $x_{k_q}\leftarrow b_q$ に置き換える。更新された列から得られる多重集合 $M$ について、$M$ の要素数と、$M$ の要素の和を出力する。

@{lang.end}

## @{keyword.constraints}

@{lang.en}

- $@{param.N_MIN} \leq N \leq @{param.N_MAX}$
- $@{param.Q_MIN} \leq Q \leq @{param.Q_MAX}$
- $0 \leq t_i \leq 2$
- If $t_i=0$, $@{param.X_MIN} \leq x_i \leq @{param.X_MAX}$
- If $t_i\in\lbrace 1, 2 \rbrace$, $x_i=-1$
- $0 \leq k_q \lt N$
- $0 \leq a_q \leq 2$
- If $a_q=0$, $@{param.X_MIN} \leq b_q \leq @{param.X_MAX}$
- If $a_q\in\lbrace 1, 2 \rbrace$, $b_q=-1$

@{lang.ja}

- $@{param.N_MIN} \leq N \leq @{param.N_MAX}$
- $@{param.Q_MIN} \leq Q \leq @{param.Q_MAX}$
- $0 \leq t_i \leq 2$
- $t_i=0$ の場合、$@{param.X_MIN} \leq x_i \leq @{param.X_MAX}$
- $t_i\in\lbrace 1, 2 \rbrace$ の場合、$x_i=-1$
- $0 \leq k_q \lt N$
- $0 \leq a_q \leq 2$
- $a_q=0$ の場合、$@{param.X_MIN} \leq b_q \leq @{param.X_MAX}$
- $a_q\in\lbrace 1, 2 \rbrace$ の場合、$b_q=-1$

@{lang.end}

## @{keyword.input}

~~~
$N$ $Q$
$t_0$ $x_0$
$\vdots$
$t_{N-1}$ $x_{N-1}$
$k_0$ $a_0$ $b_0$
$\vdots$
$k_{Q-1}$ $a_{Q-1}$ $b_{Q-1}$
~~~

## @{keyword.sample}

@{example.example_00}

@{example.example_01}
