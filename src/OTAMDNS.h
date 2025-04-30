#ifndef OTAMDNS_H
#define OTAMDNS_H

#include <ArduinoOTA.h>
#if defined(ESP32)
  #include <WiFi.h>
  #include <ESPmDNS.h>
  #include <Update.h>
#elif defined(ESP8266)
  #include <ESP8266WiFi.h>
  #include <ESP8266mDNS.h>
#endif

void OTAMDNS_begin(const char* ssid, const char* password, const char* hostPrefix, int verLength, const char* otapass, int subadd = -1, __FILE__);
void OTAMDNS_loop();

#endif