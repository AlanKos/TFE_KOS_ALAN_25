#ifndef GPS_H     
#define GPS_H

#include <Adafruit_GPS.h> 
#include <HardwareSerial.h>

#define adresse_GPS 0x10

extern Adafruit_GPS GPS;

void init_GPS(void);
void mesure_GPS(void);
void affichage_GPS(void);
void lecture_GPS(void);
float convertToDecimalDegrees();
#endif