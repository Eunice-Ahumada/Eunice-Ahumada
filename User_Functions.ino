#include "Incubator-CO2.ino"
#include <Wire.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

#define CO2_SENSOR_ADDRESS 0x23


void timerExpired() {
  handleEvent();
}


void timeToReadRTC() {

  DateTime now = rtc.now(); // Print the time in the format HH:MM:SS
  
  Serial.print(now.hour(), DEC);
  Serial.print(':');
  Serial.print(now.minute(), DEC);
  Serial.print(':');
  Serial.println(now.second(), DEC);
 
  delay(1000);  // Wait a second before reading the time again
  
  handleEvent(TIMER_EXPIRED);
}


void timeToReadSensor() {
  unsigned long currentTime = millis();  // Get the current time in milliseconds
  if (currentTime - lastMeasurementTime >= 60000) { // Check if one minute has passed since the last measurement
    lastMeasurementTime = currentTime; // Update last measurement time
  }
  handleEvent(CO2_MEASUREMENT);
}



void CO2Measurement() {
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


void sensorReadingReady() {

  Serial.println("Lectura del sensor lista");
  
}



void CO2Control() {
 
  def CO2Control(): // Definition of the CO2 Control function
  concentration = CO2Measurement() // CO2 concentration is initialized
  umbral = 5 // The CO2 concentration threshold of 5% is established

  while True:
  concentration = CO2Measurement() // Read the current CO2 concentration
    if concentration < umbral: // Check if the concentration is below 5%
      abrirValvulaSolenoide()
      print("Válvula solenoide abierta")
      elif concentration >= umbral: // Check if the concentration has reached 5%
      cerrarValvulaSolenoide()
      print("Válvula solenoide cerrada")

}


void dataLoggin() (int co2Concentration) 
{
  saveData(co2Concentration); // Save CO2 concentration data to SD card
  handleEvent(CLOUD_SEND); // Placeholder for triggering TIMER_EXPIRED event
}


void cloudSend() { 
 if (WiFi.status() == WL_CONNECTED) { // Check WiFi connection status
    HTTPClient http;

    http.begin(serverName); // Specify the URL
    http.addHeader("Content-Type", "application/x-www-form-urlencoded"); // Specify content-type header

    int co2Concentration = 500; // Replace with the actual CO2 concentration value
    String httpRequestData = "co2=" + String(co2Concentration); // Prepare the data to be sent

    int httpResponseCode = http.POST(httpRequestData); // Send the request

    if (httpResponseCode > 0) {
      String response = http.getString(); // Get the response to the request
      Serial.println(httpResponseCode); // Print return code
      Serial.println(response); // Print request answer
    } else {
      Serial.print("Error on sending POST: "); }
}
}



void cloudSendSuccess() { 
  Serial.println("Envío a la nube exitoso");
  // Aquí puedes agregar más acciones relevantes, como encender un LED, enviar una notificación, etc.
}





