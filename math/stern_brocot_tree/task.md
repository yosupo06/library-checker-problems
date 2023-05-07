## @{keyword.statement}

@{lang.en}
The following are true for all problems.

- Positive rational number in input/output is represented by irreducible fraction $a/b$.
- Positive rational numbers are identified with nodes in Stern–Brocot Tree (SBT). 
- If a node $a/b$ of SBT appears in **input**, $a, b$ satisfies following constraints:
  - $1\leq a \leq @{param.TARGET_FRAC_MAX}$
  - $1\leq b \leq @{param.TARGET_FRAC_MAX}$
  - $a$ and $b$ are comprime.
@{lang.ja}
次の項目は以下のすべての問題で共通します：

- 入出力に現れる正の有理数は、既約分数 $a/b$ で表します。
- $0$ より大きい有理数と、 Stern–Brocot Tree (SBT) のノードを同一視します。
- SBT のノード $a/b$ が **入力** に現れる場合、次の制約が付きます。
  - $1\leq a \leq @{param.TARGET_FRAC_MAX}$
  - $1\leq b \leq @{param.TARGET_FRAC_MAX}$
  - $a$ と $b$ は互いに素
@{lang.end}

@{lang.en}
$T$ problems related to SBT in the following list are given. 
@{lang.ja}
Stern–Brocot Tree に関して、次のリストに含まれる問題が合計 $T$ 個与えられます。
@{lang.end}

- ENCODE_PATH

  @{lang.ja}
  $1/1$ から $a/b$ までの SBT におけるパスを、左の子に向かう移動を `L` 、右の子に向かう移動を `R` とした文字列で表します。この文字列を連長圧縮して、次の形式で出力してください。
  @{lang.en}
  Represent the path from $1/1$ to $a/b$ in SBT as a string, using `L` for leftward move and `R` for rightward move. 
  Compress the string using run-length encoding and output it in the following format.
  @{lang.end}
  ```
  $k$ $c_0$ $n_0$ $c_1$ $n_1$ $\ldots$ $c_{k-1}$ $n_{k-1}$
  ```

  @{lang.ja}
  $c_i$ は `L` または `R` で、$n_i$ は $c_i$ が連続して並ぶ回数を表す正整数です。
  @{lang.en}
  Here, $c_i$ is `L` or `R`, and $n_i$ is a positive integer representing the number of consecutive $c_i$s. 
  @{lang.end}

  - @{keyword.input}
    ```
    ENCODE_PATH $a$ $b$
    ```

  - @{keyword.output}
    ```
    $k$ $c_0$ $n_0$ $c_1$ $n_1$ $\ldots$ $c_{k-1}$ $n_{k-1}$
    ``` 
  
- DECODE_PATH

  @{lang.ja}
  $1/1$ から $a/b$ までのパスが ENCODE_PATH の形式で与えられるので、$a$ , $b$ を出力してください。 
  @{lang.en}
  The path from $1/1$ to $a/b$ is given in the format of ENCODE_PATH. 
  Print $a, b$. 
  @{lang.end}

  - @{keyword.constraints}

  @{lang.ja}
    - $c_i\neq c_{i+1}$
    - $1\leq n_i\leq 10^9$
    - 正しい出力において $1\leq a\leq 10^9$ および $1\leq b\leq 10^9$ となることが保証される
  @{lang.en}
    - $c_i\neq c_{i+1}$
    - $1\leq n_i\leq 10^9$
    - It is guaranteed that the answer satisfies $1\leq a\leq 10^9$ and $1\leq b\leq 10^9$.
  @{lang.end}

  - @{keyword.input}
    ```
    DECODE_PATH $k$ $c_0$ $n_0$ $c_1$ $n_1$ $\ldots$ $c_{k-1}$ $n_{k-1}$
    ```

  - @{keyword.output}
    ```
    $a$ $b$
    ``` 

- LCA
  @{lang.ja}
  $a/b$ と $c/d$ の LCA $f/g$ を求め、出力してください。
  @{lang.en}
  Print the LCA $f/g$ of $a/b$ and $c/d$.
  @{lang.end}

  - @{keyword.input}
    ```
    LCA $a$ $b$ $c$ $d$
    ```

  - @{keyword.output}
    ```
    $f$ $g$
    ``` 

- ANCESTOR

  @{lang.ja}
  $a/b$ の祖先であって深さが $k$ のノード $f/g$ を出力してください。存在しなければ代わりに `-1` とだけ出力してください。
  @{lang.en}
  Print the ancestor $f/g$ of $a/b$ with depth $k$. If it does not exists, just print `-1`.
  @{lang.end}

  - @{keyword.constraints}
  
    - $@{param.K_MIN_ANCESTOR} \leq k\leq @{param.K_MAX_ANCESTOR}$

  - @{keyword.input}
    ```
    ANCESTOR $k$ $a$ $b$
    ```

  - @{keyword.output}

    ```
    $f$ $g$
    ```

- RANGE

  @{lang.ja}
  頂点 a/b の子孫の集合は、ある有理数開区間です。その下限 $f/g$ と上限 $h/k$ を出力してください。ただし、 $+\infty$ の場合は `1 0` 、 $0$ の場合は `0 1` と出力してください。
  @{lang.en}
  The set of descendants of a/b forms an open interval of rational numbers. 
  Print the infimum $f/g$ and the supremum $h/k$ of the interval. 
  Exceptionally, print `0 1` for a $0$ , `1 0` for a $+\infty$ .
  @{lang.end}

  - @{keyword.input}

    ```
    RANGE $a$ $b$
    ```

  - @{keyword.output}

    ```
    $f$ $g$ $h$ $k$
    ```


## @{keyword.constraints}

- $@{param.T_MIN} \leq T \leq @{param.T_MAX}$

## @{keyword.input}

```
$T$
$\text{query}_0$
$\text{query}_1$
$\vdots$
$\text{query}_{T-1}$
```

## @{keyword.output}

@{lang.en}
Print the answer to each problem on a separate line.
@{lang.ja}
それぞれの問題文に従って出力してください。 $1$ 行に $1$ 問の答えを出力してください。
@{lang.end}

## @{keyword.sample}

@{example.example_00}
