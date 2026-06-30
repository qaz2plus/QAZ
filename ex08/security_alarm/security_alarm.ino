#include <WiFi.h>
#include <WebServer.h>

// 修改为你的2.4G WiFi信息
const char* wifi_ssid = "qaz";
const char* wifi_pwd = "123456789";

WebServer server(80);
const uint8_t ledPin = 2;
const uint8_t touchPin = T0;

bool isArm = false;    // 布防状态
bool alarmOn = false;  // 报警触发状态

// HTML存入Flash，防止内存溢出
const char html_page[] PROGMEM = R"HTML(
<!DOCTYPE html>
<html lang="zh-CN">
<head>
<meta charset="utf-8">
<title>物联网安防报警主机</title>
<style>
body{text-align:center;margin-top:100px;}
button{font-size:26px;padding:16px 40px;margin:20px;}
#armBtn{background:#009933;color:#fff;}
#disarmBtn{background:#cc0000;color:#fff;}
</style>
</head>
<body>
<h2>安防布防控制界面</h2>
<a href="/arm"><button id="armBtn">一键布防 ARM</button></a>
<a href="/disarm"><button id="disarmBtn">一键撤防 DISARM</button></a>
</body>
</html>
)HTML";

// 首页
void rootPage()
{
  server.send_P(200, "text/html", html_page);
}

// 布防接口
void handleArm()
{
  isArm = true;
  server.sendHeader("Location","/");
  server.send(302, "text/plain", "");
}

// 撤防接口
void handleDisarm()
{
  isArm = false;
  alarmOn = false;
  digitalWrite(ledPin, LOW);
  server.sendHeader("Location","/");
  server.send(302, "text/plain", "");
}

void setup()
{
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);

  // WiFi连接
  WiFi.begin(wifi_ssid, wifi_pwd);
  while(WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.print("\nWiFi连接成功,设备IP:");
  Serial.println(WiFi.localIP());

  // 绑定路由
  server.on("/", rootPage);
  server.on("/arm", handleArm);
  server.on("/disarm", handleDisarm);
  server.begin();
}

void loop()
{
  server.handleClient();

  // 布防状态检测触摸报警
  if(isArm && !alarmOn)
  {
    int touchVal = touchRead(touchPin);
    if(touchVal < 300)
    {
      alarmOn = true;
    }
  }

  // 报警高频闪烁LED
  if(alarmOn)
  {
    digitalWrite(ledPin, HIGH);
    delay(100);
    digitalWrite(ledPin, LOW);
    delay(100);
  }
}