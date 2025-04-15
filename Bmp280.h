#ifndef Bmp280_H    
#define Bmp280_H   
#include <Adafruit_BMP280.h>
#include "fonctions.h"

extern float temp, humidity, pressure;
extern float Bmp280_Temp,Bmp280_Press,Bmp280_Alt;
void initBmp280(void);
void GetDataBmp280(void);

#endif 