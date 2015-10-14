#include <DHT.h>
#include <Ticker.h>

#define DHTPIN  2     // DTH connected to pin 2
#define DHTTYPE DHT21 // DHT11, DHT21, DHT22
#ifdef DEBUG_DHT
#define DHTTICK 5    // Read every 5 seconds
#else
#define DHTTICK 300    // Read every 5 minutes
#endif

DHT dht( DHTPIN, DHTTYPE );
Ticker ticker_DHT;
boolean do_read_DHT = false;

#define TIMEDATESIZE 20 // YYYY/MM/DD hh:mm.ss

float temperature = NAN;
float humidity = NAN;
float feelslike = NAN;
char readouttime_c[TIMEDATESIZE];
String readouttime; 

/*
 * To be called from the main setup
 */
void setup_DHT(void) {
  dht.begin();
  read_DHT();
  ticker_DHT.attach(DHTTICK, tick_DHT);
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
  if (timeStatus() != timeNotSet) {
    snprintf(readouttime_c, TIMEDATESIZE, "%04d/%02d/%02d %02d:%02d.%02d", year(), month(), day(), hour(), minute(), second());
    readouttime = readouttime_c;
  }

  #ifdef DEBUG_DHT_TIME
  Serial.print("Readout time ");
  Serial.println(readouttime);
  #endif

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
