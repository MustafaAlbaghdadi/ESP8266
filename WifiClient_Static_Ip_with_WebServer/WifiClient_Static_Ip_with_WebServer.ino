
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#ifndef APSSID
#define APSSID "ahmed"
#define APPSK  "ahmed1234"
#endif
const char *ssid = APSSID;
const char *password = APPSK;
constexpr uint8_t RST_PIN = 5;
constexpr uint8_t SS_PIN = 4;
ESP8266WebServer server(80);

void setup() {
  Serial.begin(9600);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  IPAddress dhcpIp =WiFi.localIP();
  dhcpIp[3] = 100;
  if (!WiFi.config(dhcpIp, WiFi.gatewayIP(), WiFi.subnetMask())) {
   
  }
  server.on("/", handleRoot);
  server.begin();
}
void loop() {
  server.handleClient();

}

void handleRoot() {
  String query = server.argName(0);
  Serial.println(query);
  String message = Serial.readString();
  server.send(200, "text/plain", message);

}
