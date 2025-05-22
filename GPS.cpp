#include "GPS.h"

HardwareSerial GPSSerial(2);  
Adafruit_GPS GPS(&GPSSerial);
byte status_GPS = 1;

int init_GPS(char GPS_adr) {
  GPSSerial.begin(9600);         // Démarre la communication série avec le GPS
  GPS.begin(9600);               // Initialisation Adafruit GPS

  GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);
  GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ);  
  GPS.sendCommand(PMTK_API_SET_FIX_CTL_1HZ);

  if (GPS.begin(9600)) {
    status_GPS = 0;
  } else {
    status_GPS = 1;
  }

  return status_GPS;
}

void etat_GPS(char GPS_adresse) {
  if (init_GPS(GPS_adresse) == 1) {
    Serial.println("échec démarrage GPS ");
  } else {
    Serial.println("initialisation GPS OK");
  }
}

void mesure_GPS() {
  GPS.read();  
  if (GPS.newNMEAreceived()) {
    if (!GPS.parse(GPS.lastNMEA())) {
      Serial.println("erreur d'analyse");
    }
  }
}

void affichage_GPS() {
  Serial.print("Satellites detected: ");
  Serial.println(GPS.satellites);  
}   

void lecture_GPS() {
  if (status_GPS == 0) {
    mesure_GPS();
    affichage_GPS();
  }
}

float convertToDecimalDegrees(float nmeaDegrees) {
  int degrees = (int)(nmeaDegrees / 100);
  float minutes = nmeaDegrees - (degrees * 100);
  return degrees + (minutes / 60.0);
}