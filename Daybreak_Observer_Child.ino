#include<WiFi.h>
#include<WebServer.h>
#include<HTTPClient.h>
#include<SPI.h>
#include<MFRC522.h>

const char *ssid="483E5E78354D-2G";
const char *pass="xx2pf9t9ctmthb";
IPAddress ip(192,168,3,102);
IPAddress gateway(192,168,3,1);
const char* stop_url="http://192.168.3.101/stop";

#define SWITCH 4
#define LED 13
#define BUZZER 14
#define SS_PIN 5
#define RST_PIN 22
MFRC522 mfrc522(SS_PIN, RST_PIN);

bool is_alarm=false;

WebServer server(80);

//親機のアラームがONになったときの処理
void handleAlarm()
{
  is_alarm=true;
  digitalWrite(LED,HIGH);
  Serial.println("Alarm started");
  server.send(200,"text/plain","Alarm started");
}

//無効なURLが指定された場合
void handleNotFound()
{
  String messege="Not Found:";
  messege+=server.uri();
  server.send(404,"text/plain","messege");
}

void setup() {
  Serial.begin(115200);
  
  SPI.begin();
  mfrc522.PCD_Init();

  //GPIO設定
  pinMode(SWITCH,INPUT_PULLDOWN);
  pinMode(LED,OUTPUT);
  pinMode(BUZZER,OUTPUT);
  digitalWrite(LED,LOW);
  digitalWrite(BUZZER,LOW);

  //WiFi接続
  WiFi.begin(ssid,pass);
  while(WiFi.status()!=WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  WiFi.config(ip,gateway,WiFi.subnetMask(),IPAddress(8,8,8,8),IPAddress(8,8,4,4));
  Serial.println("");
  Serial.println("WiFi Connected.");

  //WebServerの初期化
  server.on("/alarm",handleAlarm);
  server.onNotFound(handleNotFound);
  server.begin();
}

void loop()
{
  //Webサーバを動作させる
  server.handleClient();

  if(is_alarm)
  {
     if(mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial())
     {
      Serial.println("RFID detected.");
      digitalWrite(BUZZER,HIGH);
      delay(100);
      digitalWrite(BUZZER,LOW);
      digitalWrite(LED,LOW);

      HTTPClient http;
      http.begin(stop_url);
      int httpCode=http.GET();
      http.end();

      is_alarm = false;

      mfrc522.PICC_HaltA();       // カードとの通信を終了
      mfrc522.PCD_StopCrypto1();  // リーダーの暗号化通信を停止

      delay(500);
     }
  }
}
