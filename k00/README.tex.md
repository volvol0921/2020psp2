# 課題0 レポート

aa83988848 薗田光太郎

## 課題

標本男性の中で身長の最大値と最小値を求めよ．

## ソースコードの説明

l.14: データファイル名を入力させ，fnameに格納

l.15: 入力させた文字列の最後にエンターキーが入っているので，fnameの文字列の最後をヌル文字'\0'に置換

l.16: fnameを確認

l.18: fnameで指定したファイルの先頭アドレスをファイルポインタ fp に読み込む

l.19: もしfpがNULLだったときは，ファイルを開けなかったので，即座にプログラム終了

l.24: ファイルを1行ずつbufに読み込む．もし読み込み成功する限り以下を繰り返す

l.25: bufからscanfで数値文字列を実数としてvalに読み込む

l.26: もしvalがmax_valより大きければ，max_valにvalを代入して更新．

l.29: もしvalがmin_valより小さければ，min_valにvalを代入して更新．

l.34: ファイルを閉じる．閉じれないときは，即座にプログラム終了．

l.39: 最大値max_valを出力

l.40: 最小値min_valを出力

## 出力結果

```
input the filename of sample:../sample/heights_male.csv
the filename of sample: ../sample/heights_male.csv
Highest: 183.870000
Lowest: 167.830000
```

## 修正履歴

