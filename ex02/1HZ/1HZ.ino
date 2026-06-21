// 定义LED引脚，ESP32板载LED对应GPIO 2
const int ledPin = 2;
// 1Hz闪烁时间间隔：亮500毫秒、灭500毫秒
const unsigned long interval = 500;
unsigned long previousTime = 0;
bool ledState = LOW;

void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);
}

void loop() {
  // 获取系统当前运行总毫秒数
  unsigned long currentTime = millis();
  // 判断是否达到设定的间隔时间
  if (currentTime - previousTime >= interval) {
    previousTime = currentTime;
    // 翻转LED亮灭状态
    ledState = !ledState;
    digitalWrite(ledPin, ledState);
  }
}