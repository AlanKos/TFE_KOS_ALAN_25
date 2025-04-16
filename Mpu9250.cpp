#include "Mpu9250.h"
MPU9250_asukiaaa mySensor;
float gX = 0, gY = 0, gZ = 0;
float aX = 0, aY = 0, aZ = 0;
float mX = 0, mY = 0, mZ = 0, mDirection = 0;

void initMpu9250() {
  Serial.println("Init MPU9250");
  mySensor.setWire(&Wire);
  mySensor.beginAccel();
  mySensor.beginGyro();
  mySensor.beginMag();

  bool accelOK = !isnan(mySensor.accelX());
  bool gyroOK  = !isnan(mySensor.gyroX());
  bool magOK   = !isnan(mySensor.magX());

  if (accelOK && gyroOK && magOK) {
    Serial.println("MPU9250 prêt.");
  } else {
    Serial.println("Erreur init MPU9250:");
    if (!accelOK) Serial.println(" - Accéléro");
    if (!gyroOK)  Serial.println(" - Gyro");
    if (!magOK)   Serial.println(" - Magnéto");
  }
}

void GetDataMpu9250(void) {
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
  updateAcceleration();
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