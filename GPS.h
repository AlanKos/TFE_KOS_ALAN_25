#ifndef GPS_H     
#define GPS_H

#include <Adafruit_GPS.h> 
#include <HardwareSerial.h>

#define adresse_GPS 0x10

extern Adafruit_GPS GPS;

int init_GPS(char GPS_adr);
void etat_GPS(char GPS_adresse);
void mesure_GPS(void);
void affichage_GPS(void);
void lecture_GPS(void);
float convertToDecimalDegrees();
#endif