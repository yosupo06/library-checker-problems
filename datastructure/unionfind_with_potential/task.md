## @{keyword.statement}

@{lang.en}

There is an unknown sequence of integers $(a_0, \ldots, a_{N - 1})$, process $Q$ queries.

- `$t_i$ = 0 $u_i$ $v_i$ $x_i$`: You are provided with information that $a_u \equiv a_v + x \pmod{@{param.MOD}}$. This information is valid if it does not contradict any previously given valid information. If this information is valid, output $1$; otherwise, output $0$.

- `$t_i$ = 1 $u_i$ $v_i$`: Based on the valid information provided so far, output the value of $a_u - a_v \bmod @{param.MOD}$ if it can be determined; otherwise, output $-1$.

@{lang.ja}

未知の整数列 $(a_0, \ldots, a_{N - 1})$ がある。$Q$ クエリを処理せよ。

- `$t_i$ = 0 $u_i$ $v_i$ $x_i$`：列 $a$ に関して $a_u \equiv a_v + x \pmod{@{param.MOD}}$ であるという情報が与えられる。この情報が valid であるとは，これまでの valid な情報に矛盾しないことを意味する。この情報が valid ならば $1$、そうでないなら $0$ を出力する。

- `$t_i$ = 1 $u_i$ $v_i$`: これまでの valid な情報をもとに
$a_u - a_v \bmod @{param.MOD}$ が定まるならばその値，定まらないならば $-1$ を出力せよ。

@{lang.end}

## @{keyword.constraints}

- $1 \leq N \leq @{param.N_MAX}$
- $1 \leq Q \leq @{param.Q_MAX}$
- $0 \leq u_i, v_i \lt N$
- $0 \leq x_i \lt @{param.MOD}$

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
