# ((repository name))

((problem URL))

((ranking)) 位

generated from https://github.com/buyoh/atcoder-hc-tmpl

# mmworkspace

workspace for heuristic contest

based on https://github.com/buyoh/codetesting

# quick start guide

- `F5`
  - `"[local] g++ - Build and debug active file"`
  - デバッグ実行する。入力は `stdin/default.txt`。
- `ctrl + shift + B`
  - 今開いているファイルをビルドする
  - 成果物は out ディレクトリに配置される
- Run Test Task (shortcutkey unassigned)
  - stdin ディレクトリにあるファイルを入力として実行する。
  - 結果は out に格納される。
  - https://code.visualstudio.com/docs/getstarted/keybindings#_tasks によると、ショートカットキーが無いので、コマンドパレットから適宜設定する

# submission code rules

- 標準エラーの末尾行にスコアを出力すること

# directory rules

- stdin
  - 手作業で作成あるいは配布された入力データを配置
  - 好きにして良い
  - `default.txt` は デバッグ実行に使用
  - それ以外のファイル名は任意
  - ディレクトリの作成は非推奨
- src
  - ソースコードを配置
  - 好きにして良い
- bin
  - コードのビルドや実行に関連するスクリプトを配置
  - ファイル名は変更しない
  - 例えばソースコードを別の言語に置き換える場合に中身を書き換える
- script
  - 大量にテストケースを回すとき等のルーチンの記述をしたスクリプトを配置
  - リポジトリメンテナンス以外ではファイル名、中身は変更しない
- out
  - 生成物フォルダ

# commandline arguments

TODO

# sample problem

ナップサック問題が入っています

```
N C
v_1 w_1
...
v_N w_N
```

N = 10 : アイテムの個数
C = 100 : 選択できるアイテムの総重量
v_i : アイテムの価値
w_i : アイテムの重量
