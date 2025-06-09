#include "GPS.h"
Adafruit_GPS GPS(&Wire);
#define GPSECHO false
uint32_t timer = millis();
void init_GPS(void) {
  GPS.begin(0x10);           // Initialisation GPS
  GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);// recomended minimum et fix data
  GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ);  
  GPS.sendCommand(PGCMD_ANTENNA); //status antenne
  GPS.println(PMTK_Q_RELEASE); // demande version firmware

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
  mesure_GPS();
  affichage_GPS();
}