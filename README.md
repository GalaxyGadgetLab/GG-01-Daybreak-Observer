# 銀河ガジェット1号：黎明の観測者(Daybreak Observer)

>共に夜明けと新時代の幕開けを観測しようじゃないかッ!

## 概要
スピーカを搭載した親機を枕元に，停止用RFIDリーダを備えた子機をリビングに設置します．
アラーム時刻の設定は，同一ネットワーク内のデバイスからブラウザ経由で親機のWebサーバーへアクセスして行います．
リビングまで移動してラボの会員証(RFIDタグ)をかざさない限り，アラームは止まりません．

## 構成
## ハードウェア

### 親機(Parent Unit)
| Function | Component / Module | Interface |
| MCU | ESP32-WROOM-32E | - |
| Audio | DFPlayer Mini | UART |
| RTC | DS3231  | I2C |
| Display | 2.8"TFT(ILI9341) | SPI |

### 子機(Child Unit)
| Function | Component / Module | Interface |
| MCU | ESP32-WROOM-32E | - |
| RFID | MFRC522 (NFC Reader/Writer) | SPI |
| Indicator | High-brightness Red LED | GPIO |
| Alarm | Piezoelectric Buzzer | GPIO |

## PCB設計
本プロジェクトでは，専用のカスタム基板を設計・製作しました．
-**Design Tool：** KiCad 9.0

 

