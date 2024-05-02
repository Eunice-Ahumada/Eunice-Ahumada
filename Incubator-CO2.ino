/*
 Name:		Incubator-CO2.ino
 Created:	24 april 2024
 Authors:	Eunice Ahumada y Aarón Vélez
*/


//////////////////////////////////////////////////////////////////
////// Libraries and its associated constants and variables //////
//////////////////////////////////////////////////////////////////

#include <QueueArray.h>




//////////////////////////////////////////
////// User Constants and Variables //////
//////////////////////////////////////////

time_t local_t; // Variable that stores the number of seconds since a particular date and time
float CO2_concentration; // Variable that defines the CO2 concentration inside the incubator
enum EstadoValvula {CLOSE,OPEN}; // Variable that defines the possible states of the valve

QueueArray<int> event_queue;

// Define states for the state machine
enum State {
  IDLE,
  RUNNING,
  DOOR_OPEN,
  READ_RTC,
  UPDATE_RTC,
  READ_SENSORS,
  COMPUTE_PID,
  ACTUATE_SOLENOID,
  UPDATE_SCREEN,
  LOG_DATA,
  SEND_TO_CLOUD,
  CHECK_LIMITS
};


// Define events for the event-driven architecture
enum Event {
  TIME_TO_READ_RTC, // Time to read the real time clock
  TIME_TO_UPDATE_RTC, // Time to update the real time clock
  SENSOR_READING_READY, // The sensor is ready to measure CO2
  TIME_TO_READ_SENSOR, // Time to read the sensor
  CO2_MEASUREMENT, // Every minute the sensor reading is triggered to measure the CO2 concentration
  CO2_CONTROL, // If the CO2 concentration is less than 5% the solenoid valve is activated
  DATA_LOGGING, // Relevant data is storage in SD memory
  CLOUD_SEND, // Data is sent to the cloud
  CLOUD_SEND_SUCCESS, // Successful data sending
};


// Global variables
State currentState = IDLE;
const unsigned long intervalReadingSensors = 1000; // Interval for reading sensors in milliseconds
const unsigned long intervalLoggingData = 5000;    // Interval for logging data in milliseconds
const unsigned long intervalSendingToCloud = 10000; // Interval for sending data to cloud in milliseconds

// Pin Location Example
const int pinCO2SensorRX = 12; // The RX pin of the CO2 probe is connected to pin 12 of the ESP32
const int pinCO2SensorTX = 13; // The TX pin of the CO2 probe is connected to pin 13 of the ESP32



//////// Function prototypes

// Main States Handler
void handleEvent(Event event);

// User functions
void readSensors();
void logData();
void sendToCloud();
void handleAlarm();
void actuateSolenoid();
void updateRTC();
void updateScreen();
void checkLimits();
void computePID();



//////////////////////////////////////////////////////////////////////////
// the setup function runs once when you press reset or power the board //
//////////////////////////////////////////////////////////////////////////



void setup() {
  // Initialize serial communication
  Serial.begin(115200);
}




//////////////////////////////////////////////////////////////////////////
// The loop function runs over and over again until power down or reset //
//////////////////////////////////////////////////////////////////////////


void loop() 
{
 {
   // Placeholder for checking events (e.g., timer expiration, sensor readings, cloud status)
  // Simulated with delay for demonstration purposes
  // delay(1000);
  
  
  /////// Director (Procuder of Events)
  // TIME_TO_READ_RTC logic
  if (true) 
  { //replace true with adecuate logic
    event_queue.enqueue(TIME_TO_READ_RTC)
  }
  // TIME_TO_READ_SENSOR logic
  if (local_t % 300) 
  {
    event_queue.enqueue(TIME_TO_READ_SENSOR)
  }
  // Tesi if another event occurred
  // If so, add event to queue



  /////// Event handler (Consumer of Events)
  while (!event_queue.isEmpty()) 
  {
    Event currentEvent = event_queue.dequeue();
    handleEvent(currentEvent);
  }
 }
}


















