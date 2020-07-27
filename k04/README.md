# 課題4 レポート

bb35314039 富岡 大輝

## 課題

[../sample/heights.csv]は標本全体（男性と女性合わせた14人）のデータをまとめたものである．
一方，[../sample/IDs.csv]は標本14人の学籍番号（身長データと同じ順番）である．
学籍番号を尋ねて，その学籍番号のデータがリストにあれば，学籍番号，身長，性別のデータを表示し，リストになければ，「No data」と表示せよ．

この二つのファイルを読み取り，学籍番号，身長，性別の3つをメンバーとする構造体の配列で管理するとよい．

## ソースコードの説明

- l69-81: 動的配列から特定の ID を持つ要素を線形探索で探す。
- l94-97: CSV のヘッダ行をスキップするため 1 行読む。
- l107-121: 1 レコードずつ読み，動的配列に加えていく。
- l134-160: ID のファイルを読み，要素に ID を書いていく。行数が合わなかったらエラーで終了。
- l171-177: 結果を出力。

## 入出力結果

例えば，ID 45313125のデータを調べたいとき，

```
Input the filename of sample height : ../sample/heights.csv
Input the filename of sample ID : ../sample/IDs.csv
Which ID's data do you want? : 45313125
---
ID : 45313125
gender : Female
height : 152.4
```

例えば，ID 45313124のデータを調べたいとき，

```
Input the filename of sample height : ../sample/heights.csv
Input the filename of sample ID : ../sample/IDs.csv
Which ID's data do you want? : 45313124
---
No data
```

## 修正履歴

[comment #20200727 moto]
- OKです。