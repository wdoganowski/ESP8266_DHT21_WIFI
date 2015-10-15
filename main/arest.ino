// Create aREST instance
aREST_UI rest = aREST_UI();

extern float temperature;
extern float humidity;
extern float feelslike;

/*
 * To be called from the main setup
 */
void setup_aRest(String id, String name) {
  // UI
  rest.title(name);
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

