## @{keyword.statement}

@{lang.en}

There is an unknown sequence of $2 \times 2$ invertible matrices with integer components $(a_0, \ldots, a_{N - 1})$, process $Q$ queries.

- `$t_i$ = 0 $u_i$ $v_i$ $x_{0, 0}$ $x_{0, 1}$ $x_{1, 0}$ $x_{1, 1}$`: You are provided with information that $a_u \equiv a_v x \pmod{@{param.MOD}}$, where $x$ is a $2 \times 2$ matrix with elements $x_{0, 0}, x_{0, 1}, x_{1, 0}, x_{1, 1}$. This information is valid if it does not contradict any previously given valid information. If this information is valid, output $1$; otherwise, output $0$.
- `$t_i$ = 1 $u_i$ $v_i$`: Based on the valid information provided so far, output the value of $a_v^{-1}a_u \bmod @{param.MOD}$ if it can be determined; otherwise, output $-1$.

@{lang.ja}

整数を成分とする $2 \times 2$ 可逆行列からなる未知の列 $(a_0, \ldots, a_{N - 1})$ がある。$Q$ クエリを処理せよ。

- `$t_i$ = 0 $u_i$ $v_i$ $x_{0, 0}$ $x_{0, 1}$ $x_{1, 0}$ $x_{1, 1}$`: 列 $a$ に関して $a_u \equiv a_v x \pmod{@{param.MOD}}$ であるという情報が与えられる。ここで、 $x$ は要素 $x_{0, 0}, x_{0, 1}, x_{1, 0}, x_{1, 1}$ を持つ $2 \times 2$ 行列です。この情報が valid であるとは，これまでの valid な情報に矛盾しないことを意味する。この情報が valid ならば $1$ 、そうでないなら $0$ を出力する。
- `$t_i$ = 1 $u_i$ $v_i$`: これまでの valid な情報をもとに $a_v^{-1}a_u \bmod @{param.MOD}$ が定まるならばその値，定まらないならば $-1$ を出力せよ。

@{lang.end}

## @{keyword.constraints}

- $1 \leq N \leq @{param.N_MAX}$
- $1 \leq Q \leq @{param.Q_MAX}$
- $0 \leq u_i, v_i \lt N$
- $0 \leq x_{0, 0}, x_{0, 1}, x_{1, 0}, x_{1, 1} < @{param.MOD}$
- $x_{0, 0}x_{1, 1} - x_{0, 1}x_{1, 0} \equiv 1 \pmod {@{param.MOD}}$

## @{keyword.input}

~~~
$N$ $Q$
$\textrm{Query}_0$
$\textrm{Query}_1$
:
$\textrm{Query}_{Q - 1}$
~~~

## @{keyword.sample}

@{example.example_00}
