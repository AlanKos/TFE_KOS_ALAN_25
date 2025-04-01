//**********************************************
// Kos Alan 6A
// Station de mesure embarquée pour voiture
// Utilise : ESP32 DEVKIT V1, MPU_9250, GPSPA1010D, BMP280
//****************COMENTAIRES*******************
//aucune idee comment le string marche jdois voir
//faut optimiser!
//bordel en loop
//plein de trucs en double jpense faut corriger
//FAUT FAIRE FONCTIONNER LE LORA!!!!
//SD comment sa marche ???
//**********************************************
#include "fonctions.h"
void setup() {
  Serial.begin(115200);
  while (!Serial);
  Serial.println("System initialized");
  initialiserCapteurs();
  delay_second(1); 
}

void loop() {
  updateAcceleration();
  Serial.println("\n--- Données des capteurs ---");
  lireGPS();
  lireBMP280();
  afficherDonnees();
  String dataToSend = prepareLoRaMessage();
  Serial.println("Données LoRa envoyées : " + dataToSend);  
  LoRa.beginPacket();
  LoRa.print(dataToSend); 
  LoRa.endPacket();
  Serial.println("LoRa Sent: " + dataToSend); 
  delay_second(2);
}
