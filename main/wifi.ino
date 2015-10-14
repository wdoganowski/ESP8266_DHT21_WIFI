const char* ssid = "wifi";
const char* password = "haslo4wifi123";

// The port to listen for incoming TCP connections 
#define LISTEN_PORT 80

// Create an instance of the server
WiFiServer server(LISTEN_PORT);

/*
 * To be called from the main setup
 */
void setup_WiFi() {
  // Connect to WiFi
  WiFi.mode(WIFI_STA);
  //WiFi.softAP(APssid);
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(1500);
    #ifdef DEBUG_WIFI
    Serial.print(".");
    #endif
  }
  #ifdef DEBUG_WIFI
  Serial.println("");
  Serial.println("WiFi connected");
  #endif
 
  // Start the server
  server.begin();
  #ifdef DEBUG_WIFI
  Serial.println("Server started");
  #endif
  
  // Print the IP address
  #ifdef DEBUG_WIFI
  printWifiStatus();
  #endif
}

/*
 * To be called from the main loop
 */
void handle_WiFi(WiFiClient* client) {
  // Handle HTTP calls
  *client = server.available();
  if (!*client) {
    return;
  }
  while(!client->available()){
    delay(1);
  }
}

/*
 * Debug WiFi status
 */
#ifdef DEBUG_WIFI
void printWifiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("Local IP Address: ");
  Serial.println(ip);

  ip = WiFi.softAPIP();
  Serial.print("AP IP Address: ");
  Serial.println(ip);
  
  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}
#endif
