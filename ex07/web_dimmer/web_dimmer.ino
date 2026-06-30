#include <WiFi.h>
#include <WebServer.h>

// 替换为你自己的2.4G WiFi，不能是5G、不能中文名称
const char* wifi_ssid = "qaz";
const char* wifi_pwd = "123456789";

WebServer server(80);
const uint8_t ledPin = 2;
int led_bright = 0;

// 关键：HTML页面必须定义在全局（所有函数外部），避免栈内存溢出
const char html_page[] PROGMEM = R"HTML(
<!DOCTYPE html>
<html lang="zh-CN">
<head>
<meta charset="utf-8">
<title>ESP32网页调光</title>
<style>
body{text-align:center;margin-top:100px;font-size:24px;}
input{width:85%;height:32px;margin-top:20px;}
</style>
</head>
<body>
<h2>PWM无极调光控制器</h2>
<p>当前亮度：<span id="num">0</span></p>
<input type="range" min="0" max="255" value="0" oninput="send(this.value)">
<script>
function send(val){
  document.getElementById("num").innerText = val;
  fetch("/set?b="+val);
}
</script>
</body>
</html>
)HTML";

// 首页接口
void rootPage()
{
  server.send_P(200, "text/html", html_page);
}

// 亮度调节接口
void setBrightness()
{
  if(server.hasArg("b"))
  {
    led_bright = server.arg("b").toInt();
    analogWrite(ledPin, led_bright);
  }
  server.send(200, "text/plain", "OK");
}

void setup()
{
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);
  analogWrite(ledPin, 0);

  // 连接WiFi
  WiFi.begin(wifi_ssid, wifi_pwd);
  while(WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.print("\nWiFi连接成功,设备IP:");
  Serial.println(WiFi.localIP());

  // 绑定网页路由
  server.on("/", rootPage);
  server.on("/set", setBrightness);
  server.begin();
}

void loop()
{
  server.handleClient();
}