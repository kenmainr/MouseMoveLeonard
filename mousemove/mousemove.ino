#include <Mouse.h>

const int LED = 13;                         //点滅させるLEDを指定
const int BUTTON = 7;                       //ON-OFFトグルスイッチを指定
const int MOUSEMOVEDELTA         = 4;        //マウス移動量
const unsigned long MOVEINTERVAL = 45000UL; //マウス移動間隔 *0.001 秒
const unsigned long blinkPattern[2][4] = {  //点滅パターン
    {1000, 100 , 100 , 100 },
    {LOW , HIGH, LOW , HIGH}
  };

const int S_ON = 0;
const int S_OFF = 1;

//初期設定
void setup() {
  Mouse.begin();
  pinMode(LED, OUTPUT);
  pinMode(BUTTON, INPUT);
  digitalWrite(LED, HIGH);
}

//1,ボタン状態を検知
//2.状態ONならマウス起動と、LED点滅処理を行う
void loop() {
  if (checkState() == 0){
    mouseMove();
    blinkLED();
  }else{
    digitalWrite(LED, LOW);
  }
}

//ボタン状態を取得し、LOW->HIGHの変更時(クリック時）にボタン状態を反転
// 返値{S_ON/S_OFF}
int checkState(){
  static int button_state = S_ON;
  static int button_val = HIGH;
  static int old_button_val = HIGH;

  button_val = digitalRead(BUTTON);
  if((button_val == HIGH) && (old_button_val == LOW)){ 
    button_state = 1 - button_state;
    delay(10);
  }
  old_button_val = button_val;
  return button_state;
}

//定期的にマウス移動を行う 返値{0:処理スキップ,1:処理}
int mouseMove() {
  static int mouseMoveSign = 1;
  static unsigned long lastMillis = 0; 
  if (  (millis() < lastMillis) or (millis() - lastMillis) > MOVEINTERVAL) {
    lastMillis = millis();
    Mouse.move(MOUSEMOVEDELTA * mouseMoveSign, 0, 0);
    mouseMoveSign = 0 - mouseMoveSign;
    return 1;
  }else{
    return 0;
  }
}

//LED 点滅　返値{0:処理スキップ,1:処理}
int blinkLED() {
  static unsigned long lastMillis = 0;
  static int state = 0;
  if (  (millis() - lastMillis) > blinkPattern[0][state]) {
    lastMillis = millis();
    digitalWrite(LED, blinkPattern[1][state]);
    if (++state > 3)state = 0;
    return 1;
  }else{
    return 0;
  }
}
