#include <OTAMDNS.h>               // Inclusie van je herbruikbare OTA/mDNS-bibliotheek
#include "gewoon_secrets.h"        // Bevat: const char* ssid; const char* password;
#define SUBADD    256              // zet statisch IP adres op basis 192.168.2.* Indien 256 dynamisch van DHCP
                                   // verander zonodig IP basis in OTADNS.cpp IPAddress local_IP(192,168,2,subadd);
#define OTAVERLEN 5                // Lengte van versiestukje aan einde van IDE bestandsnaam, bv. "Filenaam_V01_0.ino"=5 (lengte van V01_0)
#define OTAPASS   ""               // Optioneel: OTA wachtwoord laat leeg indien nvt. Als Arduino IDE vraagt wachtwoord vul letterlijk in ""
#define OTAPREFIX "D1-OTAMDNSTEST" // Prefix van hostnaam zichtbaar in IDE en mDNS

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println("\nStart setup");

  // Initialiseer WiFi, mDNS en OTA met één regel
  OTAMDNS_begin(ssid, password, OTAPREFIX, OTAVERLEN, OTAPASS, SUBADD, __FILE__);

  Serial.println("Setup klaar");
}

void loop() {
  OTAMDNS_loop();  // Houd OTA service draaiende 
}
