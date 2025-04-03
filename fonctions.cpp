#include "fonctions.h"
#include <math.h>
float gX = 0, gY = 0, gZ = 0;
float aX, aY, aZ;
//question sur optimisation de la taille de code!!!!
float mX, mY, mZ, mDirection;
MPU9250_asukiaaa mySensor;
Adafruit_GPS GPS(&GPS_SERIAL);
Adafruit_BMP280 bmp;
const int txPower = 20;
int counter = 0;
void initialiserCapteurs() {
  Serial.println("Initialisation des capteurs...");
  Wire.begin(SDA_PIN, SCL_PIN);
  mySensor.setWire(&Wire);
  mySensor.beginAccel();
  mySensor.beginGyro();
  mySensor.beginMag();
  Serial.println("MPU9250 prêt.");
  GPS_SERIAL.begin(9600, SERIAL_8N1, 16, 17);
  GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);
  GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ);
  Serial.println("GPS prêt.");
  if (!bmp.begin(0x77)) {
    Serial.println("Erreur: BMP280 non détecté!");
  } else {
    Serial.println("BMP280 prêt.");
  }
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
void lireMPU9250() {
  if (mySensor.accelUpdate() == 0) {
    aX = mySensor.accelX();
    aY = mySensor.accelY();
    aZ = mySensor.accelZ();
  }
  if (mySensor.gyroUpdate() == 0) {
    gX = mySensor.gyroX();
    gY = mySensor.gyroY();
    gZ = mySensor.gyroZ();
  }
  if (mySensor.magUpdate() == 0) {
    mX = mySensor.magX();
    mY = mySensor.magY();
    mZ = mySensor.magZ();
    mDirection = atan2(mY, mX) * 180 / M_PI;
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
void updateAcceleration() {
  mySensor.accelUpdate();
  float rawX = mySensor.accelX();
  float rawY = mySensor.accelY();
  float rawZ = mySensor.accelZ();

  gX = 0.9 * gX + 0.1 * rawX;
  gY = 0.9 * gY + 0.1 * rawY;
  gZ = 0.9 * gZ + 0.1 * rawZ;

  aX = rawX - gX;
  aY = rawY - gY;
  aZ = rawZ - gZ;
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
  message += "Temp:" + String(bmp.readTemperature(), 2) + ",";
  message += "Pressure:" + String(bmp.readPressure() / 100.0, 2);
  return message;
}
void delay_second(int s) {
  delay(s * 1000);
}
void afficherDonnees() {
  Serial.print("Temp: ");
  Serial.print(bmp.readTemperature());
  Serial.println("°C ");
  Serial.print("Pression: ");
  Serial.print(bmp.readPressure() / 100.0);
  Serial.println(" hPa");
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