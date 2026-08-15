#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "YOUR_WIFI_NAME";
const char* password = "YOUR_WIFI_PASSWORD";

WebServer server(80);

const int ledPin = 2;

bool ledState = false;

void handleRoot() {

  String html = "<!DOCTYPE html><html>";
  html += "<head>";
  html += "<meta name='viewport' content='width=device-width, initial-scale=1'>";
  html += "<title>ESP32 LED Control</title>";
  html += "</head>";

  html += "<body style='text-align:center;font-family:Arial;'>";

  html += "<h1>ESP32 LED Control</h1>";

  if(ledState)
    html += "<h2>LED Status: ON</h2>";
  else
    html += "<h2>LED Status: OFF</h2>";

  html += "<p><a href='/on'><button style='width:150px;height:50px;'>ON</button></a></p>";
  html += "<p><a href='/off'><button style='width:150px;height:50px;'>OFF</button></a></p>";

  html += "</body></html>";

  server.send(200, "text/html", html);
}

void handleOn() {
  digitalWrite(ledPin, HIGH);
  ledState = true;
  handleRoot();
}

void handleOff() {
  digitalWrite(ledPin, LOW);
  ledState = false;
  handleRoot();
}

void setup() {

  Serial.begin(115200);

  pinMode(ledPin, OUTPUT);

  WiFi.begin(ssid, password);

  Serial.print("Connecting");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi Connected");

  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  server.on("/", handleRoot);
  server.on("/on", handleOn);
  server.on("/off", handleOff);

  server.begin();

  Serial.println("Web Server Started");
}

void loop() {
  server.handleClient();
}