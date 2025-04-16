//**********************************************
// Kos Alan 6A
// Station de mesure embarquée pour voiture
// Utilise : ESP32 DEVKIT V1, MPU_9250, GPSPA1010D, BMP280
//****************COMENTAIRES*******************
//faut optimiser!
//SD comment sa marche ???
//gps faire fonctionner et magnetometre
//**********************************************
#include "fonctions.h"

void setup() {
  Serial.begin(115200);
  while (!Serial);
  Serial.println("System initialized");
  Wire.begin(SDA_PIN, SCL_PIN);
  initBmp280();
  initMpu9250();
  initLoRa();
  delay_second(1); 
}

void loop() {
  Serial.println("\n--- Données des capteurs ---");
  //lireGPS();
  afficherDonnees();
  delay(200);
  GetDataBmp280();
  delay(200);
  GetDataMpu9250();
  delay(200);
  sendLoRa();
  delay(1000);
}
