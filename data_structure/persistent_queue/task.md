## @{keyword.statement}

@{lang.en}
Let $S_{-1}$ be an empty sequence.
Process the following $Q$ queries.
The $i$-th query is given in the following form.

- `0 $t_i$ $x_i$`: Define $S_i$ as the sequence obtained by adding $x_i$ to the end of $S_{t_i}$.
- `1 $t_i$`: Define $S_i$ as the sequence obtained by deleting the front element of $S_{t_i}$. Print the deleted element.
@{lang.ja}
$S_{-1}$ を空の列とします。
$Q$ 個のクエリを処理してください。
$i$ 個目のクエリは以下の形式で与えられます。

- `0 $t_i$ $x_i$`: $S_{t_i}$ の末尾に $x_i$ を追加した列を $S_i$ とする。
- `1 $t_i$`: $S_{t_i}$ の先頭を削除した列を $S_i$ とする。削除した要素を出力する。
@{lang.end}

## @{keyword.constraints}

@{lang.en}
- $@{param.Q_MIN} \leq Q \leq @{param.Q_MAX}$
- $-1 \leq t_i < i$
- $@{param.X_MIN} \leq x_i \leq @{param.X_MAX}$
- In query 1, $S_{t_i}$ is not empty.
@{lang.ja}
- $@{param.Q_MIN} \leq Q \leq @{param.Q_MAX}$
- $-1 \leq t_i < i$
- $@{param.X_MIN} \leq x_i \leq @{param.X_MAX}$
- クエリ 1 について、$S_{t_i}$ は空ではない。
@{lang.end}

## @{keyword.input}

~~~
$Q$
$\textrm{Query}_0$
$\textrm{Query}_1$
:
$\textrm{Query}_{Q-1}$
~~~

## @{keyword.sample}

@{example.example_00}
