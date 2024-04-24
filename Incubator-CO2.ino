/*
 Name:		Arduino_code_Incubator_CO2.ino
 Created:	18/04/2024
 Author:	Eunice Lopez Ahumada
*/


#include <M5Core2.h>
#include <Wire.h>
#include "GMP251.h"

// Definir el pin de control de la válvula solenoide
#define VALVE_PIN 32

// Inicializar el sensor de CO2
GMP251 sensor_co2;

void setup() {
  M5.begin();
  Wire.begin();
  
  // Configurar el pin de la válvula solenoide
  pinMode(VALVE_PIN, OUTPUT);
  digitalWrite(VALVE_PIN, LOW);

  M5.Lcd.clear();
  M5.Lcd.setTextSize(2);
  M5.Lcd.setCursor(50, 50);
  M5.Lcd.println("Control de CO2");
  M5.Lcd.setCursor(50, 80);
  M5.Lcd.println("en incubadora");
}

void loop() {
  // Medir la concentración de CO2
  int concentration = sensor_co2.read();
  
  // Mostrar la concentración de CO2 en la pantalla
  M5.Lcd.setCursor(50, 120);
  M5.Lcd.printf("CO2: %d ppm", concentration);
  
  // Regular la concentración de CO2 al 5%
  int desired_concentration = 5000; // 5% de CO2 en ppm
  if (concentration < desired_concentration) {
    // Encender la válvula solenoide para añadir CO2
    digitalWrite(VALVE_PIN, HIGH);
  } else {
    // Apagar la válvula solenoide si la concentración es suficiente
    digitalWrite(VALVE_PIN, LOW);
  }

  delay(10000); // Medir y regular cada 10 segundos
}

