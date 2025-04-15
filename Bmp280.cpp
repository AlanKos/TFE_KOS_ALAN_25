
  #include "Bmp280.h"

  Adafruit_BMP280 bmp;
  float temp, humidity, pressure;
  float Bmp280_Temp,Bmp280_Press,Bmp280_Alt;
  float altitude(int32_t press, float seaLevel = 1013.25) {
    return 44330.0 * (1.0 - pow((press / 100.0) / seaLevel, 0.1903));
  }


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
    Bmp280_Temp = temp;
    Bmp280_Press = pressure;
    Bmp280_Alt = altitude(pressure);

  }

