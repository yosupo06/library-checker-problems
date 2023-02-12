## @{keyword.statement}

@{lang.en}
@{lang.ja}
@{lang.end}

次の項目は以下のすべての問題で共通します：

- **入力** に現れる正の有理数は、既約分数 $a/b$ で表します。
- $0$ より大きい有理数と、 Stern–Brocot Tree (SBT) のノードを同一視します。
- SBT のノード $a/b$ が入出力に現れる場合、次の制約が付きます。
  - $1\leq a \leq @{param.TARGET_FRAC_MAX}$
  - $1\leq b \leq @{param.TARGET_FRAC_MAX}$
  - $a$ と $b$ は互いに素

Stern–Brocot Tree に関して、次のリストに含まれる問題が合計 $T$ 個与えられます。

- ENCODE_PATH

  $1/1$ から $a/b$ までの SBT におけるパスを、左の子に向かう移動を `L` 、右の子に向かう移動を `R` とした文字列で表します。この文字列を連長圧縮して、次の形式で出力してください。
  
  ```
  $k$ $c_0$ $n_0$ $c_1$ $n_1$ $\ldots$ $c_{k-1}$ $n_{k-1}$
  ```

  $c_i$ は `L` または `R` で、$n_i$ は $c_i$ が連続して並ぶ回数を表す正整数です。

  - 入力
    ```
    ENCODE_PATH $a$ $b$
    ```

  - 出力
    ```
    $k$ $c_0$ $n_0$ $c_1$ $n_1$ $\ldots$ $c_{k-1}$ $n_{k-1}$
    ``` 
  
- DECODE_PATH

  $1/1$ から $a/b$ までのパスが ENCODE_PATH の形式で与えられるので、$a$ , $b$ を出力してください。 

  - 制約 

    - $c_i\neq c_{i+1}$
    - $1\leq n_i\leq 10^9$
    - 正しい出力において $1\leq a\leq 10^9$ および $1\leq b\leq 10^9$ となることが保証される

  - 入力
    ```
    DECODE_PATH $k$ $c_0$ $n_0$ $c_1$ $n_1$ $\ldots$ $c_{k-1}$ $n_{k-1}$
    ```

  - 出力
    ```
    $a$ $b$
    ``` 

- LCA

  $a/b$ と $c/d$ の LCA $f/g$ を求め、出力してください。

  - 入力
    ```
    LCA $a$ $b$ $c$ $d$
    ```

  - 出力
    ```
    $f$ $g$
    ``` 

- ANCESTOR

  $a/b$ の祖先であって深さが $k$ のノード $f/g$ を出力してください。存在しなければ代わりに `-1` とだけ出力してください。

  - 制約 
  
    - $@{param.K_MIN_ANCESTOR} \leq k\leq @{param.K_MAX_ANCESTOR}$

  - 入力
    ```
    ANCESTOR $a$ $b$ $k$
    ```

  - 出力

    ```
    $f$ $g$
    ```

- CHILD

  $a/b$ の左の子 $f/g$ 、 $a/b$ の右の子 $h/k$ の順に出力してください。

  - 入力
    ```
    CHILD $a$ $b$
    ```

  - 出力

    ```
    $f$ $g$ $h$ $k$
    ```

- RANGE

  頂点 a/b の子孫の集合は、ある有理数開区間です。その左端 $f/g$ と右端 $h/k$ を出力してください。 $+\infty$ の場合は代わりに `1 0` 、 $0$ の場合は `0 1` として出力してください。

  - 入力

    ```
    RANGE $a$ $b$
    ```

  - 出力

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

@{lang.ja}

@{lang.end}

それぞれの問題文に従って出力してください。 $1$ 行に $1$ 問の答えを出力してください。

## @{keyword.sample}

@{example.example_00}
