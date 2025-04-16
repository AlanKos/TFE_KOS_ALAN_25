#ifndef FONCTIONS_H
#define FONCTIONS_H
#include <Arduino.h>
#include "Bmp280.h"
#include "Mpu9250.h"
#include <Wire.h>
//#include <Adafruit_GPS.h>
#include <SPI.h>
#include "LoRaAK.h"
#include "LoRa.h"
#define SDA_PIN 21
#define SCL_PIN 22
#define GPS_SERIAL Serial2  
#define PMTK_SET_NMEA_UPDATE_1HZ "$PMTK220,1000*1F"
#define PMTK_SET_NMEA_OUTPUT_RMCGGA "$PMTK314,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0*28"
//extern MPU9250_asukiaaa mySensor;
//extern Adafruit_GPS GPS;
String millisToTimeString(unsigned long currentMillis); 

//void lireGPS(void);
void afficherDonnees(void);
//float convertToDecimalDegrees(float nmeaDegrees);
void delay_second(int s);
String prepareLoRaMessage(void);
#endif 