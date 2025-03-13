#ifndef FONCTIONS_H
#define FONCTIONS_H
#include <Arduino.h>
#include <Wire.h>
#include <MPU9250_asukiaaa.h>
#include <Adafruit_GPS.h>
#include <Adafruit_BMP280.h>
#include <SPI.h>
#include <LoRa.h>
#define ss 14
#define rst 5
#define dio0 2
#define SDA_PIN 21
#define SCL_PIN 22
#define GPS_SERIAL Serial2  
#define PMTK_SET_NMEA_UPDATE_1HZ "$PMTK220,1000*1F"
#define PMTK_SET_NMEA_OUTPUT_RMCGGA "$PMTK314,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0*28"
extern MPU9250_asukiaaa mySensor;
extern Adafruit_GPS GPS;
extern Adafruit_BMP280 bmp;
void initialiserCapteurs();
void lireMPU9250();
void lireGPS();
void lireBMP280();
void afficherDonnees();
float convertToDecimalDegrees(float nmeaDegrees);
void delay_second(int s);
void envoi_donnees();
#endif // FONCTIONS_H