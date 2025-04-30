# OTAMDNS Library

Een eenvoudige library om OTA-updates en mDNS-advertenties toe te voegen aan ESP32- en ESP8266-projecten.

## Gebruik

```cpp
#include <OTAMDNS.h>

void setup() {
  OTAMDNS_setup("ESP-OTA123", "mijnSSID", "mijnWachtwoord", "1234");
}

void loop() {
  OTAMDNS_loop();
}
```