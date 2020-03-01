//-----------------------------------------------------------------------------
// File: Sensors.h
// Desc: Declares sensor-related functions for the project.
//-----------------------------------------------------------------------------
#ifndef sensors_h
#define sensors_h

#include "Arduino.h"

void CheckI2CPresent();
void InitSensors();

//#ifdef SENSOR_MPU9250
//void Read9250Settings();
//void Write9250Settings();
//#endif

void UpdateSensors();
void GyroCalc();
void AccelCalc();
void MagCalc();

void SetGyroOffset();
void testPanOutput();
void trackerOutput();
void calMagOutput();
void calAccOutput(); 
void calMagAccOutput(); // Output both mag and accel in one pass.
void dbgOutput(); 
void CalibrateMag();
void FilterSensorData();
void ResetCenter();
void SensorInfoPrint();

void testAllSensors();
void testRollOutput();
void testAllData();
void testAccOutput();
void testGyroOutput();
void testMagOutput();

#endif // sensors_h
