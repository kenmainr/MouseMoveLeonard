# MouseMoveLeonard
Arduino Leonard Mouse Move Regularly

## これは何か

マウスを定期的に　動かすためのAruduino Leonard 用 スケッチです。
以下を必要に応じて設定して Arduino に書き込めば　定期的にマウスを動かせます。
```
const int LED = 13;                         //点滅させるLEDを指定
const int BUTTON = 7;                       //ON-OFFトグルスイッチを指定
const int MOUSEMOVEDELTA         = 4;        //マウス移動量
const unsigned long MOVEINTERVAL = 45000UL; //マウス移動間隔 *0.001 秒
const unsigned long blinkPattern[2][4] = {  //点滅パターン
    {1000, 100 , 100 , 100 },
    {LOW , HIGH, LOW , HIGH}
  };
```
各種用途にお使いください :-)