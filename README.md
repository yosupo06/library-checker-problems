[![Build Status](https://drone.yosupo.jp/api/badges/yosupo06/library-checker-problems/status.svg)](https://drone.yosupo.jp/yosupo06/library-checker-problems)

# ケース生成

```
cd /path/to/library-checker-problems
./generate.py problems.toml
./generate.py problems.toml -p unionfind # 問題指定
```

# ディレクトリ構成

sample/aplusbを参考にしてください

- info.toml: 問題のさまざまな情報
- gen/: ケース生成スクリプト
- sol/: 回答コード
- checker.cpp: output_checker
- task.md: 問題文

# 問題の追加

- problems.tomlにいい感じに追加する
- sample/aplusbディレクトリを参考に、いい感じに


# library-checker-project

- problems: [library-checker-problems](https://github.com/yosupo06/library-checker-problems)
- judge: [library-checker-judge](https://github.com/yosupo06/library-checker-judge)
- frontend: [library-checker-frontend](https://github.com/yosupo06/library-checker-frontend)

# Contribution

細かい修正(嘘解法, typo, この解答落ちるはずなんだけど！)
- issueを立ててくれると嬉しいです
- pull requestを送ってくれるともっと嬉しいです

このライブラリをベリファイしたいんだけど！
- https://github.com/yosupo06/library-checker-problems/issues/3 に書いてくれると嬉しいです

こんな感じの問題が欲しい!
- https://github.com/yosupo06/library-checker-problems/projects/1 の精査待ちを参考に issue を立てて、精査待ちに追加してくれると嬉しいです

この問題が欲しい！
- https://github.com/yosupo06/library-checker-problems/projects/1 の作業待ちを参考に issue を立てて、精査待ちに追加してくれると嬉しいです 制約は https://github.com/yosupo06/library-checker-problems/blob/master/GUILDLINE.md も参考にしてください

精査待ち, 作業待ちの問題について、ここがおかしくない？ / ここはこうしたほうが良くない？
- お気軽に(その問題に対応するissueへ)コメントください

作業待ちに欲しい問題が入っているがもう待ちきれない！
- ゆるして
- https://github.com/yosupo06/library-checker-problems/blob/master/GUILDLINE.md と sample/aplusb を参考に準備してpull requestを送ってくれると嬉しいです

精査待ちに欲しい問題が入っているがもう待ちきれない！
- ゆるして

# Thanks

checker, validatorなどにtestlib (https://github.com/MikeMirzayanov/testlib) を使用しています。
