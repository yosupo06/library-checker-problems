## @{keyword.statement}

@{lang.en}
A string $S$ consisting of lowercase English letters is given. Output the information of the eertree (also known as palindromic tree, or palindrome tree) of $S$ according to the following description.

- Let $P$ be the set of non-empty palindromic substrings of $S$, and let $n = |P|$.
- The eertree of $S$ consists of $2$ trees, which include $n$ vertices corresponding to the elements of $P$ and two special vertices called `ODD` and `EVEN`.
- Number the vertices of the eertree as follows:
    - The number of ODD is $-1$, and the number of EVEN is $0$.
    - Each other vertex $v$ corresponds to some $\mathrm{str}(v) \in P$. For $\mathrm{str}(v) = S_i \cdots S_{j-1}$, assign numbers $1, 2, \ldots, n$ to the vertices in ascending order of $j$, where $(i,j)$ is chosen such that $j$ is minimal.
    - For each vertex $v$ ($1 \leq v \leq n$), let $p_v$ be the number of its parent vertex. That is, $p_v$ is the number of the vertex corresponding to the palindrome obtained by removing the first and last characters of $\mathrm{str}(v)$. However, if $|\mathrm{str}(v)| = 2$, the parent is `EVEN` (number $0$), and if $|\mathrm{str}(v)| = 1$, the parent is `ODD` (number $-1$).
- For each vertex $v$ ($1 \leq v \leq n$), let $s_v$ be the destination of the suffix link from $v$. That is, $s_v$ is the number of the vertex corresponding to the largest non-empty palindromic suffix of $\mathrm{str}(v)$ that is shorter than $\mathrm{str}(v)$. If no such palindromic suffix exists, the suffix link destination is defined as `EVEN` (number $0$).

Output $n$ and $p_v, s_v$ for each $v$ ($1 \leq v \leq n$).

Additionally, for each $i = 1, 2, \ldots, |S|$, output the number of the vertex corresponding to the largest palindromic suffix of the prefix $S_0 \cdots S_{i-1}$ of length $i$.

@{lang.ja}
英小文字からなる文字列 $S$ が与えられます．$S$ の回文木（eertree, palindromic tree, palindrome tree などともいう）の情報を以下の説明に従って出力してください．

- $P$ を $S$ の空でない回文部分文字列からなる集合，$n = |P|$ とします．
- $S$ の eertree とは，$P$ の要素に対応する $n$ 頂点および `ODD`, `EVEN` という特別な頂点からなる $2$ つの木です．
- eertree の頂点には，次のように番号をつけてください．
    - `ODD` の番号は $-1$，`EVEN` の番号は $0$ とします．
    - それ以外の頂点 $v$ は，ある $\mathrm{str}(v)\in P$ と対応します．$\mathrm{str}(v)=S_i\cdots S_{j-1}$ となる $(i,j)$ を $j$ が最小となるようにとったとき，$j$ について昇順に頂点に $1, 2, \ldots, n$ の番号をつけてください．
- 頂点 $v$ ($1\leq v\leq n$) に対し，その親の頂点の番号を $p_v$ とします．
  つまり，$\mathrm{str}(v)$ の先頭と末尾の文字を削除してできる回文に対応する頂点の番号を $p_v$ とします．
  ただし，$|\mathrm{str}(v)|=2$ ならば親は `EVEN`（番号は $0$），$|\mathrm{str}(v)|=1$ ならば親は `ODD`（番号は $-1$）と定義します．
- 頂点 $v$ ($1\leq v\leq n$) に対し，$v$ からの suffix link の行き先を $s_v$ とします．つまり，$\mathrm{str}(v)$ の空でない接尾辞回文のうちで，$\mathrm{str}(v)$ より短いもののうち最大のものに対応する頂点を $s_v$ とします．ただし，そのような接尾辞回文が存在しない場合には suffix link の行き先は `EVEN` （番号は $0$） と定義します．

$n$ および，各 $v$ ($1\leq v\leq n$) に対する $p_v, s_v$ を出力してください．

さらに，各 $i = 1, 2, \ldots, |S|$ に対して，$S$ の長さ $i$ の接頭辞 $S_0\cdots S_{i-1}$ の最大回文接尾辞に対する頂点の番号 $v_i$ を出力してください．
@{lang.end}

## @{keyword.constraints}

@{lang.en}

- $@{param.MIN_N} \leq |S| \leq @{param.MAX_N}$
- Each character of $S$ is a lowercase English letter. 

@{lang.ja}

- $@{param.MIN_N} \leq |S| \leq @{param.MAX_N}$
- $S$ は英小文字からなる文字列．

@{lang.end}

## @{keyword.input}

```
$S$
```

## @{keyword.output}

```
$n$
$p_1$ $s_1$
$\vdots$
$p_n$ $s_n$
$v_1$ $\ldots$ $v_{|S|}$
```

## @{keyword.sample}

@{example.example_00}

@{example.example_01}

@{example.example_02}
