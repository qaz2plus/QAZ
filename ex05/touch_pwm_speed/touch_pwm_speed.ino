const int touchPin = T0;
const int ledPin = 2;

// 触摸防抖
bool lastTouch = false;
unsigned long debounceTime = 50;
unsigned long lastDebounce = 0;

// 呼吸档位
int speedLevel = 1; // 1/2/3三档
int step1 = 5;  // 1档慢速步长
int step2 = 12; // 2档中速
int step3 = 20; // 3档快速
int brightness = 0;
int fadeStep = 5;

void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  unsigned long now = millis();
  bool currentTouch = touchRead(touchPin) > 300;

  // 触摸切换档位逻辑
  if ((currentTouch != lastTouch) && (now - lastDebounce > debounceTime)) {
    lastDebounce = now;
    if (currentTouch && !lastTouch) {
      // 档位循环 1→2→3→1
      speedLevel++;
      if (speedLevel > 3) speedLevel = 1;
      // 根据档位修改呼吸步长
      switch(speedLevel){
        case 1: fadeStep = step1; break;
        case 2: fadeStep = step2; break;
        case 3: fadeStep = step3; break;
      }
    }
  }
  lastTouch = currentTouch;

  // PWM呼吸灯逻辑
  analogWrite(ledPin, brightness);
  brightness += fadeStep;
  if (brightness >= 255 || brightness <= 0) {
    fadeStep = -fadeStep;
  }
  delay(10);
}