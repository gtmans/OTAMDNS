#include "OTAMDNS.h"

String fullHost;

void OTAMDNS_begin(const char* ssid, const char* password, const char* hostPrefix, int verLength, const char* otapass, int subadd) {
  String myhost = __FILE__;
  myhost = myhost.substring(myhost.length() - 4 - verLength, myhost.length() - 4);
  fullHost = String(hostPrefix) + myhost;
  const char* OTA_HOST = fullHost.c_str();

#if defined(ESP8266)
  if (subadd >= 0) {
    IPAddress local_IP(192, 168, 2, subadd);
    IPAddress gateway(192, 168, 2, 254);
    IPAddress subnet(255, 255, 255, 0);
    WiFi.config(local_IP, gateway, subnet);
  }
#elif defined(ESP32)
  if (subadd >= 0) {
    IPAddress local_IP(192, 168, 2, subadd);
    IPAddress gateway(192, 168, 2, 254);
    IPAddress subnet(255, 255, 255, 0);
    IPAddress primaryDNS(8, 8, 8, 8);
    IPAddress secondaryDNS(8, 8, 4, 4);
    WiFi.config(local_IP, gateway, subnet, primaryDNS, secondaryDNS);
  }
#endif

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.waitForConnectResult() != WL_CONNECTED) {
    WiFi.begin(ssid, password);
    delay(1000);
  }

#if defined(ESP8266)
  if (!MDNS.begin(OTA_HOST)) return;
#elif defined(ESP32)
  if (!MDNS.begin(WiFi.getHostname())) return;
  MDNS.addService("http", "tcp", 80);
#endif

  ArduinoOTA.setHostname(OTA_HOST);
  if (otapass && otapass[0] != '\0') ArduinoOTA.setPassword(otapass);

  ArduinoOTA.onStart([]() {
#if defined(LED_BUILTIN)
    digitalWrite(LED_BUILTIN, LOW);
#endif
  });

  ArduinoOTA.onEnd([]() {
#if defined(LED_BUILTIN)
    for (int i = 0; i < 2; i++) {
      digitalWrite(LED_BUILTIN, HIGH);
      delay(250);
      digitalWrite(LED_BUILTIN, LOW);
      delay(250);
    }
#endif
#if defined(ESP32)
  MDNS.end();
#elif defined(ESP8266)
  MDNS.close();
#endif
  delay(100);
  ESP.restart();
  });

  ArduinoOTA.begin();
}

void OTAMDNS_loop() {
  ArduinoOTA.handle();
}