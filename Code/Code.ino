#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "NEERANJANAM";
const char* pass = "20#ENTE_NET#21";
const int pin = 10;
WebServer server(80);

void handleRoot() {
  String html = "<html><body>";
  html += "<style>";
  html += "@import url('https://fonts.googleapis.com/css2?family=Ubuntu:wght@300&display=swap');";
  html += "body {";
  html += "     background-color: aquamarine;";
  html += "     font-family: 'ubuntu';";
  html += "}";
  html += "#onB {";
  html += "     border: 5px solid green;";
  html += "     border-radius: 30px;";
  html += "     background-color: rgb(6,158,92);";
  html += "}";
  html += "#offB {";
  html += "     border: 5px solid red;";
  html += "     border-radius: 30px;";
  html += "     background-color: crimson;";
  html += "     color: white;";
  html += "}";
  html += "#container {";
  html += "     border: 8px solid rgb(38,99,132);";
  html += "     width: fit-content;";
  html += "     border-radius: 60px;";
  html += "}";
  html += "button {";
  html += "     font-family: 'ubuntu';";
  html += "     width: 70px;";
  html += "     height: 48px;";
  html += "}";
  html += "#onB:hover {";
  html += "     border: 5px solid red;";
  html += "     background-color: crimson;";
  html += "}";
  html += "#offB:hover {";
  html += "     border: 5px solid green;";
  html += "     background-color: rgb(6,158,92);";
  html += "}";
  html += "</style>";
  html += "<center>";
  html += "<h1>ESP32-S3</h1>";
  html += "<div id=\"container\">";
  html += "<button id=\"onB\" onclick=\"toggleLight('/on')\">On</button>";
  html += "<button id=\"offB\" onclick=\"toggleLight('/off')\">Off</button>";
  html += "</div>";
  html += "</center>";
  html += "<script>";
  html += "function toggleLight(u) {";
  html += "     var xml = new XMLHttpRequest();";
  html += "     xml.open('GET',u,true);";
  html += "     xml.send();";
  html += "}";
  html += "</script>";
  html += "</body></html>";

  server.send(200, "text/html", html);
}

void handleOn() {
  digitalWrite(pin, HIGH);
}

void handleOff() {
  digitalWrite(pin, LOW);
}

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid,pass);

  if (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(10);
  }

  Serial.println("Connected!");
  Serial.println(WiFi.localIP());

  pinMode(10, OUTPUT);
  digitalWrite(10, LOW);

  server.on("/",handleRoot);
  server.on("/on",handleOn);
  server.on("/off",handleOff);
  server.begin();
}

void loop() {
  server.handleClient();
}