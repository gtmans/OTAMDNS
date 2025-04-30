# OTAMDNS Library

Een eenvoudige library om OTA-updates en mDNS-naam toe te voegen aan ESP32- en ESP8266-projecten.
Installeert WiFi (desgewenst op een vast adres) en Start ArduinoOTA (updates via WiFi) waarbij de 
OTA (mDNS) netwerknaam het versienummer van je programma in de Arduino IDE bevat. 
Zo kun je vanuit de Arduino IDE bij Tools/Port zien welk programma, versie en IP adres je wilt updaten.
MB. Dit is mijn allereerste library maar ik heb hem wel uitgebreid getest op D1-mini en M5 Core. 

## Gebruik
```
  // Initialiseer WiFi, mDNS en OTA met één regel
  OTAMDNS_begin(ssid, password, OTAPREFIX, OTAVERLEN, OTAPASS, SUBADD);
  Serial.println("Setup klaar");
}

void loop() {
  OTAMDNS_loop();  // Houd OTA service draaiende
}

```
