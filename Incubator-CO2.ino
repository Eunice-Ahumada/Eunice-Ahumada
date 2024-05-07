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
#include <Wire.h>
#include <SD.h>



//////////////////////////////////////
////// Constants and Variables //////
////////////////////////////////////

time_t local_t; // Variable that stores the number of seconds since a particular date and time
float CO2_concentration; // Variable that defines the CO2 concentration inside the incubator
enum EstadoValvula {CLOSE,OPEN}; // Variable that defines the possible states of the valve

QueueArray<int> event_queue;

// Main States Handler
void handleEvent(Event event);

// States for the state machine
enum State {
  IDLE, // The system is waiting for an event
  READING_RTC,
  UPDATING_RTC,
  READING_SENSOR,
  CONTROLLING_CO2,
  LOGGING_DATA,
  SENDING_TO_CLOUD,
  CLOUD_SEND_SUCCESS, 

};


// Define events for the event-driven architecture
enum Event {
  TIMER_EXPIRED, // Indicates that a certain time interval has passed
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
const int CO2_SENSOR_ADDRESS = 0x23;
const int SD_CHIP_SELECT = 10; // Pin for the chip select of the SD card

// Pin Location Example
const int pinCO2SensorRX = 12; // The RX pin of the CO2 probe is connected to pin 12 of the ESP32
const int pinCO2SensorTX = 13; // The TX pin of the CO2 probe is connected to pin 13 of the ESP32


// User functions
void timerExpired();
void timeToReadRTC();
void timeToUpdateRTC();
void sensorReadingReady();
void timeToReadSensor();
void CO2Measurement();
void CO2Control();
void dataLogging();
void cloudSend();
void cloudSendSuccess();




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
 
/////// Director (Procuder of Events) Como se llavarán a cabo los eventos
  
 //// Time ////

  // TIME_TO_READ_RTC logic
  if (true) 
  { //replace true with adequate logic
    event_queue.enqueue(TIME_TO_READ_RTC)
  }

  //TIME_TO_UPDATE_RTC logic
  if (local_t % 1 == 0) // The time is updated every second
  {
    event_queue.enqueue(TIME_TO_UPDATE_RTC);
  }

 //// CO2 Sensor ////

  // TIME_TO_READ_SENSOR logic
  if (local_t % 60 == 0) // Read the sensor every minute
  {
    event_queue.enqueue(TIME_TO_READ_SENSOR)
  }
 
  // CO2_MEASUREMENT logic
  if (local_t % 60 == 0 && local_t > 0) // CO2 measurement every minute
  {
    event_queue.enqueue(CO2_MEASUREMENT);
  }

  // SENSOR READING READY logic
  if (local_t % 60 == 0) // Sensor reading ready
  {
    event_queue.enqueue(SENSOR_READING_READY);
  }

  // CO2_CONTROL logic
  if (CO2_concentration != 5.0) // CO2 control when the measured concentration is different than 5%
  {
    event_queue.enqueue(CO2_CONTROL);
  }

 //// Data ////
   
  // DATA_LOGGING logic
  if (local_t % 3600 == 0 && local_t > 0) // Record data every hour
  {
    event_queue.enqueue(DATA_LOGGING);
  }

  // CLOUD_SEND logic
  if (local_t % 3600 == 0 && local_t > 0) // Send data to the cloud every hour
  {
    event_queue.enqueue(CLOUD_SEND);
  }

  bool send_success = sendToCloud();

  // CLOUD_SEND_SUCCESS logic
  if (success_condition) // Check if sending to the cloud was successful
  {
    event_queue.enqueue(CLOUD_SEND_SUCCESS); 
  }



/////// Event handler (Consumer of Events)

  while (!event_queue.isEmpty()) // Continues as long as the event queue is not empty
  {
    Event currentEvent = event_queue.dequeue();
    handleEvent(currentEvent);
  }
 

}


















