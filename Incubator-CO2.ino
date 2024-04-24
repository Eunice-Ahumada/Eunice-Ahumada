/*
 Name:		Arduino_code_Incubator_CO2.ino
 Created:	18/04/2024
 Author:	Eunice Lopez Ahumada
*/

///////////////////////////////////////////////////////////////////
////// Libraries and its associated constants and variables //////
/////////////////////////////////////////////////////////////////

////// Board library
#include <M5Stack.h>

////// Comunication libraries
#include <Wire.h>
#include <WiFi.h>
#include <WiFiUdp.h>
WiFiUDP ntpUDP; //Esta instancia se utiliza para realizar operaciones UDP

////// Library for CO2 Sensor


//CO2 sensor input GMP251//;
const int CO2In = 2; //Especificar el PIN de entrada del sensor
const int n = 500; // Mida n veces la entrada ADC para promediar 
float sum = 0; // Registro de desplazamiento para almacenar los datos del ADC


//////////////////////////////////////
////// Constants and Variables //////
////////////////////////////////////

