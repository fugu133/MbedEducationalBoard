# Mbed Educational Board
マイコン教育用として開発した基板になります．  
ベースは[mbed LPC1768](https://os.mbed.com/platforms/mbed-LPC1768/)でmbed OSを使ってプロトタイピング開発が可能です.  

サイズが75mm x 55mmの基板に以下の機能が搭載されています．
* タクトスイッチ x4
* アナログボリューム x3
* 完全絶縁のモータドライバ x2
* 6軸IMUセンサ x1
* トランスデューサ x1
* USBコネクタ x1
* GPIO x5 (内2つはI2C)

初学者向けに周辺機器を動かすための[ドライバ](https://github.com/fugu133/MbedEducationalBoard/tree/main/mbed/flib)を用意しているので簡単に扱えるかと思います．

比較的簡単にはんだ付けができるよう一部モジュール基板を使用しています．  
この基板一枚で簡単なロボットも作ることができます！

<img src="https://user-images.githubusercontent.com/62766332/222352534-bcca6b25-83e9-4362-a7ba-4657dda806e8.jpg" width="300">
