#define DEBUG

#ifdef  DEBUG
//#define DEBUG_MAIN
#define DEBUG_DHT
#define DEBUG_RELAY
#define DEBUG_WIFI
#endif

// Wifi
#include <ESP8266WiFi.h>

// aRest
#include <aREST.h>
#include <aREST_UI.h>

// WiFi parameters
char device_id[] = "ESP_ABCDEF";
const char* device_name = "ESP8266_DHT21";

void setup( void )
{  
  // Start Serial
  #ifdef DEBUG
  Serial.begin(115200);
  #endif
  #ifdef DEBUG_MAIN
  Serial.setDebugOutput(true);
  #endif

  // Give name and ID to device
  byte mac[6];
  WiFi.macAddress(mac); // Read MAC
  #ifdef DEBUG_MAIN
  sprintf(device_id, "ESP_%X%X%X", mac[3], mac[4], mac[5]);
  #endif

  setup_WiFi();
  setup_aRest(device_id, device_name);
  setup_relay();
  setup_DHT();
}

void loop() {
  
  handle_DHT();
  WiFiClient client;
  handle_WiFi(&client);
  handle_aRest(&client); 
  handle_relay();
  
}
