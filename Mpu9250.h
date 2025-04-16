#ifndef Mpu9250_H
#define Mpu9250_H
#include <MPU9250_asukiaaa.h>
#include "fonctions.h"

extern float gX, gY, gZ ;
extern float aX, aY, aZ;

void initMpu9250(void);
void GetDataMpu9250(void);
void updateAcceleration(void);

#endif