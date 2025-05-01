# OTAMDNS Library

Een eenvoudige library om OTA-updates en mDNS-naam toe te voegen aan ESP32- en ESP8266-projecten.
Installeert WiFi (desgewenst op een vast adres) en Start ArduinoOTA (updates via WiFi) waarbij de 
OTA (mDNS) netwerknaam het versienummer van je programma in de Arduino IDE bevat. 
Zo kun je vanuit de Arduino IDE bij Tools/Port zien welk programma, versie en IP adres je kunt updaten.
bv. menu Tools/Port: M5-OTA12-V1_12 at 192.168.2.15

LET OP! Mocht je problemen ondervinden met deze library gebruik dan het originele programma in examples\OTAMDNSORG.ino
Dit is mijn eerste library en heb hem uitgebreid getest op D1-mini en M5 Core maar vergeet niet dat ik een 65+ beginner ben ...

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
