/*
 Name:		Arduino_code_Incubator_CO2.ino
 Created:	18/04/2024
 Author:	Eunice Lopez Ahumada
*/
#include <M5Stack.h>
#include <SoftwareSerial.h>

#define CO2_SENSOR_PIN 2 // Pin TX de la sonda de CO2
#define CO2_SENSOR_BAUDRATE 9600 // Baud rate de la sonda de CO2
#define SOLENOID_PIN 13 // Pin GPIO para controlar la válvula solenoide

#define TARGET_CO2_LEVEL 500 // Nivel objetivo de CO2 (en ppm)
#define CO2_HYSTERESIS 50 // Histéresis para el control de CO2 (en ppm)

SoftwareSerial co2Sensor(CO2_SENSOR_PIN, CO2_SENSOR_PIN - 1); // Crear instancia de SoftwareSerial para la sonda de CO2

void setup() {
  Serial.begin(115200); // Iniciar la comunicación serial
  co2Sensor.begin(CO2_SENSOR_BAUDRATE); // Iniciar la comunicación con la sonda de CO2
  pinMode(SOLENOID_PIN, OUTPUT); // Configurar el pin de control de la válvula solenoide como salida
}

void loop() {
  // Leer la concentración de CO2 de la sonda
  int co2Concentration = readCO2Concentration();

  // Mostrar la concentración de CO2 en la pantalla
  M5.Display.clear();
  M5.Display.print("Concentración de CO2: ");
  M5.Display.print(co2Concentration);
  M5.Display.println(" ppm");

  // Controlar la válvula solenoide
  if (co2Concentration > TARGET_CO2_LEVEL + CO2_HYSTERESIS) {
    digitalWrite(SOLENOID_PIN, LOW); // Abrir la válvula solenoide para reducir el CO2
  } else if (co2Concentration < TARGET_CO2_LEVEL - CO2_HYSTERESIS) {
    digitalWrite(SOLENOID_PIN, HIGH); // Cerrar la válvula solenoide para aumentar el CO2
  }

  delay(1000); // Esperar 1 segundo antes de realizar la siguiente lectura
}

int readCO2Concentration() {
  // Leer datos de la sonda de CO2
  while (co2Sensor.available() == 0) {
    delay(1);
  }

  byte data[9];
  co2Sensor.readBytes(data, 9);

  // Extraer la concentración de CO2 de los datos
  int co2Concentration = (data[2] << 8) | data[3];

  return co2Concentration;
}
