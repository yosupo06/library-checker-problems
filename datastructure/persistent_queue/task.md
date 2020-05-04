## {{keyword.statement}}
$S_{-1}$ を空の列とします。
$Q$ 個のクエリを処理してください。
$i$ 個目のクエリは以下の形式で与えられます。

- `0 $t_i$ $x_i$`: $S_{t_i}$ の末尾に $x_i$ を追加した列を $S_i$ とする。
- `1 $t_i$`: $S_{t_i}$ の先頭を削除した列を $S_i$ とする。削除した要素を出力する。

## {{keyword.constraints}}

- ${{param.Q_MIN}} \le Q \le {{param.Q_MAX}}$
- $-1 \le t_i \lt i$
- ${{param.X_MIN}} \le x_i \le {{param.X_MAX}}$
- クエリ 1 について、$S_{t_i}$ は空ではない

## {{keyword.input}}

~~~
$Q$
$\textrm{Query}_0$
$\textrm{Query}_1$
:
$\textrm{Query}_{Q-1}$
~~~

{{example.example_00}}
