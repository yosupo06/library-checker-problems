## @{keyword.statement}

@{lang.en}
You are given a $@{param.X_MAX} \times @{param.Y_MAX}$ matrix $A = (A_{xy})$ ($0\leq x < @{param.X_MAX}$, $0\leq y < @{param.Y_MAX}$). 
Initially, all entries $A_{xy}$ equal $0$. 

First, process following $N$ queries. 

- `$l$ $d$ $r$ $u$ $w$`: Add $w$ to all entries $A_{xy}$ satisfying $l\leq x < r$ and $d\leq y < u$. 

Then, process following $Q$ queries. 

- `$l$ $d$ $r$ $u$`: Calculate sum of entries $A_{xy}$ satisfying $l\leq x < r$ and $d\leq y < u$, and print it modulo $@{param.MOD}$. 

@{lang.ja}
$@{param.X_MAX} \times @{param.Y_MAX}$ 行列 $A = (A_{xy})$ ($0\leq x < @{param.X_MAX}$, $0\leq y < @{param.Y_MAX}$) があります。
はじめ、すべての $x, y$ に対して $A_{xy} = 0$ です。

まず、次のクエリを $N$ 個処理してください。

- `$l$ $d$ $r$ $u$ $w$`: $l\leq x < r$ かつ $d\leq y < u$ を満たすすべての成分 $A_{x,y}$ に $w$ を加算する。

その後、次のクエリを $Q$ 個処理してください。

- `$l$ $d$ $r$ $u$`: $l\leq x < r$ かつ $d\leq y < u$ を満たすすべての成分 $A_{x,y}$ の総和を $@{param.MOD}$ で割った余りを出力する。

@{lang.end}


## @{keyword.constraints}

- $@{param.N_MIN} \leq N \leq @{param.N_MAX}$
- $@{param.Q_MIN} \leq Q \leq @{param.Q_MAX}$
- $@{param.X_MIN} \leq l_i < r_i \leq @{param.X_MAX}$
- $@{param.Y_MIN} \leq d_i < u_i \leq @{param.Y_MAX}$
- $0 \leq w_i < @{param.MOD}$

## @{keyword.input}

~~~
$N$ $Q$
$l_0$ $d_0$ $r_0$ $u_0$ $w_0$
$\vdots$
$l_{N-1}$ $d_{N-1}$ $r_{N-1}$ $u_{N-1}$ $w_{N-1}$
$l_0$ $d_0$ $r_0$ $u_0$
$\vdots$
$l_{Q-1}$ $d_{Q-1}$ $r_{Q-1}$ $u_{Q-1}$
~~~

@{example.example_00}
