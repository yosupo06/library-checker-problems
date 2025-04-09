## @{keyword.statement}

@{lang.en}
You are given strings $S_0, \dots, S_{N-1}$, each consisting of lowercase English letters. Output the information of the Trie constructed from these strings according to the following description.

- Let $P_{i,j}$ denote the prefix of length $j$ of $S_i$ (where $0 \leq j \leq |S_i|$).
- Define the set $P$ as $P = { P_{i,j} \mid 0 \leq i < N, 0 \leq j \leq |S_i| }$. Let $n = |P|$.
- The Trie of $(S_0, \dots, S_{N-1})$ is a tree consisting of $n$ vertices, corresponding to the elements of $P$.
Each vertex $v$ in the Trie corresponds to some $\mathrm{str}(v) \in P$. 
  - When choosing $(i, j)$ such that $\mathrm{str}(v) = P_{i,j}$, assign a number $0, 1, \dots, n-1$ to the vertices in lexicographical order of $(i, j)$ with $i$ minimized. In particular, $\mathrm{str}(0)$ is the empty string.
- For each vertex $v$ ($1 \leq v < n$), let $p_v$ denote the number of the parent vertex. In other words, $p_v$ is the number of the vertex corresponding to the string obtained by removing the last character from $\mathrm{str}(v)$.
- For each vertex $v$ ($1 \leq v \leq n$), let $s_v$ denote the suffix link destination. That is, $s_v$ is the number of the vertex corresponding to the largest suffix of $\mathrm{str}(v)$ that belongs to $P$ and is shorter than $\mathrm{str}(v)$.

Output the value of $n$, and for each vertex $v$ ($1 \leq v < n$), output $p_v$ and $s_v$. Additionally, for each $i = 0, 1, \dots, N-1$, output the number of the vertex corresponding to $S_i$.

@{lang.ja}
英小文字からなる文字列 $S_0,\ldots,S_{N-1}$ が与えられます．これらからなる Trie の情報を以下の説明に従って出力してください．

- $P_{i,j}$ を $S_i$ の長さ $j$ の接頭辞とします（$0\leq j\leq |S_i|）．
- 集合 $P$ を $P=\lbrace P_{i,j}\mid 0\leq i<N, 0\leq j\leq |S_i|\rbrace$ で定めます．$n = |P|$ とします．
- $(S_0,\ldots,S_{N-1})$ の Trie とは，$P$ の要素に対応する $n$ 頂点からなる木です．
  - Trie の頂点 $v$ は，ある $\mathrm{str}(v)\in P$ と対応します．$\mathrm{str}(v)=P_{i,j}$ となる $(i,j)$ を $i$ が最小となるようにとったとき，$(i,j)$ について辞書順昇順に頂点に $0, 1, \ldots, n-1$ の番号をつけてください．特に，$\mathrm{str}(0)$ は空文字列です．
- 頂点 $v$ ($1\leq v < n$) に対し，その親の頂点の番号を $p_v$ とします．つまり， $\mathrm{str}(v)$ から末尾 $1$ 文字を削除してできる文字列に対応する頂点の番号を $p_v$ とします．
- 頂点 $v$ ($1\leq v\leq n$) に対し，$v$ からの suffix link の行き先を $s_v$ とします．つまり，$\mathrm{str}(v)$ の接尾辞であって $P$ に属し $\mathrm{str}(v)$ より短いもののうち最大のものに対応する頂点を $s_v$ とします．

$n$ および，各 $v$ ($1\leq v\leq n-1$) に対する $p_v, s_v$ を出力してください．
さらに，各 $i=0,1,\ldots,N-1$ に対して $S_i$ に対応する頂点の番号 $v_i$ を出力してください．
@{lang.end}

## @{keyword.constraints}

@{lang.en}

- $@{param.MIN_N} \leq N \leq @{param.MAX_N}$
- $@{param.MIN_S_SUM} \leq |S_i| \leq @{param.MAX_S_SUM}$
- $@{param.MIN_S_SUM} \leq \sum_{0\leq i<N}|S_i| \leq @{param.MAX_S_SUM}$
- Each character of $S$ is a lowercase English letter. 

@{lang.ja}

- $@{param.MIN_N} \leq N \leq @{param.MAX_N}$
- $@{param.MIN_S_SUM} \leq |S_i| \leq @{param.MAX_S_SUM}$
- $@{param.MIN_S_SUM} \leq \sum_{0\leq i<N}|S_i| \leq @{param.MAX_S_SUM}$
- $S_i$ は英小文字からなる文字列．

@{lang.end}

## @{keyword.input}

```
$N$
$S_0$
$\vdots$
$S_{N-1}$
```

## @{keyword.output}

```
$n$
$p_1$ $s_1$
$\vdots$
$p_{n-1}$ $s_{n-1}$
$v_0$ $\ldots$ $v_{N-1}$
```

## @{keyword.sample}

@{example.example_00}

@{example.example_01}

@{example.example_02}
