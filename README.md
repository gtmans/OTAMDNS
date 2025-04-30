# OTAMDNS Library

Een eenvoudige library om OTA-updates en mDNS-naam toe te voegen aan ESP32- en ESP8266-projecten.
Installeert WiFi (desgewenst op een vast adres) en Start ArduinoOTA (updates via WiFi) waarbij de 
OTA (mDNS) netwerknaam het versienummer van je programma in de Arduino IDE bevat. 
Zo kun je vanuit de Arduino IDE bij Tools/Port zien welk programma, versie en IP adres je wilt updaten.
bv. Tools/Port: M5-OTA12-V1_12 at 192.168.2.15

LET OP! deze library werkt misschien niet 100% ... het originele programma werkt in elk geval wel en staat in examples\OTAMDNSORG.ino

NB. Dit is mijn allereerste library maar ik heb hem wel uitgebreid getest op D1-mini en M5 Core. Ik ben een 65+ beginner en heb hulp gehad van ChatGPT

## Gebruik
```
  // Initialiseer WiFi, mDNS en OTA met één regel
  OTAMDNS_begin(ssid, password, OTAPREFIX, OTAVERLEN, OTAPASS, SUBADD, __FILE__);
  Serial.println("Setup klaar");
}

void loop() {
  OTAMDNS_loop();  // Houd OTA service draaiende
}

```
