//**********************************************
// Kos Alan 6A
// Station de mesure embarquée pour voiture
// Utilise : ESP32 DEVKIT V1, MPU_9250, GPSPA1010D, BMP280
//**********************************************
#include "fonctions.h"

void setup() {
  Serial.begin(115200);
  while (!Serial);
  Serial.println("System initialized");
  Wire.begin(SDA_PIN, SCL_PIN);
  initBmp280();
  init_GPS();
  initMpu9250();
  initLoRa();
  delay_second(1); 
}

void loop() {
  Serial.println("\n--- Données des capteurs ---");
  GetDataBmp280();
  GetDataMpu9250();
  mesure_GPS();
  afficherDonnees();
  sendLoRa();
  delay(1000);
}
