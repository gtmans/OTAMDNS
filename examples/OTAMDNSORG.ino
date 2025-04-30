// OTAMDNS_V01_3
// for ESP32 and ESP8266
// does OTA and puts version number of compiled file in the networkname
// check MDNS with WIN+R,cmd,dns-sd -B _arduino._tcp 
#include      "gewoon_secrets.h" // WiFi settings const char* ssid and const char* password
#define       SUBADD      0       // IP-address = 192.168.2.SUBADD if not defined DHCP address
const char*   OTA_PASS    = "1234";  // make PASS "" if no password
String        myhost_pre  = "ESP-OTA000-TST";
String        fullHost;
int           LenVerStr   = 5;  //len of version part in filename like in OTAMDNS_V01_0.ino "V01_0"=5 

#include      <ArduinoOTA.h>    // OTA management
#if defined   (ESP32)
  #include    <ESPmDNS.h>
  #include    <Update.h>        // Firmware schrijven (OTA updates)
  #include    <WiFi.h>          // ESP32 WiFi stack
#elif defined (ESP8266)
  #include    <ESP8266mDNS.h>   // ESP8266 eigen mDNS
  #include    <ESP8266WiFi.h>   // ESP8266 WiFi stack
#else
  #error      "Unknown platform!"
#endif

#define MSG(x) do { if (Serial) Serial.println(x); } while(0)

void setup() {
  Serial.begin(115200);
  delay(1000);
  MSG("");

  // Hostnaam samenstellen op basis van bestandsnaam
  String version = String(__FILE__).substring(String(__FILE__).length() - 4 - LenVerStr, String(__FILE__).length() - 4);
  fullHost = myhost_pre + version;
  static char otaHostBuffer[32];
  fullHost.toCharArray(otaHostBuffer, sizeof(otaHostBuffer));
  const char* OTA_HOST = otaHostBuffer;
  MSG(OTA_HOST);

#ifdef LED_BUILTIN
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);  // LED uit
#else
  MSG("LED_BUILTIN not defined on this board.");
#endif

  MSG("Booting");

#ifdef SUBADD  // assign IP if defined
  IPAddress local_IP(192, 168, 2, SUBADD);
  IPAddress gateway(192, 168, 2, 254);
  IPAddress subnet(255, 255, 255, 0);
  IPAddress primaryDNS(8, 8, 8, 8);
  IPAddress secondaryDNS(8, 8, 4, 4);
  if (!WiFi.config(local_IP, gateway, subnet, primaryDNS, secondaryDNS)) {
    MSG("STA Failed to configure");
  }  
#endif

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.waitForConnectResult() != WL_CONNECTED) {
    MSG("Retrying connection...");
    WiFi.begin(ssid, password);
  }

#if defined(ESP8266)
  if (!MDNS.begin(OTA_HOST)) {
    MSG(String("Error bij starten van mDNS! voor ") + OTA_HOST);
  } else {
    MSG("mDNS gestart!");
  }
#else
  if (MDNS.begin(WiFi.getHostname())) {
    MSG("mDNS responder gestart (ESPmDNS)");
    MDNS.addService("http", "tcp", 80);
  } else {
    MSG("Error setting up ESPmDNS!");
  }
#endif

  ArduinoOTA.setHostname(OTA_HOST);
  if (OTA_PASS[0] != '\0') {
    ArduinoOTA.setPassword(OTA_PASS);
  }

  ArduinoOTA.onStart([]() {
    String type = (ArduinoOTA.getCommand() == U_FLASH) ? "sketch" : "filesystem";
    MSG("Start OTA update van: " + type);
#ifdef LED_BUILTIN
    digitalWrite(LED_BUILTIN, LOW);  // LED aan
#endif
  });

  ArduinoOTA.onEnd([]() {
#ifdef LED_BUILTIN
    for (int i = 0; i < 4; i++) {
      digitalWrite(LED_BUILTIN, HIGH);
      delay(250);
      digitalWrite(LED_BUILTIN, LOW);
      delay(250);
    }
#else
    delay(2000);
#endif

#if defined(ESP8266)
    MDNS.close();
#elif defined(ESP32)
    MDNS.end();
#endif
    delay(100);
    MSG("\nOTA klaar, MDNS gestopt, herstarten...");
    ESP.restart();
  });

  ArduinoOTA.onError([](ota_error_t error) {
#ifdef LED_BUILTIN
    for (int i = 0; i < 20; i++) {
      digitalWrite(LED_BUILTIN, HIGH);
      delay(250);
      digitalWrite(LED_BUILTIN, LOW);
      delay(250);
    }
#endif
    ESP.restart();
  });

  ArduinoOTA.begin();
  MSG("Ready");
}

void loop() {
  ArduinoOTA.handle();
}
