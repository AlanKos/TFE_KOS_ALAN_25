#include "fonctions.h"
#include <math.h>
#include "Bmp280.h"
#include "Mpu9250.h"
//question sur optimisation de la taille de code!!!!
MPU9250_asukiaaa mySensor;
Adafruit_GPS GPS(&GPS_SERIAL);
const int txPower = 20;
int counter = 0;
void initialiserCapteurs() {
  Serial.println("Initialisation des capteurs...");

  
  GPS_SERIAL.begin(9600, SERIAL_8N1, 16, 17);
  GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);
  GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ);
  Serial.println("GPS prêt.");
  LoRa.setPins(ss, rst, dio0);
  if (!LoRa.begin(433E6)) {
    Serial.println("Erreur: LoRa non détecté!");
  } else {
    LoRa.setTxPower(txPower);
    LoRa.setSpreadingFactor(12);
    LoRa.setSignalBandwidth(125E3);
    LoRa.setCodingRate4(5);
    LoRa.setPreambleLength(8);
    LoRa.setSyncWord(0xF3);
    Serial.println("LoRa prêt.");
  }
}

void lireGPS() {
  if (GPS.newNMEAreceived() && GPS.parse(GPS.lastNMEA())) {
    if (GPS.fix) {
      float latitude = convertToDecimalDegrees(GPS.latitude);
      float longitude = convertToDecimalDegrees(GPS.longitude);
      Serial.print("GPS - Lat: ");
      Serial.print(latitude, 6);
      Serial.print(", Lon: ");
      Serial.println(longitude, 6);
    }
  }
}

void envoi_donnees() {
  String dataToSend = prepareLoRaMessage();
  LoRa.beginPacket();
  LoRa.print(dataToSend);
  LoRa.endPacket();
  Serial.println("LoRa Sent: " + dataToSend);
  counter++;
}

float convertToDecimalDegrees(float nmeaDegrees) {
  int degrees = (int)(nmeaDegrees / 100);
  float minutes = nmeaDegrees - (degrees * 100);
  return degrees + (minutes / 60.0);
}
String prepareLoRaMessage() {
  String message = "Accel_X:" + String(aX, 2) + ",";
  message += "Accel_Y:" + String(aY, 2) + ",";
  message += "Accel_Z:" + String(aZ, 2) + ",";
  message += "Gyro_X:" + String(gX, 2) + ",";
  message += "Gyro_Y:" + String(gY, 2) + ",";
  message += "Gyro_Z:" + String(gZ, 2) + ",";
  message += "Mag_X:" + String(mX, 2) + ",";
  message += "Mag_Y:" + String(mY, 2) + ",";
  message += "Mag_Z:" + String(mZ, 2) + ",";
  message += "Mag_Dir:" + String(mDirection, 2) + ",";
  if (GPS.fix) {
    float latitude = convertToDecimalDegrees(GPS.latitude);
    float longitude = convertToDecimalDegrees(GPS.longitude);
    message += "Lat:" + String(latitude, 6) + String(GPS.lat) + ",";
    message += "Lon:" + String(longitude, 6) + String(GPS.lon) + ",";
    message += "Alt:" + String(GPS.altitude, 2) + ",";
    message += "Speed:" + String(GPS.speed, 2) + ",";
  } else {
    message += "GPS:NoFix,";
  }
  // message += "Temp:" + String(bmp.readTemperature(), 2) + ",";
  //message += "Pressure:" + String(bmp.readPressure() / 100.0, 2) + ",";
  //message += "Altitude" + String(bmp.readAltitude(1022.5));
  return message;
}
void delay_second(int s) {
  delay(s * 1000);
}
void afficherDonnees() {
  Serial.print("Temp: ");
  Serial.print(Bmp280_Temp);
  Serial.println("°C ");
  Serial.print("Pression: ");
  Serial.print(Bmp280_Press / 100.0);
  Serial.println(" hPa");
  Serial.print("Altitude: ");
  Serial.print(Bmp280_Alt);
  Serial.println(" m");
  Serial.print("Accel filtrée - X: ");
  Serial.print(aX);
  Serial.print(", Y: ");
  Serial.print(aY);
  Serial.print(", Z: ");
  Serial.println(aZ);
  Serial.print("Gyro          - X: ");
  Serial.print(gX);
  Serial.print(", Y: ");
  Serial.print(gY);
  Serial.print(", Z: ");
  Serial.println(gZ);
}

String millisToTimeString(unsigned long currentMillis) {
  unsigned long hours = currentMillis / 3600000UL;
  unsigned long minutes = (currentMillis % 3600000UL) / 60000UL;
  unsigned long seconds = (currentMillis % 60000UL) / 1000UL;
  unsigned long milliseconds = currentMillis % 1000UL;

  char buffer[15];  // "hh:mm:ss.ms" + null terminator
  snprintf(buffer, sizeof(buffer), "%02lu:%02lu:%02lu.%03lu", hours, minutes, seconds, milliseconds);

  return String(buffer);
}