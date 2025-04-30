#include <OTAMDNS.h>               // Inclusie van je herbruikbare OTA/mDNS-bibliotheek
#include "gewoon_secrets.h"        // Bevat: const char* ssid; const char* password;

//#define SUBADD 123               // Optioneel: zet statisch IP adres op basis 192.168.2.*
                                   // verander zonodig in OTADNS.cpp IPAddress local_IP(192,168,2,subadd);
#define OTAVERLEN 5                // Lengte van versiestukje aan einde van IDE bestandsnaam, bv. "Filenaam_V01_0.ino"=5 (lengte V01_0)
#define OTAPASS   ""               // Optioneel: OTA wachtwoord laat leeg indien nvt.
#define OTAPREFIX "ESP-OTA000-TST" // Prefix van hostnaam zichtbaar in IDE en mDNS

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println("\nStart setup");

  // Initialiseer WiFi, mDNS en OTA met één regel
  OTAMDNS_begin(ssid, password, OTAPREFIX, OTAVERLEN, OTAPASS, SUBADD);

  Serial.println("Setup klaar");
}

void loop() {
  OTAMDNS_loop();  // Houd OTA service draaiende
}
