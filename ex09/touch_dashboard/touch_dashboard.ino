#include <WiFi.h>
#include <WebServer.h>

// 修改为你的2.4G WiFi信息
const char* wifi_ssid = "qaz";
const char* wifi_pwd = "123456789";

WebServer server(80);
const uint8_t touchPin = T0;

// HTML存入Flash，防内存崩溃
const char html_page[] PROGMEM = R"HTML(
<!DOCTYPE html>
<html lang="zh-CN">
<head>
<meta charset="utf-8">
<title>触摸传感器实时仪表盘</title>
<style>
body{text-align:center;margin-top:120px;}
#dataShow{font-size:90px;color:#0066cc;font-weight:bold;}
</style>
</head>
<body>
<h2>实时触摸数值监控</h2>
<div id="dataShow">0</div>
<script>
function updateData(){
  fetch("/sensor")
  .then(res=>res.text())
  .then(val=>document.getElementById("dataShow").innerText=val);
}
setInterval(updateData, 200);
</script>
</body>
</html>
)HTML";

// 主页
void rootPage()
{
  server.send_P(200, "text/html", html_page);
}

// 传感器数据接口
void sensorData()
{
  int touchVal = touchRead(touchPin);
  server.send(200, "text/plain", String(touchVal));
}

void setup()
{
  Serial.begin(115200);

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
  server.on("/sensor", sensorData);
  server.begin();
}

void loop()
{
  server.handleClient();
}