#include "Incubator-CO2.ino"

void handleEvent(Event event) { // Takes an event as argument
  switch (currentState) { // Evaluates the current state of the system
    
    case IDLE:
      if (event == TIMER_EXPIRED) { // If the event is TIMER_EXPIRED, the current system state is updated to READING_SENSOR
        currentState = READING_SENSOR; 
        timeToReadSensor();
      } else if (event == TIME_TO_READ_RTC) { // If the event is not TIMER_EXPIRED, it is checked if it is TIME_TO_READ_RTC
        currentState = READING_RTC;
        timeToReadRTC(); // Perform the action associated with this event
      }
      break;

   case READING_RTC:
     if (event == TIME_TO_READ_SENSOR) {
        currentState = READING_SENSOR;
        timeToReadSensor();
     }  else if (event == TIME_TO_READ_RTC) {
        currentState = IDLE;
        timeToReadRTC();
     }
     break;


    case READING_SENSOR:
      if (event == TIME_TO_READ_SENSOR) {
        currentState = CONTROLLING_CO2;
        timeToReadSensor();
      } else if (event == CO2_MEASUREMENT) {
        currentState = CONTROLLING_CO2;
        CO2Measurement();
      } else if (event == SENSOR_READING_READY) {
        currentState = LOGGING_DATA;
        sensorReadingReady();
      }  
      break;

    case CONTROLLING_CO2:
      if (event == CO2_CONTROL) {
        CO2Control();
      } else if (event == DATA_LOGGING) {
        currentState = LOGGING_DATA;
        dataLogging();
      } else if (event == CLOUD_SEND) {
        currentState = SENDING_TO_CLOUD;
        cloudSend();
      }
      break;

    case LOGGING_DATA:
      if (event == CLOUD_SEND) {
        currentState = SENDING_TO_CLOUD;
        cloudSend();
      }
      break;

    case SENDING_TO_CLOUD:
      if (event == CLOUD_SEND_SUCCESS) {
        currentState = IDLE;
        cloudSendSuccess();
      }
      break;
  }
}
