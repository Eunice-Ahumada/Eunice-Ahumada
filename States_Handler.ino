
void handleEvent(Event event) {
  switch (currentState) {
    case IDLE:
      // Handle events in IDLE state
      if (event == TIMER_EXPIRED) {
        currentState = READING_SENSORS;
        readSensors();
      }
      break;
    case READING_SENSORS:
      // Handle events in READING_SENSORS state
      if (event == SENSOR_READING_READY) {
        currentState = LOGGING_DATA;
        logData();
      }
      break;
    case LOGGING_DATA:
      // Handle events in LOGGING_DATA state
      if (event == TIMER_EXPIRED) {
        currentState = SENDING_TO_CLOUD;
        sendToCloud();
      }
      break;
    case SENDING_TO_CLOUD:
      // Handle events in SENDING_TO_CLOUD state
      if (event == CLOUD_SEND_SUCCESS) {
        currentState = IDLE;
        // Reset timer for reading sensors
      }
      break;
    case ALARM_TRIGGERED:
      // Handle events in ALARM_TRIGGERED state
      // Wait for manual reset or timeout
      break;
  }
}