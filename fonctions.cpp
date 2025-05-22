#include "fonctions.h"
#include <math.h>
#include "Bmp280.h"
#include "Mpu9250.h"
#include "LoRaAK.h"
#include "GPS.h"
#include <Adafruit_GPS.h>
const uint8_t tachPin = 4;
volatile uint32_t prevRiseTime = 0;
volatile uint32_t riseTime     = 0;
volatile uint32_t fallTime     = 0;
volatile uint32_t highTime     = 0;
volatile uint32_t periodTime   = 0;
volatile bool     newData      = false;

float duty = 0;
float freq = 0;
float rpm = 0;

String prepareLoRaMessage() {
  String message = "Accel_X:" + String(aX, 2) + ",";
  message += "Accel_Y:" + String(aY, 2) + ",";
  message += "Accel_Z:" + String(aZ, 2) + ",";
  message += "Gyro_X:" + String(gX, 2) + ",";
  message += "Gyro_Y:" + String(gY, 2) + ",";
  message += "Gyro_Z:" + String(gZ, 2) + ",";
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
  Serial.print("Duty cycle: ");
  Serial.print(duty, 1);
  Serial.println(" %\t");
  Serial.print("Freq: ");
  Serial.print(freq, 1);
  Serial.println(" Hz\t");
  Serial.print("RPM: ");
  Serial.println(rpm, 0);
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

void tacy() {
  if (newData) {
    noInterrupts();
    uint32_t high = highTime;
    uint32_t period = periodTime;
    newData = false;
    interrupts();

    duty = (float)high / (float)period * 100.0;
    freq = 1e6 / (float)period;
    rpm = freq * 60.0;
  }
}

void isrPWM() {
  uint32_t t = micros();
  bool level = digitalRead(tachPin);

  if (level) {
    riseTime = t;
    if (prevRiseTime != 0) {
      periodTime = t - prevRiseTime;
    }
    prevRiseTime = t;

  } else {
    fallTime = t;
    if (riseTime != 0) {
      highTime = fallTime - riseTime;
      newData = true;
    }
  }
}
