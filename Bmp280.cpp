#include "Bmp280.h"

Adafruit_BMP280 bmp;
float temp, altitude, pressure;
float Bmp280_Temp, Bmp280_Press, Bmp280_Alt;

void initBmp280(void) {
  Serial.println("Init Bmp280");
  if (!bmp.begin(0x77)) {
    Serial.println("Erreur: BMP280 non détecté!");
  } else {
    Serial.println("BMP280 prêt.");
  }
}

void GetDataBmp280(void) {
  temp = bmp.readTemperature();
  pressure = bmp.readPressure();
  altitude = bmp.readAltitude(1021.5);
  Bmp280_Temp = temp;
  Bmp280_Press = pressure;
  Bmp280_Alt = altitude;
}
