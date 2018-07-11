#include <NewPing.h>
#include <SPI.h>
#include <SD.h>
#include <Wire.h> //I2C needed for sensors
#include <SparkFunMPL3115A2.h> //Pressure sensor - Search "SparkFun MPL3115" and install from Library Manager
#include <SparkFunHTU21D.h> //Humidity sensor - Search "SparkFun HTU21D" and install from Library Manager



#define SONAR_NUM     2 // Number of sensors.
#define MAX_DISTANCE 150 // Maximum distance (in cm) to ping.
#define PING_INTERVAL 33 // Milliseconds between sensor pings (29ms is about the min to avoid cross-sensor echo).

#define SD_INTERVAL 400000 // Milliseconds between result registration to the sd card.
#define MIN_DISTANCE 20 // Minimum distance to identify that a person is in front of the sensor.
#define MAX_DELAY 1000 // Maximum ammount of time to wait for a person to pass in front of the opposite sensor.

unsigned long pingTimer[SONAR_NUM]; // Holds the times when the next ping should happen for each sensor.
unsigned int people_in = 0;
unsigned int people_out = 0;
unsigned int *ppl_in= &people_in;
unsigned int *ppl_out= &people_out;

/*unsigned int cm[SONAR_NUM];         // Where the ping distances are stored.
uint8_t currentSensor = 0;          // Keeps track of which sensor is active.
*/
unsigned int first = 0;
unsigned int second = 1;

unsigned int in = 0;
unsigned int out = 1;

float humidity;
float temp_h;
float light_lvl;
float pressure;

float *hum= &humidity;
float *temp= &temp_h;
float *light= &light_lvl;
float *pres = &pressure;
char dataString;

MPL3115A2 myPressure; //Create an instance of the pressure sensor
HTU21D myHumidity; //Create an instance of the humidity sensor

//Hardware pin definitions
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
const byte STAT_BLUE = 7;
const byte STAT_GREEN = 8;

const byte REFERENCE_3V3 = A3;
const byte LIGHT = A1;
const byte BATT = A2;

//Global Variables
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
long lastSecond; //The millis counter to see when a second rolls by



  //Configure the pressure sensor
  


NewPing sonar[SONAR_NUM] = {     // Sensor object array.
  NewPing(7, 8, MAX_DISTANCE), // Each sensor's trigger pin, echo pin, and max distance to ping.
  NewPing(9, 10, MAX_DISTANCE)
};

int check_sensor(unsigned int id) {
  delay(PING_INTERVAL);
  if (sonar[id].ping_cm() < MIN_DISTANCE && sonar[id].ping_cm() > 4 ) {
    return 1;
  }
  return 0;
}

int check_opposite(unsigned int id, unsigned int dir) {
  long time_e = millis();
  while (millis() - time_e < MAX_DELAY) {
    if (check_sensor(id)) {
      if (dir == in) {
        people_in++;
        Serial.print("in: ");
        Serial.println(people_in);
      } else {
        people_out++;
        Serial.print("out: ");
        Serial.println(people_in);
      }
      break;
    }
  }
     
                                       
}

void setup() {
  Serial.begin(115200);
  
}


long ping_nxt = PING_INTERVAL;
long sd_nxt = SD_INTERVAL;
void loop() {
  
  if (millis() > ping_nxt) { // check for people
    
    Serial.print("first: ");
    Serial.print(sonar[first].ping_cm());
    Serial.print(" - second: ");
    Serial.println(sonar[second].ping_cm());
    
   
    if (check_sensor(first)) {
      check_opposite(second, in);
    } else if (check_sensor(second)) {
      check_opposite(first, out);
    }
    
    ping_nxt = millis() + PING_INTERVAL + 700;
  }

 
  if (millis() > sd_nxt) { // register the current observations
    // {time, in, out, temp, hum, snd}
    // people_in = 0;
    // people_out = 0;

   
    

    /*
    Serial.print("in: ");
    Serial.print(people_in);
    Serial.print(" - out: ");
    Serial.print(people_out);
    Serial.println(); */
    
    sd_nxt = millis() + SD_INTERVAL;
  }
  
  
}
