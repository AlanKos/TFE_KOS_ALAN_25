#include "fonctions.h"
#include <math.h>
#include "Bmp280.h"
#include "Mpu9250.h"
#include "LoRaAK.h"
#include "GPS.h"
#include <Adafruit_GPS.h>

String prepareLoRaMessage() {
  String message = "Accel_X:" + String(aX, 2) + ",";
  message += "Accel_Y:" + String(aY, 2) + ",";
  message += "Accel_Z:" + String(aZ, 2) + ",";
  message += "Gyro_X:" + String(gX, 2) + ",";
  message += "Gyro_Y:" + String(gY, 2) + ",";
  message += "Gyro_Z:" + String(gZ, 2) + ",";
  message += "Temp:" + String(Bmp280_Temp) +"°C,";
  message += "Pression:" + String(Bmp280_Press / 100.0) + "hPa,";
  message += "Altitude:" + String(Bmp280_Alt) + "m,";
  message += "longtude:" + String(GPS.longitude, 4) + ",";
  message += "latitude:" + String(GPS.latitude, 4) + ",";
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
  Serial.print("Date: ");
  Serial.print(GPS.day, DEC);
  Serial.print('/');
  Serial.print(GPS.month, DEC);
  Serial.print("/20");
  Serial.println(GPS.year, DEC);
  Serial.print("Fix: ");
  Serial.print((int)GPS.fix);
  Serial.print(" quality: ");
  Serial.println((int)GPS.fixquality);
  if (GPS.fix) {  
    Serial.println("GPS Data:");
    Serial.print("  Latitude: ");
    Serial.print(GPS.latitude, 4);
    Serial.print(GPS.lat);
    Serial.print("  Longitude: ");
    Serial.print(GPS.longitude, 4);
    Serial.println(GPS.lon);
    Serial.printf("Sattelites: %02d \n", GPS.satellites);
    Serial.printf("Altitude: %.2f meters \n", GPS.altitude);
    Serial.printf("Speed: %.2f knots \n", GPS.speed);
    Serial.printf("Course: %.2f degrees \n", GPS.angle);
    Serial.printf("Date: %02d / %02d / %02d \n", GPS.day, GPS.month, GPS.year);
    Serial.printf("Time: %02d:%02d:%02d \n", GPS.hour, GPS.minute, GPS.seconds);
  }
   else
  {
    Serial.println("Waiting for GPS fix...");
  }
}