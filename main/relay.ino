#define RELAY_PIN 0

int relay_state = LOW;

/*
 * To be called in the main setup
 */
void setup_relay() {
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, relay_state); // OFF (reverse logic)
  rest.function("set_relay", set_relay);
  rest.variable((char *)"relay", &relay_state);
  rest.label((char *)"relay");  
  rest.button(RELAY_PIN);
}

/*
 * To be called in the main loop
 */
void handle_relay() {
  // Read current state
  relay_state = digitalRead(RELAY_PIN); 
}

/*
 * Callback from aRest
 */
int set_relay(String state) {
  state.toUpperCase();
  if(state.toInt()==1 || state=="ON") {
    #ifdef DEBUG_RELAY
    Serial.println("Relay to HIGH");
    #endif    
    relay_state = HIGH;
    digitalWrite(RELAY_PIN, relay_state); 
    return 1;
  } else {
    #ifdef DEBUG_RELAY
    Serial.println("Relay to LOW");
    #endif    
    relay_state = LOW;
    digitalWrite(RELAY_PIN, relay_state); 
    return 0;
  }
}

