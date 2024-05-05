/*
 Name:		Incubator-CO2.ino
 Created:	24 april 2024
 Authors:	Eunice Ahumada y Aarón Vélez
*/


//////////////////////////////////////////////////////////////////
////// Libraries and its associated constants and variables //////
//////////////////////////////////////////////////////////////////

#include <QueueArray.h>
#include <TimeLib.h>


//////////////////////////////////////////
////// Constants and Variables //////
//////////////////////////////////////////

time_t local_t; // Variable that stores the number of seconds since a particular date and time
float CO2_concentration; // Variable that defines the CO2 concentration inside the incubator
enum EstadoValvula {CLOSE,OPEN}; // Variable that defines the possible states of the valve

QueueArray<int> event_queue;

// Main States Handler
void handleEvent(Event event);

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
const unsigned long intervalReadingSensors = 60000; // Interval for reading sensors in milliseconds
const unsigned long intervalLoggingData = 3600000;    // Interval for logging data in milliseconds
const unsigned long intervalSendingToCloud = 3600000; // Interval for sending data to cloud in milliseconds

// Pin Location Example
const int pinCO2SensorRX = 12; // The RX pin of the CO2 probe is connected to pin 12 of the ESP32
const int pinCO2SensorTX = 13; // The TX pin of the CO2 probe is connected to pin 13 of the ESP32


// User functions
void readSensors();
void logData();
void sendToCloud();
void actuateSolenoid();
void updateRTC();
void updateScreen();
void computePID();



/////////////////////////
////// the setup ///////
///////////////////////


void setup() {
  // Initialize serial communication
  Serial.begin(115200); 
}




///////////////////////
////// The loop //////
/////////////////////


void loop() 
{
 
  /////// Director (Procuder of Events)
  
  // Add events
  
  // TIME_TO_READ_RTC logic
  if (true) 
  { //replace true with adecuate logic
    event_queue.enqueue(TIME_TO_READ_RTC)
  }
  // TIME_TO_READ_SENSOR logic
  if (local_t % 300 == 0) 
  {
    event_queue.enqueue(TIME_TO_READ_SENSOR)
  }
 

  /////// Event handler (Consumer of Events)

  // Add events

  while (!event_queue.isEmpty()) 
  {
    Event currentEvent = event_queue.dequeue();
    handleEvent(currentEvent);
  }
 

 /////// Main event handler (Events with functions)

void handleEvent(Event event) 
  {
  switch(event) 
   {
    case TIME_TO_READ_RTC:
      updateRTC();
      break;
    case TIME_TO_READ_SENSOR:
      readSensors();
      break;
   }    
  }  


}


















