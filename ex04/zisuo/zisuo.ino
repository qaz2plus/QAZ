// 引脚定义
const int touchPin = T0;
const int ledPin = 2;

// 状态变量
bool ledState = LOW;        // LED自锁状态
bool lastTouch = false;     // 上一次触摸状态
unsigned long debounceTime = 50; // 防抖延时ms
unsigned long lastDebounce = 0; // 防抖计时

void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
  digitalWrite(ledPin, ledState);
}

void loop() {
  unsigned long now = millis();
  bool currentTouch = touchRead(touchPin) > 300; // 触摸阈值30，可微调

  // 防抖判断
  if ((currentTouch != lastTouch) && (now - lastDebounce > debounceTime)) {
    lastDebounce = now;
    // 边缘检测：上次未触摸，本次触摸 → 触发翻转
    if (currentTouch == true && lastTouch == false) {
      ledState = !ledState;
      digitalWrite(ledPin, ledState);
    }
  }
  lastTouch = currentTouch;
}