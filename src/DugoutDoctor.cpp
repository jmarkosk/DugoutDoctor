/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#include "application.h"
#line 1 "h:/DugoutDoctor/DugoutDoctor/src/DugoutDoctor.ino"
/*
 * Project DugoutDoctor
 * Description:
 * Author: 
 * Date:
 */

//Includes
#include "elapsedMillis.h"
#include "Adafruit_DHT_Particle.h"


void setup();
void loop();
#line 13 "h:/DugoutDoctor/DugoutDoctor/src/DugoutDoctor.ino"
SYSTEM_THREAD(ENABLED);
SYSTEM_MODE(MANUAL);

//#define THINGSPEAK_CHANNEL_ID 411366
//#define THINGSPEAK_API_KEY_WRITE 57VJCNFL5L8CRQ64

//Constant Strings
const char csProjectName[] = "Dugout Doctor";
const char csVersion[] = "V0.0.01";


//LED Indicators
#define HB_LED D7  //Default Particle LED - Heart Beat LED
#define USER_LED D6
u_int8_t gHB_LED_STATE = 0;

//Timers 
#define TIME_INTERVAL_1_SECOND 1000
elapsedMillis timeElapsed;

//Temp / Humidity
#define DHTPIN D2     // what pin we're connected to

// Uncomment whatever type you're using!
//#define DHTTYPE DHT11		// DHT 11 
#define DHTTYPE DHT22		// DHT 22 (AM2302)
//#define DHTTYPE DHT21		// DHT 21 (AM2301)

// Connect pin 1 (on the left) of the sensor to +5V
// Connect pin 2 of the sensor to whatever your DHTPIN is
// Connect pin 4 (on the right) of the sensor to GROUND
// Connect a 10K resistor from pin 2 (data) to pin 1 (power) of the sensor 
DHT dht(DHTPIN, DHTTYPE);
int loopCount;
void GetDHT(void);




// setup() runs once, when the device is first turned on.
void setup() {
  // Put initialization like pinMode and begin functions here.
  //Serial monitor setup
  Serial.begin(9600);
  waitFor(Serial.isConnected, 30000);

  //GPIO SETUP
  pinMode(HB_LED,OUTPUT);

  Serial.println("DEBUG: DHTxx Setup!");
  dht.begin();
	loopCount = 0;
  delay(2000);
  Serial.println("DEBUG: DHTxx Setup Complete!");



}

// loop() runs over and over again, as quickly as it can execute.
void loop() {
  // The core of your code will likely live here.
  if(timeElapsed > TIME_INTERVAL_1_SECOND)
  {
    gHB_LED_STATE = !gHB_LED_STATE;
    digitalWrite(HB_LED,gHB_LED_STATE);
    timeElapsed = 0;
    loopCount++;
  }
 
  if(loopCount == 5)
  {
     loopCount = 0;
     GetDHT();
  }

}

void GetDHT(void)
{
   // Wait a few seconds between measurements.
	delay(2000);

// Reading temperature or humidity takes about 250 milliseconds!
// Sensor readings may also be up to 2 seconds 'old' (its a 
// very slow sensor)
	//float h = dht.getHumidity();
// Read temperature as Celsius
	float t = dht.getTempCelcius();
// Read temperature as Farenheit
	//float f = dht.getTempFarenheit();
  
// Check if any reads failed and exit early (to try again).
	/*
  if (isnan(h) || isnan(t) || isnan(f)) {
		Serial.println("Failed to read from DHT sensor!");
		return;
	}
*/
    if (isnan(t)) {
		Serial.println("Failed to read from DHT sensor!");
		return;
	}


// Compute heat index
// Must send in temp in Fahrenheit!
	float hi = dht.getHeatIndex();
	float dp = dht.getDewPoint();
	float k = dht.getTempKelvin();
/*
	Serial.print("Humid: "); 
	Serial.print(h);
	Serial.print("% - ");
*/
	Serial.print("Temp: "); 
	Serial.print(t);
	Serial.print("*C ");
	
  /*
  Serial.print(f);
	Serial.print("*F ");
	Serial.print(k);
	Serial.print("*K - ");
	Serial.print("DewP: ");
	Serial.print(dp);
	Serial.print("*C - ");
	Serial.print("HeatI: ");
	Serial.print(hi);
	Serial.println("*C");
 */ 
	Serial.println(Time.timeStr());
}