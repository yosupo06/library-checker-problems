## @{keyword.statement}

@{lang.en}
You are given a sequence $a_0, a_1, ..., a_{N - 1}$, consisting of $N$ integers.

Process $Q$ queries of the following types in order :

 - `0 $i$ $x$` :  
    - If $i < |a|$, insert $x$ immediately before $a_i$  
    - If $i = |a|$, insert $x$ after $a_{|a| - 1}$  
 - `1 $i$` : Remove $a_i$ (remaining elements will be concatenated)  
 - `2 $l$ $r$` : Reverse $a_l, a_{l + 1}, a_{l + 2}, \dots, a_{r - 1}$  
 - `3 $l$ $r$ $b$ $c$` : For each $i = l, l + 1, l + 2, \dots, {r - 1}$, $a_i \gets b \times a_i + c$  
 - `4 $l$ $r$` : Print $\sum_{i = l}^{r - 1} a_i \bmod @{param.MOD}$  

@{lang.ja}

長さ $N$ の数列 $a_0, a_1, ..., a_{N-1}$ に $Q$ 個のクエリが飛んできます。処理してください。

 - `0 $i$ $x$` :  
    - $i < |a|$ なら $x$ を $a_i$ の直前に挿入する  
    - $i = |a|$ なら $x$ を $a_{|a| - 1}$ の後に挿入する  
 - `1 $i$` : $a_i$ を削除する (残った要素は連結される)
 - `2 $l$ $r$` : $a_l, a_{l + 1}, a_{l + 2}, \dots, a_{r - 1}$ を反転する  
 - `3 $l$ $r$ $b$ $c$` : 各 $i = l, l + 1, l + 2, \dots, {r - 1}$ について $a_i \gets b \times a_i + c$  
 - `4 $l$ $r$` : $\sum_{i = l}^{r - 1} a_i \bmod @{param.MOD}$ を出力する  

@{lang.end}


## @{keyword.constraints}

@{lang.en}

 - $1 \le N, Q \le @{param.N_AND_Q_MAX}$
 - $0 \le a_i \lt @{param.MOD}$
 - For the format `0 $i$ $x$` :  
    - $0 \le i \le (|a|$ at the time$)$
    - $0 \le x \lt @{param.MOD}$
 - For the format `1 $i$` :  
    - $0 \le i \lt (|a|$ at the time$)$
 - For the format `2 $l$ $r$` :  
    - $0 \le l \lt r \le (|a|$ at the time$)$
 - For the format `3 $l$ $r$ $b$ $c$` :  
    - $0 \le l \lt r \le (|a|$ at the time$)$
    - $0 \le b \lt @{param.MOD}$
    - $0 \le c \lt @{param.MOD}$
 - For the format `4 $l$ $r$` :  
    - $0 \le l \lt r \le (|a|$ at the time$)$

@{lang.ja}

 - $1 \le N, Q \le @{param.N_AND_Q_MAX}$
 - $0 \le a_i \lt @{param.MOD}$
 - `0 $i$ $x$` 形式について :  
    - $0 \le i \le ($その時点での $|a|)$
    - $0 \le x \lt @{param.MOD}$
 - `1 $i$` 形式について :  
    - $0 \le i \lt ($その時点での $|a|)$
 - `2 $l$ $r$` 形式について :  
    - $0 \le l \lt r \le ($その時点での $|a|)$
 - `3 $l$ $r$ $b$ $c$` 形式について :  
    - $0 \le l \lt r \le ($その時点での $|a|)$
    - $0 \le b \lt @{param.MOD}$
    - $0 \le c \lt @{param.MOD}$
 - `4 $l$ $r$` 形式について :  
    - $0 \le l \lt r \le ($その時点での $|a|)$

@{lang.end}

## @{keyword.input}

~~~
$N$ $Q$
$a_0$ $a_1$ ... $a_{N - 1}$
$\textrm{Query}_0$
$\textrm{Query}_1$
:
$\textrm{Query}_{Q - 1}$
~~~

@{example.example_00}
