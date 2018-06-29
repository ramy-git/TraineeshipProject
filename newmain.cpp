
// ---------------------------------------------------------------------------
// This example code was used to successfully communicate with 15 ultrasonic sensors. You can adjust
// the number of sensors in your project by changing SONAR_NUM and the number of NewPing objects in the
// "sonar" array. You also need to change the pins for each sensor for the NewPing objects. Each sensor
// is pinged at 33ms intervals. So, one cycle of all sensors takes 495ms (33 * 15 = 495ms). The results
// are sent to the "oneSensorCycle" function which currently just displays the distance data. Your project
// would normally process the sensor results in this function (for example, decide if a robot needs to
// turn and call the turn function). Keep in mind this example is event-driven. Your complete sketch needs
// to be written so there's no "delay" commands and the loop() cycles at faster than a 33ms rate. If other
// processes take longer than 33ms, you'll need to increase PING_INTERVAL so it doesn't get behind.
// ---------------------------------------------------------------------------
#include <NewPing.h>

#define SONAR_NUM     2 // Number of sensors.
#define MAX_DISTANCE 150 // Maximum distance (in cm) to ping.
#define PING_INTERVAL 33 // Milliseconds between sensor pings (29ms is about the min to avoid cross-sensor echo).

#define SD_INTERVAL XXX // Milliseconds between result registration to the sd card.
#define MIN_DISTANCE XXX // Minimum distance to identify that a person is in front of the sensor.
#define MAX_DELAY XXX // Maximum ammount of time to wait for a person to pass in front of the opposite sensor.

unsigned long pingTimer[SONAR_NUM]; // Holds the times when the next ping should happen for each sensor.
unsigned int people_in = 0;
unsigned int people_out = 0;

unsigned int cm[SONAR_NUM];         // Where the ping distances are stored.
uint8_t currentSensor = 0;          // Keeps track of which sensor is active.

unsigned int *first=&cm[0]; // ultrasensor 1
unsigned int *second=&cm[1]; // ultrasensor 2


/*
int check_sensor(){
  bool first;
  bool second;
  bool directio;
  unsigned long time_e;
    if ( 8< *us1< 80) {
     directio = 1;
     first=1;
     return first;
     second=0;
     return second;
     return directio;
     time_e=millis();
     return time_e;
     EVENT_first=1;
     EVENT=1;
    }
        
    }
    if ( 8< *us2< 80) {
     
        direction = 0;
        first=0;
        return first;
        second=1;
        return second;
        return directio;
        time_e=millis();
        return time_e;
        EVENT_second=1;
        EVENT=1;
    
    }
}
*/
   
int check_opposite(unsigned int id, unsigned int dir) {
  XXX time_e = millis();
  while (millis() - time_e < MAX_DELAY) {
    if (sonar[id].ping_cm() < MIN_DIST) {
      if (dir == 0) {
        people_in++
      } else {
        people_out++
      }
      break;
    }
  }
     
      
      /*
       if(EVENT_second) {
         
      while( millis()-time_e < TIME_MAX ) { 
         checksensor();
      if( EVENT_first)
      {people_in++;
      returne people_in;
        }
      }
      if( EVENT_first) {
         while( millis()-time_e < TIME_MAX ) {
           checksensor();
         if( EVENT_second)
      {people_out++;
      return people_out;
        }
                                          }
                                          
      } 
        */                                  
}

NewPing sonar[SONAR_NUM] = {     // Sensor object array.
  NewPing(7, 8, MAX_DISTANCE), // Each sensor's trigger pin, echo pin, and max distance to ping.
  NewPing(12, 13, MAX_DISTANCE)
};

void setup() {
  Serial.begin(115200);
}

void loop() {
  if (millis() > PING_INTERVAL) { // check for people
    if (sonar[first].ping_cm() < MIN_DISTANCE) {
      check_opposite(second, 1);
    } else if (sonar[second].ping_cm() < MIN_DISTANCE) {
      check_opposite(first, 0);
    }
  }
  
  if (millis() > SD_INTERVAL) { // register the current observations
    // {time, in, out, temp, hum, snd}
    // people_in = 0;
    // people_out = 0;
  }
  

  /*
  for (uint8_t i = 0; i < SONAR_NUM; i++) { // Loop through all the sensors.
    if (millis() >= pingTimer[i]) {         // Is it this sensor's time to ping?
      pingTimer[i] += PING_INTERVAL * SONAR_NUM;  // Set next time this sensor will be pinged.
      if (i == 0 && currentSensor == SONAR_NUM - 1) oneSensorCycle(); // Sensor ping cycle complete, do something with the results.
      sonar[currentSensor].timer_stop();          // Make sure previous timer is canceled before starting a new ping (insurance).
      currentSensor = i;                          // Sensor being accessed.
      cm[currentSensor] = 0;                      // Make distance zero in case there's no ping echo for this sensor.
      sonar[currentSensor].ping_timer(echoCheck); // Do the ping (processing continues, interrupt will call echoCheck to look for echo).
    }
  }
  // Other code that *DOESN'T* analyze ping results can go here.
  */
}

/*
void echoCheck() { // If ping received, set the sensor distance to array.
  if (sonar[currentSensor].check_timer())
    cm[currentSensor] = sonar[currentSensor].ping_result / US_ROUNDTRIP_CM;
}
void oneSensorCycle() { // Sensor ping cycle complete, do something with the results.
  // The following code would be replaced with your code that does something with the ping results.
    
checksensor();
 if(EVENT) {
  checkOppo(); 
 EVENT=0;
 EVENT_first=0;
 EVENT_second;
 };
*/
  
}
