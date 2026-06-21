// ESP32板载LED引脚定义
const int ledPin = 2;
// SOS时序定义：短亮、长亮、字符间隔、整套循环间隔
const unsigned long shortLight = 200;
const unsigned long longLight = 600;
const unsigned long gapOff = 200;
const unsigned long cycleStop = 1500;

unsigned long prevTime = 0;
bool ledState = LOW;
// 状态机：0=3短闪，1=3长闪，2=3短闪，3=整套结束停顿
int workStage = 0;
int flashCnt = 0;

void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);
}

void loop() {
  unsigned long curTime = millis();
  // 判断当前是亮灯时长还是熄灭间隔
  unsigned long waitTime = ledState ? (workStage == 0 || workStage == 2 ? shortLight : longLight) : gapOff;
  
  if (curTime - prevTime >= waitTime) {
    prevTime = curTime;
    ledState = !ledState;
    digitalWrite(ledPin, ledState);
    
    // 熄灭时计数，切换阶段
    if (!ledState) {
      flashCnt++;
      if (flashCnt >= 3) {
        flashCnt = 0;
        workStage++;
        // 整套SOS完成，长停顿后重置
        if (workStage >= 3) {
          workStage = 0;
          prevTime = curTime + cycleStop;
        }
      }
    }
  }
}