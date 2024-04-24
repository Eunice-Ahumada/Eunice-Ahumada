/*
 Name:		Incubator-CO2.ino
 Created:	24 april 2024
 Authors:	Eunice Ahumada y Aarón Vélez
*/




//////////////////////////////////////////////////////////////////
////// Libraries and its associated constants and variables //////
//////////////////////////////////////////////////////////////////










//////////////////////////////////////////
////// User Constants and Variables //////
//////////////////////////////////////////




// Define states for the state machine
enum State {
  IDLE,
  UPDATE_RTC
  READ_SENSORS,
  COMPUTE_PID
  ACTUATE_SOLENOID
  UPDATE_SCREEN,
  LOG_DATA,
  SEND_TO_CLOUD,
  CHECK_LIMITS
};

// Define events for the event-driven architecture
enum Event {
  TIMER_EXPIRED,
  SENSOR_READING_READY,
  CLOUD_SEND_SUCCESS,
  ALARM_TRIGGERED_EVENT
};



// Global variables
State currentState = IDLE;
unsigned long intervalReadingSensors = 1000; // Interval for reading sensors in milliseconds
unsigned long intervalLoggingData = 5000;    // Interval for logging data in milliseconds
unsigned long intervalSendingToCloud = 10000; // Interval for sending data to cloud in milliseconds




//////// Function prototypes
// Main States Handler
void handleEvent(Event event);

// User functions
void readSensors();
void logData();
void sendToCloud();
void handleAlarm();











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


void loop() {
  // Placeholder for checking events (e.g., timer expiration, sensor readings, cloud status)
  // Simulated with delay for demonstration purposes
  delay(1000);
  
  // Placeholder for triggering events based on conditions
  // Simulated with random events for demonstration purposes
  Event randomEvent = static_cast<Event>(random(TIMER_EXPIRED, ALARM_TRIGGERED_EVENT + 1));
  handleEvent(randomEvent);
}


















