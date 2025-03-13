#include "fonctions.h"
MPU9250_asukiaaa mySensor;
Adafruit_GPS GPS(&GPS_SERIAL);
Adafruit_BMP280 bmp;
const int txPower = 20;
int counter = 0;
// Initialisation des capteurs
void initialiserCapteurs() {
  Serial.println("Initialisation des capteurs...");
  // Initialisation du bus I2C
  Wire.begin(SDA_PIN, SCL_PIN);
  mySensor.setWire(&Wire);
  // Initialisation du MPU9250
  mySensor.beginAccel();
  mySensor.beginGyro();
  mySensor.beginMag();
  Serial.println("MPU9250 prêt.");
  // Initialisation du GPS
  GPS_SERIAL.begin(9600, SERIAL_8N1, 16, 17);
  GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);
  GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ);
  Serial.println("GPS prêt.");
  // Initialisation du BMP280
  bmp.begin(0x77);
  Serial.println("BMP280 prêt.");
  //Initialisation du LoRa
  LoRa.setPins(ss, rst, dio0);
  LoRa.begin(433E6);
  LoRa.setTxPower(txPower);        // Définit la puissance de transmission à la valeur maximale (20 dBm)
  LoRa.setSpreadingFactor(12);       // Définit le facteur d'étalement à 12 (pour une portée plus longue)
  LoRa.setSignalBandwidth(125E3);    // Définit la largeur de bande à 125 kHz (courant pour la longue portée)
  LoRa.setCodingRate4(5);            // Définit le taux de codage à 4/5 pour améliorer la fiabilité
  LoRa.setPreambleLength(8);         // Définit la longueur du préambule (aide à la portée)tt
  Serial.println("LOL");
  delay(500);
  LoRa.setSyncWord(0xF3);
  Serial.println("LoRa prêt.");
}
// Lecture du MPU9250
void lireMPU9250() {
  if (mySensor.accelUpdate() == 0) {
    Serial.print("Accel - X: ");
    Serial.print(mySensor.accelX());
    Serial.print(", Y: ");
    Serial.print(mySensor.accelY());
    Serial.print(", Z: ");
    Serial.println(mySensor.accelZ());
  }
  if (mySensor.gyroUpdate() == 0) {
    Serial.print("Gyro - X: ");
    Serial.print(mySensor.gyroX());
    Serial.print(", Y: ");
    Serial.print(mySensor.gyroY());
    Serial.print(", Z: ");
    Serial.println(mySensor.gyroZ());
  }
}
// Lecture du GPS
void lireGPS() {
  if (GPS.newNMEAreceived() && GPS.parse(GPS.lastNMEA())) {
    if (GPS.fix) {
      float latitude = convertToDecimalDegrees(GPS.latitude);
      float longitude = convertToDecimalDegrees(GPS.longitude);
      Serial.print("GPS - Latitude: ");
      Serial.print(latitude, 6);
      Serial.print(", Longitude: ");
      Serial.println(longitude, 6);
    }
  }
}
// Lecture du BMP280
void lireBMP280() {
  Serial.print("Température: ");
  Serial.print(bmp.readTemperature());
  Serial.println(" °C");
  Serial.print("Pression: ");
  Serial.print(bmp.readPressure() / 100.0);
  Serial.println(" hPa");
  Serial.print("Altitude: ");
  Serial.print(bmp.readAltitude(1013.25));
  Serial.println(" m");
}
// Envoi des données par LoRa
void envoi_donnees() {
  Serial.print("Sending packet: ");
  Serial.println(counter);
  LoRa.beginPacket();
  LoRa.print("hello ");
  LoRa.print(counter);
  LoRa.endPacket();
  counter++;
}
// Affichage de toutes les données
void afficherDonnees() {
  Serial.println("\n--- Données des capteurs ---");
  lireMPU9250();
  lireGPS();
  lireBMP280();
}
// Conversion NMEA → Degrés décimaux
float convertToDecimalDegrees(float nmeaDegrees) {
  int degrees = (int)(nmeaDegrees / 100);
  float minutes = nmeaDegrees - (degrees * 100);
  return degrees + (minutes / 60.0);
}
// delay en seconde
void delay_second(int s) {
  delay(s * 1000);
}