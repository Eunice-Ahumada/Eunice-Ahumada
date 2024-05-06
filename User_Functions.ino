#include "Incubator-CO2.ino"

#include <Wire.h>
#define CO2_SENSOR_ADDRESS 0x23



void readSensor() 
{
  
  Wire.begin(); // Initializes I2C communication

  Wire.requestFrom(CO2_SENSOR_ADDRESS, 2); // Requests 2 bytes of sensor data

  while (Wire.available() < 2); // Wait until all bytes are received
 
  byte msb = Wire.read(); // Read received bytes
  byte lsb = Wire.read();

  int co2Concentration = (msb << 8) | lsb; // Calculates the concentration of CO2 in parts per million (ppm)
  
  Serial.print("CO2 Concentration: "); // Print the CO2 concentration on the serial monitor
  Serial.print(co2Concentration);
  Serial.println(" ppm");

  logData(co2Concentration);

  handleEvent(SENSOR_READING_READY); // Placeholder for triggering SENSOR_READING_READY event
}




void logData() (int co2Concentration) 
{
  saveData(co2Concentration); // // Save CO2 concentration data to SD card

  // Placeholder for triggering TIMER_EXPIRED event
  handleEvent(CLOUD_SEND);
}
 

 
void sendToCloud() 
{
  // Placeholder for sending data to cloud
  // Simulated with printing to serial monitor for demonstration purposes
  Serial.println("Sending data to cloud...");
  // Simulated delay
  delay(500);
  // Placeholder for triggering CLOUD_SEND_SUCCESS event
  handleEvent(CLOUD_SEND_SUCCESS);
}



void actuateSolenoid()
{
}

void updateRTC()
{
}

void updateScreen()
{
}

void checkLimits()
{
}

void computePID()
{
}
