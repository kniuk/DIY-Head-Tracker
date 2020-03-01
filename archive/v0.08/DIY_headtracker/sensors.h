
#ifndef sensors_h
#define sensors_h
#include "Arduino.h"

void init_sensors();
void WriteToI2C(int device, byte address, byte val);
void ReadFromI2C(int device, byte address, char bytesToRead);
void updateSensors();
void gyroCalc();
void accCalc();
void magCalc();


void testAccOutput();
void testGyroOutput();
void testMagOutput();
void plot_all_sensors();
void setSensorOffset();
void testPanOutput();
void headtrackerOutput();
void testRollOutput();
void testAllData();
void quickTest();
void calMagOutput();

void calAccOutput(); 
void calMag();
void filter();
void resetCenter();

void SensorInfoPrint();

#endif
