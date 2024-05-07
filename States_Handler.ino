void handleEvent(Event event) {
  switch (currentState) {
    
    case IDLE:
      if (event == TIMER_EXPIRED) {
        currentState = READING_SENSOR;
        timeToReadSensor();
      } else if (event == TIME_TO_READ_RTC) {
        currentState = READING_RTC;
        timeToReadRTC();
      }
      break;

    case READING_RTC:
      if (event == SENSOR_READING_READY) {
        currentState = READING_SENSOR;
        sensorReadingReady();
      }
      break;

    case UPDATING_RTC:
      if (event == TIME_TO_UPDATE_RTC) {
        currentState = IDLE;
        timeToUpdateRTC();
      }
      break;

    case READING_SENSOR:
      if (event == CO2_MEASUREMENT) {
        currentState = CONTROLLING_CO2;
        CO2Measurement();
      } else if (event == CO2_CONTROL) {
        CO2Control();
      } else if (event == DATA_LOGGING) {
        currentState = LOGGING_DATA;
        dataLogging();
      } else if (event == CLOUD_SEND) {
        currentState = SENDING_TO_CLOUD;
        cloudSend();
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
