# Library Checker Problems

[![CircleCI](https://circleci.com/gh/yosupo06/library-checker-problems/tree/master.svg?style=svg)](https://circleci.com/gh/yosupo06/library-checker-problems/tree/master)
[![Gitter](https://badges.gitter.im/library-checker-problems/community.svg)](https://gitter.im/library-checker-problems/community?utm_source=badge&utm_medium=badge&utm_campaign=pr-badge)

Source code of [https://judge.yosupo.jp](https://judge.yosupo.jp)

## library-checker-project

- problems: [library-checker-problems](https://github.com/yosupo06/library-checker-problems)
- judge: [library-checker-judge](https://github.com/yosupo06/library-checker-judge)
- frontend: [library-checker-frontend](https://github.com/yosupo06/library-checker-frontend)

## Requirements

- Linux / OS X
- python3.6+
- g++ or clang++ (--std=c++14, __int128_tが使える必要あり)

### (需要と余力があれば)対応予定

- Windows
- python3.5
- MSVC++
- __int128_tの除去

## How to Use

```sh
cd /path/to/library-checker-problems

pip3 install toml markdown
# or pip3 install -r requirements.txt

./generate.py problems.toml # generate testcase of all problems
./generate.py problems.toml -p unionfind # generate testcase of unionfind
```

## Contribution

issueを立てるほどじゃないけどちょっと気になるとか

- gitter(このREADMEの先頭の、chat on gitter ってやつをクリックすると飛べます)というチャットルームがあります

細かい修正(嘘解法, typo, この解答落ちるはずなんだけど！)

- issueを立ててくれると嬉しいです
- pull requestを送ってくれるともっと嬉しいです

このライブラリをベリファイしたいんだけど！

- https://github.com/yosupo06/library-checker-problems/issues/3 に書いてくれると嬉しいです

こんな感じの問題が欲しい!

- https://github.com/yosupo06/library-checker-problems/projects/1 の精査待ちを参考に issue を立ててくれると嬉しいです(クッソ雑でいいです)

精査待ち, 作業待ちの問題について、ここがおかしくない？ / ここはこうしたほうが良くない？

- お気軽に(その問題に対応するissueへ)コメントください

作業待ちに欲しい問題が入っているがもう待ちきれない！

- ゆるして
- https://github.com/yosupo06/library-checker-problems/blob/master/GUILDLINE.md と sample/aplusb を参考に準備してpull requestを送ってくれると嬉しいです

精査待ちに欲しい問題が入っているがもう待ちきれない！

- ゆるして

judge.yosupo.jpにこんな機能が欲しい！

- https://github.com/yosupo06/library-checker-frontend のissueに書いてくれると嬉しいです

ジャッジサーバーに攻撃完了です

- https://github.com/yosupo06/library-checker-judge のissueには書かずに、https://twitter.com/yosupot までこっそり教えてね

## ディレクトリ構成

sample/aplusbを参考にしてください

- info.toml: 問題のさまざまな情報
- gen/: ケース生成スクリプト
- sol/: 回答コード
- checker.cpp: output_checker
- task.md: 問題文

## 問題の追加

- problems.tomlにいい感じに追加する
- sample/aplusbディレクトリを参考に、いい感じに

## Thanks

checker, validatorなどに [testlib](https://github.com/MikeMirzayanov/testlib) を使用しています。
