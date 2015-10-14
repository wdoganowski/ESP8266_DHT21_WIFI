// Create aREST instance
aREST_UI rest = aREST_UI();

extern float temperature;
extern float humidity;
extern float feelslike;
extern String readouttime;

/*
 * To be called from the main setup
 */
void setup_aRest(String id, String name) {
  // Setup variables
  rest.variable((char *)"temperature", &temperature);
  rest.variable((char *)"humidity", &humidity);
  rest.variable((char *)"feelslike", &feelslike);
  rest.variable((char *)"readouttime", &readouttime);
    
  // Create UI
  rest.title(name);
  rest.label((char *)"temperature");
  rest.label((char *)"humidity");
  rest.label((char *)"feelslike");  
  rest.label((char *)"readouttime");  

  // Register
  rest.set_id(id);
  rest.set_name(name);
}

/*
 * To be called from the main loop
 */
void handle_aRest(WiFiClient* client) {
    rest.handle(*client);
}

