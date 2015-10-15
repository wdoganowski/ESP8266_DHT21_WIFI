#include <DHT.h>
#include <Ticker.h>

#define DHTPIN  2     // DTH connected to pin 2
#define DHTTYPE DHT21 // DHT11, DHT21, DHT22
#ifdef DEBUG_DHT
#define DHTTICK "5"   // Read every 5 seconds
#else
#define DHTTICK "300" // Read every 5 minutes
#endif

DHT dht( DHTPIN, DHTTYPE );
Ticker ticker_DHT;
boolean do_read_DHT = false;

#define TIMEDATESIZE 20 // YYYY/MM/DD hh:mm.ss

float temperature = NAN;
float humidity = NAN;
float feelslike = NAN;

/*
 * To be called from the main setup
 */
void setup_DHT(void) {
  // Setup function
  rest.function("set_ticker", set_ticker_DHT);
  // Setup variables
  rest.variable((char *)"humidity", &humidity);
  rest.variable((char *)"temperature", &temperature);
  rest.variable((char *)"feelslike", &feelslike);
  // Create UI
  rest.label((char *)"humidity");
  rest.label((char *)"temperature");
  rest.label((char *)"feelslike");  
  // Setup DHT
  dht.begin();
  read_DHT();
  set_ticker_DHT(DHTTICK);
}

/*
 * To set the ticker time in seconds
 */
int set_ticker_DHT(String tick) {
  int t = tick.toInt();
  if (t) {
    ticker_DHT.attach(t, tick_DHT); // Provide the number as 'params' or the ticker time will not be set
    #ifdef DEBUG_DHT
    dbg("Ticker set to %d seconds", t);
    #endif  read_DHT(); // Push the read out so just after calling "tick" the data can be read
  } else {
    #ifdef DEBUG_DHT
    Serial.println("Ticker not set");
    #endif  read_DHT(); // Push the read out so just after calling "tick" the data can be read
  }
  return t;
}

/*
 * To be called from the ticker
 */
void tick_DHT(void) {
  do_read_DHT = true; // Will call read_DHT in the main loop
}

/*
 * To be called from the main loop
 */
void handle_DHT(void) {
  if(do_read_DHT) {
    do_read_DHT = false;
    read_DHT();
  }
}

/*
 * Do the job of reading the sensor
 */
void read_DHT(void) {
  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  humidity = dht.readHumidity();
  // Read temperature as Celsius (the default)
  temperature = dht.readTemperature();

  // Check if any reads failed and exit early (to try again).
  if (isnan(humidity) || isnan(temperature)) {
    feelslike = NAN;
    #ifdef DEBUG_DHT
    Serial.println("Failed to read from DHT sensor!");
    #endif
    return;
  }
   
  // Compute heat index in Celsius (isFahreheit = false)
  feelslike = dht.computeHeatIndex(temperature, humidity, false);
  #ifdef DEBUG_DHT
  dbg("Humidity: %f %\tTemperature: %f*C %\tFeels like: %f*C ", humidity, temperature, feelslike);
  #endif
}
