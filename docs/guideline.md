# 問題の作り方

以下の物が必要になります。なお、全てを準備する必要はなく、部分的な準備でも十分ありがたいです(出来たところまででpull requestを飛ばして貰えば大丈夫です)。

- フォルダの作成
- task.md(問題文)
- sol/correct.cpp(想定解)
- verifier.cpp(input checker)
- checker.cpp(output checker)
- gen/example_00.in, gen/example_01.in, gen/random.cppなど(ジェネレーター)
- info.toml

## フォルダの作成

問題を置くフォルダを決めます。
問題ID(例: `unionfind`) は既に決まっているはずなので、それっぽいジャンル(例: `datastructure`)を選んで
`datastructure/unionfind` にフォルダを作ればいいです。ジャンルは大体悩むことはないと思うんですが、微妙な場合でもフィーリングでいいです(後から変えられるので)

## task.md(問題文)

markdown + mathjax 形式です。他のtask.mdをコピペして弄ればいいと思います。
伝わればいいので、細かいところは気にしないで大丈夫です。

## sol/correct.cpp(想定解)

想定解です。

普通の競プロと全く同じように、標準入力から受け取って標準出力に書くのを書けば大丈夫です。
コーディング規約とかも無いんで普段使いのテンプレートとか使っても大丈夫です。ただしあまりに大量ならちゃんと使わない部分を消して欲しいです。

以下のことを守らないとCIが通らないはずです。

- 言語はC++
- bits/stdc++.hを使わない
- 警告を無視しない
- 出力ファイルが手元とCIで全く同じ、以下のことに注意するといいです
  - 乱数: rand(), uniform_int_distribution, shuffleを使わない
  - 構築: sortで同率の要素の順序によって出力が変わらないか(stable_sortにする必要があるかも？)

## verifier.cpp(input checker)

入力が、制約を満たしているかを確認するコードです。
[https://codeforces.com/blog/entry/18426](https://codeforces.com/blog/entry/18426) と同じように書けば大丈夫です。
他の問題のverifier.cppも参考にやれば、よっぽど変な制約じゃ無い場合大丈夫だと思います。

## checker.cpp(output checker)

参加者の出力が、条件を満たしているか判定するコードです。

ジャッジ内容が完全一致の場合、`/sample/aplusb/checker.cpp` をコピーするだけで終わりです。

スペシャルジャッジの場合は大変です。[https://codeforces.com/blog/entry/18431](https://codeforces.com/blog/entry/18431) を参考に書いてください。

## gen/example_00.in, gen/example_01.in, gen/random.cppなど(ジェネレーター)

テストケースです。[問題の作り方](generator.md)を参考にすると追加できます。

- example_00.in は欲しい(サンプルは1個は欲しい)
- random.cpp という名前でランダムケースが3 ~ 5個ぐらい欲しい
- 後は適当に(テストケースはどんどん追加していく想定なんで、弱くていいです)
- 最初の段階なら嘘解法はいらないです

あたりが注意点です

## info.toml

準備が無事にできたら、これをinfo.tomlに書き込み、手元で動かしてみることができます。
動かし方は [README](../README.md) の How to Use 通りに
