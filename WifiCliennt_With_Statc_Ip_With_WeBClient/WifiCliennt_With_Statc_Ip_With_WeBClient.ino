
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266mDNS.h>
#include <ESP8266HTTPClient.h>
#ifndef APSSID
#define APSSID "ahmed"
#define APPSK  "ahmed1234"
#endif
const char *ssid = APSSID;
const char *password = APPSK;
constexpr uint8_t RST_PIN = 5;
constexpr uint8_t SS_PIN = 4;
HTTPClient http;

void setup() {

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }

  IPAddress dhcpIp = WiFi.localIP();
  dhcpIp[3] = 100;
  if (!WiFi.config(dhcpIp, WiFi.gatewayIP(), WiFi.subnetMask())) {

  }

  Serial.begin(115200);
}
void loop() {

  if (WiFi.status() == WL_CONNECTED) {

    WiFiClient client;
    if (http.begin(client, "http://176.223.140.119:1003/api/user/gen?pass=123")) {

      Serial.print("[HTTP] GET...\n");
      // start connection and send HTTP header
      int httpCode = http.GET();

      // httpCode will be negative on error
      if (httpCode > 0) {
        // HTTP header has been send and Server response header has been handled
        Serial.printf("[HTTP] GET... code: %d\n", httpCode);

        // file found at server
        if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
          String payload = http.getString();
          Serial.println(payload);
        }
      } else {
        Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
      }

      http.end();

    }
    else {
      Serial.printf("[HTTP} Unable to connect\n");
    }

  }


}
