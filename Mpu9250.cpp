#include "Mpu9250.h"
MPU9250_asukiaaa mySensor;
float gX = 0, gY = 0, gZ = 0;
float aX = 0, aY = 0, aZ = 0;

void initMpu9250() {
  Serial.println("Init MPU9250");
  mySensor.setWire(&Wire);
  mySensor.beginAccel();
  mySensor.beginGyro();

  bool accelOK = !isnan(mySensor.accelX());
  bool gyroOK  = !isnan(mySensor.gyroX());

  if (accelOK && gyroOK) {
    Serial.println("MPU9250 prêt.");
  } else {
    Serial.println("Erreur init MPU9250:");
    if (!accelOK) Serial.println(" - Accéléro");
    if (!gyroOK)  Serial.println(" - Gyro");
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