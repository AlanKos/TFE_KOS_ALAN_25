//**********************************************
// Kos Alan 6A
// Station de mesure embarquée pour voiture 
// Utilise : ESP32 DEVKIT V1, MPU_9250, GPSPA1010D, BMP280
//**********************************************
#include "fonctions.h"
void setup() {
  Serial.begin(115200);
  while (!Serial)
    ;
  Serial.println("System initialized");
  initialiserCapteurs();
}

void loop() {
  afficherDonnees();
  Serial.println("---");
  //envoi_donnees();
  delay_second(2);
}