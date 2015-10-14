//#define PRODUCTION

#ifndef PRODUCTION
//#define DEBUG_MAIN
//#define DEBUG_TIME_NTP
#define DEBUG_DHT
#define DEBUG_WIFI
#endif

// Wifi
#include <ESP8266WiFi.h>

// aRest
#include <aREST.h>
#include <aREST_UI.h>

// Time
#include <Time.h>

// WiFi parameters
char device_id[] = "ESP_ABCDEF";
const char* device_name = "ESP8266_DHT21";

void setup( void )
{  
  // Start Serial
  #ifndef PRODUCTION
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
  
  // Setup WiFi
  setup_WiFi();

  // Setup Time
  setup_Time();
  
  // Setup DHT
  setup_DHT();
    
  // Setup aRest
  setup_aRest(device_id, device_name);
}

void loop() {
  
  handle_Time();
  handle_DHT();
  WiFiClient client;
  handle_WiFi(&client);
  handle_aRest(&client); 
  
}
