//-----------------------------------------------------------------------------
// File: Sensors_MPU9250.cpp
//
// MPU9250 sensor board support implementation.
//
// Copyright(C) by Alexander Eltsyn (ae@aeinc.ru, RCGroup user 'AE_'
//
// This code is based on MPU9250 library by Brian R Taylor
// Copyright (c) 2017 Bolder Flight Systems
// https://github.com/bolderflight/MPU9250 
// 
//-----------------------------------------------------------------------------
#include "config.h"

// Use this code if SENSOR_MPU9250 defined only
#ifdef SENSOR_MPU9250

#include "Arduino.h"
#include "functions.h"
#include "MPU9250.h"

/*
  Below is the definition of MPU9250 sensor board orientation in headtracker.
  Use "MPU9250.png" for reference to sensor board I use and 
  "MPU9250_Orientation.png" for coordinate system definition.
  
  Each axis is described with 3 values vector:
   - Original axis index as it is drawn on MPU9250 board: 0 for X, 1 for Y and 2 for Z.
   - Accelerometer axis inversion, either 1 or -1
   - Gyro axis inversion, either 1 or -1
*/

// Axis definition:  { <AxisIndex>, <AccelerometerSign>, <GyroSign> }
// Original board orientation as drawn on MPU9250 board
const byte X[3] = {0,+1,+1};
const byte Y[3] = {1,+1,+1};
const byte Z[3] = {2,+1,+1};

// My orientation in FatShark
//const char X[3] = {1,-1,+1};
//const char Y[3] = {2,-1,-1};
//const char Z[3] = {0,+1,-1};

/*
Below are several examples of board orientation configurations. 
Please refer "MPU9250_Orientation.png" for coordinate system and 
guess what "Orientation XXX" means :)

 NOTE: Please calibrate magnetometer with headtracker GUI each time you 
 change orientation configuration. Magnetometer bias settings depends 
 on sensor orientation and compass will not work until you calibrate.


// 1. Original board orientation as drawn on MPU9250 board
const byte X[3] = {0,+1,+1};
const byte Y[3] = {1,+1,+1};
const byte Z[3] = {2,+1,+1};

// Orientation 2
const char X[3] = {1,-1,+1};
const char Y[3] = {0,+1,-1};
const char Z[3] = {2,+1,+1};

// Orientation 3
const char X[3] = {1,-1,+1};
const char Y[3] = {2,-1,-1};
const char Z[3] = {0,+1,-1};

// Orientation 4
const char X[3] = {2,-1,+1};
const char Y[3] = {1,+1,+1};
const char Z[3] = {0,+1,-1};

// Orientation 5
const char X[3] = {2,-1,+1};
const char Y[3] = {0,+1,-1};
const char Z[3] = {1,-1,-1};

// Orientation 6
const char X[3] = {0,-1,-1};
const char Y[3] = {2,-1,-1};
const char Z[3] = {1,-1,-1};
*/



#define SCALING_FACTOR  125      // Scaling factor - used when converting gyro "degree per second" to angle.
#define SCALING_GUI_ACC 100.0    // Used for compatibility with GUI calibration wizard
#define SCALING_GUI_MAG 10.0     // Used for compatibility with GUI calibration wizard

// Variables defined elsewhere
extern long channel_value[];

// If IMU hardware available
int I2CPresent = 1;

// Final angles for headtracker:
float tiltAngle = 90;       // Tilt angle
float tiltAngleLP = 90;     // Tilt angle with low pass FilterSensorData
float lastTiltAngle = 90;   // Used in low pass FilterSensorData.

float rollAngle = 0;        // Roll angle
float rollAngleLP = 90;     // Roll angle with low pass FilterSensorData
float lastRollAngle = 90;   // Used in low pass FilterSensorData

float panAngle = 90;        // Pan angle
float panAngleLP = 90;      // Pan angle with low pass FilterSensorData
float lastPanAngle = 90;    // Used in low pass FilterSensorData

// Start values - center position for head tracker
float tiltStart = 0;
float panStart = 0;
float rollStart = 0;

char TrackerStarted = 0;

// Servo reversing
char tiltInverse = -1;
char rollInverse = -1;
char panInverse = -1;

// Settings
float tiltRollBeta = 0.75;
float panBeta = 0.75;
float gyroWeightTiltRoll = 0.98;
float GyroWeightPan = 0.98;
int servoPanCenter = 2100;
int servoTiltCenter = 2100;
int servoRollCenter = 2100;
int panMaxPulse = 1150;
int panMinPulse = 1150;
int tiltMaxPulse = 1150;
int tiltMinPulse = 1150;
int rollMaxPulse = 1150;
int rollMinPulse = 1150;
float panFactor = 17;
float tiltFactor = 17;
float rollFactor = 17;
unsigned char servoReverseMask = 0;
int accOffset[3] = { 0, 0, 0 }; //  Not used !!!
float magOffset[3] = { 0, 0, 0 }; //
float gyroOff[3] = { 0, 0, 0 }; // Not Used
unsigned char htChannels[3] = { 8, 7, 6 }; // pan, tilt, roll
// End settings

// Local variables
char resetValues = 1;        // Used to reset headtracker/re-center. 

float accAngleX, accAngleY, accAngleZ;      // Measured angle from accelerometer
float heading, magAngleZ;      // Orientation based on data from magnetometer

// an MPU9250 object with the MPU-9250 sensor on I2C bus 0 with address 0x68
MPU9250 IMU(Wire, 0x68);

//--------------------------------------------------------------------------------------
// "Low-level" ;) functions to obtain sensor values
// All these functions take X,Y and Z signed axis indices defined above
//--------------------------------------------------------------------------------------
// Acceleration in G's. 
float Acc(char axis[3]) {
    if (axis[0] == 0) return -IMU.getAccelY_mss() / 9.8 * axis[1];
    if (axis[0] == 1) return -IMU.getAccelX_mss() / 9.8 * axis[1];
    return IMU.getAccelZ_mss() / 9.8 * (float)axis[1];
}

// Gyro, Degrees Per Second
float Gyro(char axis[3]) {
    if (axis[0] == 0) return IMU.getGyroY_rads() * 57.3 * axis[2];
    if (axis[0] == 1) return -IMU.getGyroX_rads() * 57.3 * axis[2];
    return  IMU.getGyroZ_rads() * 57.3 * axis[2];
}

// Magnetometer readings in uT's.
// offsetIndex is a calibration bias index and always 0 for X, 1 for Y and 2 for Z axis
float Mag(char axis[3], byte offsetIndex) {
    if (axis[0] == 0) return (IMU.getMagY_uT() * axis[1] - magOffset[offsetIndex]/SCALING_GUI_MAG);
    if (axis[0] == 1) return (IMU.getMagX_uT() * axis[1] - magOffset[offsetIndex]/SCALING_GUI_MAG);
    return (-IMU.getMagZ_uT() * axis[1] - magOffset[offsetIndex]/SCALING_GUI_MAG);
}

//--------------------------------------------------------------------------------------
// Aliases to use in formulas.
//--------------------------------------------------------------------------------------
#define AccX Acc(X)
#define AccY Acc(Y)
#define AccZ Acc(Z)

#define GyroX Gyro(X)
#define GyroY Gyro(Y)
#define GyroZ Gyro(Z)

#define MagX Mag(X,0)
#define MagY Mag(Y,2)
#define MagZ Mag(Z,1)

//--------------------------------------------------------------------------------------
// Check if MPU9250 sensors available and initialize I2CPresent variable
// This function is redundant as I2CPresent will be set every time 
// you call to InitSensors()
//--------------------------------------------------------------------------------------
void CheckI2CPresent() {
    if (IMU.begin() >= 0) {
        I2CPresent = 1;
    } else {
        I2CPresent = 0;
    }
}

//--------------------------------------------------------------------------------------
// GUI interaction support functions
// Output tracker values
//--------------------------------------------------------------------------------------
void trackerOutput() {
    Serial.print(tiltAngleLP - tiltStart + 90);
    Serial.print(",");
    Serial.print(rollAngleLP - rollStart + 90);
    Serial.print(",");
    Serial.println(panAngleLP + 180);
}

//--------------------------------------------------------------------------------------
// Output magnetometer raw values for GUI calibration wizard
//--------------------------------------------------------------------------------------
void calMagOutput() {
    Serial.print((int)(MagX * SCALING_GUI_MAG + 3000));
    Serial.print(",");
    Serial.print((int)(MagZ * SCALING_GUI_MAG + 3000));
    Serial.print(",");
    Serial.println((int)(MagY * SCALING_GUI_MAG + 3000));
}

//--------------------------------------------------------------------------------------
// Output accelerator values for GUI calibration wizard
//--------------------------------------------------------------------------------------
void calAccOutput() {
    Serial.print((long)(AccX * SCALING_GUI_ACC + 3000));
    Serial.print(",");
    Serial.print((long)(AccY * SCALING_GUI_ACC + 3000));
    Serial.print(",");
    Serial.println((long)(AccZ * SCALING_GUI_ACC + 3000));
}

//--------------------------------------------------------------------------------------
// Output magnetometer and accelerator raw values for GUI calibration wizard
//--------------------------------------------------------------------------------------
void calMagAccOutput() {
    Serial.print((int)(MagX * SCALING_GUI_MAG + 3000));
    Serial.print(",");
    Serial.print((int)(MagZ * SCALING_GUI_MAG + 3000));
    Serial.print(",");
    Serial.print((int)(MagY * SCALING_GUI_MAG + 3000));
    Serial.print(",");
    Serial.print((long)(AccX * SCALING_GUI_ACC + 3000));
    Serial.print(",");
    Serial.print((long)(AccY * SCALING_GUI_ACC + 3000));
    Serial.print(",");
    Serial.println((long)(AccZ * SCALING_GUI_ACC + 3000));
}
//--------------------------------------------------------------------------------------
// Issue $DBGS and $DBGE commands to start call this function every SERIAL_OUTPUT_FRAME_INTERVAL 
//--------------------------------------------------------------------------------------
void dbgOutput() {
    Serial.print("ACC:\t"); Serial.print(AccX); Serial.print("\t"); Serial.print(AccY); Serial.print("\t"); Serial.print(AccZ);  Serial.print("\t"); 
//    Serial.print("AccAngle:\t"); Serial.print((int)accAngleX); Serial.print("\t"); Serial.print((int)accAngleY); Serial.print("\t"); Serial.print((int)accAngleZ); Serial.print("\t"); 
    Serial.print("GYRO:\t"); Serial.print((int)GyroX); Serial.print("\t"); Serial.print((int)GyroY); Serial.print("\t"); Serial.print((int)GyroZ);Serial.print("\t");
    Serial.print("Mag:\t"); Serial.print((int)MagX); Serial.print("\t"); Serial.print((int)MagY); Serial.print("\t"); Serial.print((int)MagZ); Serial.print("\t");
    Serial.print("Head:\t"); Serial.print((int)heading); Serial.print("\t");
    Serial.print("Tilt:\t"); Serial.print((int)(tiltAngle-90)); Serial.print("\tRoll:\t"); Serial.print((int)(rollAngle-90)); Serial.print("\t");
//    Serial.print("mx/my/magAngleZ:\t"); Serial.print(mx); Serial.print("\t"); Serial.print(my);Serial.print("\t"); Serial.print(magAngleZ); Serial.print("\t");
    Serial.println();
}
//--------------------------------------------------------------------------------------
// Retrieves the sensor data from MPU9250 library
//--------------------------------------------------------------------------------------
void UpdateSensors() {
    if (!I2CPresent) return;
    IMU.readSensor();
}

//--------------------------------------------------------------------------------------
// Skip setting gyro offset. Both Gyro & Accelerator already calibrated in MPU9250 library
//--------------------------------------------------------------------------------------
void SetGyroOffset() {
    if (!I2CPresent) return;
}

//--------------------------------------------------------------------------------------
// Skip mangetometer calibration - use GUI to configure MagOffsets
//--------------------------------------------------------------------------------------
void CalibrateMag() {
    if (!I2CPresent) return;
}

//--------------------------------------------------------------------------------------
// Skip any calculations, just use GyroX, GyroY and GyroZ
//--------------------------------------------------------------------------------------
void GyroCalc() {
//      angleRaw[0]+=GyroX;
//      angleRaw[1]+=GyroY;
//      angleRaw[2]+=GyroZ;
//    Serial.println(angleRaw[0]/SCALING_FACTOR);
}
//--------------------------------------------------------------------------------------
// Calculate angle from accelerometer data
//--------------------------------------------------------------------------------------
void AccelCalc() {
    // So, lets calculate R
    // R^2 = Rx^2+Ry^2+Rz^2    
    float ax = AccX; float ay = AccY; float az = AccZ;
    float R = sqrt(ax*ax + ay*ay + az*az);
    // Calculate final angles:
    if ( (R > 0.7) && (R < 1.3) && (ax<R) && (ay<R) && (az<R) ) { 
        accAngleX = acos(ax / R) * 57.3;
        accAngleY = acos(ay / R) * 57.3;
        accAngleZ = acos(az / R) * 57.3;
    }
}

//--------------------------------------------------------------------------------------
// Calculates angle from magnetometer data.
//--------------------------------------------------------------------------------------
void MagCalc() {
    float tilt = (tiltAngle - 90) / 57.3;
    float roll = (rollAngle - 90) / 57.3;

// Backup - best!!!
//    float mx = MagX*cos(tilt) - MagZ*sin(tilt);
//    float my = MagY*cos(roll) - MagX*sin(roll)*sin(tilt) - MagZ*sin(roll)*cos(tilt);
    
    float mx = MagX*cos(tilt) - MagZ*sin(tilt);
    float my = MagY*cos(roll) - MagX*sin(roll)*sin(tilt) - MagZ*sin(roll)*cos(tilt);

    // Calculate pan-angle from magnetometer
    heading = (atan2(my, mx) * 57.3);
    float a = heading - panStart;
    if (a > 180) a-=360; else if (a < -180) a += 360;
    magAngleZ = a;
}

//--------------------------------------------------------------------------------------
// Filters / merges sensor data. 
//--------------------------------------------------------------------------------------
void FilterSensorData() {
    int temp = 0;

    // Used to set initial values. 
    if (resetValues == 1)
    {
#if FATSHARK_HT_MODULE
        digitalWrite(BUZZER, HIGH);
#endif
        resetValues = 0; 
      
        tiltStart = 0;
        panStart = 0;
        rollStart = 0;
  
        UpdateSensors();    
        GyroCalc();
        AccelCalc();
        MagCalc();
        
        panAngle = 0;
        tiltStart = accAngleX;
        panStart = magAngleZ;
        rollStart = accAngleY;

#if FATSHARK_HT_MODULE
        digitalWrite(BUZZER, LOW);
#endif
    }

    // Simple FilterSensorData, uses mainly gyro-data, but uses accelerometer to compensate for pan drift
    rollAngle = (rollAngle + ((GyroX) * cos((tiltAngle - 90) / 57.3) + (GyroZ) * sin((tiltAngle - 90) / 57.3)) / SCALING_FACTOR) * gyroWeightTiltRoll + accAngleY * (1 - gyroWeightTiltRoll);
    tiltAngle = (tiltAngle + ((GyroY) * cos((rollAngle - 90) / 57.3) + (GyroZ) * sin((rollAngle - 90) / 57.3) * -1) / SCALING_FACTOR) * gyroWeightTiltRoll + accAngleX * (1 - gyroWeightTiltRoll);
    panAngle  = (panAngle + ((GyroZ) * cos((tiltAngle - 90) / 57.3) + (((GyroX) * -1) * (sin((tiltAngle - 90) / 57.3)) ) + ( ((GyroY) * 1) * (sin((rollAngle - 90) / 57.3)))) / SCALING_FACTOR) * GyroWeightPan + magAngleZ * (1 - GyroWeightPan);

    if (TrackerStarted) {
        // All low-pass filters
        tiltAngleLP = tiltAngle * tiltRollBeta + (1 - tiltRollBeta) * lastTiltAngle;
        lastTiltAngle = tiltAngleLP;
  
        rollAngleLP = rollAngle * tiltRollBeta + (1 - tiltRollBeta) * lastRollAngle;
        lastRollAngle = rollAngleLP;

        panAngleLP = panAngle * panBeta + (1 - panBeta) * lastPanAngle;
        lastPanAngle = panAngleLP;

        float panAngleTemp = panAngleLP * panInverse * panFactor;
        if ( (panAngleTemp > -panMinPulse) && (panAngleTemp < panMaxPulse) )
        {
            temp = servoPanCenter + panAngleTemp;
            channel_value[htChannels[0]] = (int)temp;
        }    

        float tiltAngleTemp = (tiltAngleLP - tiltStart) * tiltInverse * tiltFactor;
        if ( (tiltAngleTemp > -tiltMinPulse) && (tiltAngleTemp < tiltMaxPulse) )
        {
            temp = servoTiltCenter + tiltAngleTemp;
            channel_value[htChannels[1]] = temp;
        }   

        float rollAngleTemp = (rollAngleLP - rollStart) * rollInverse * rollFactor;
        if ( (rollAngleTemp > -rollMinPulse) && (rollAngleTemp < rollMaxPulse) )
        {
            temp = servoRollCenter + rollAngleTemp;
            channel_value[htChannels[2]] = temp;
        }
    }
}

//--------------------------------------------------------------------------------------
// Expected to print the mag internal sensor data as a part of DebugOuput call in
// main file. But nothing excep MagOffset is used here for now and it is already 
// printed by DebugOutput
//--------------------------------------------------------------------------------------
void SensorInfoPrint() {
}
//--------------------------------------------------------------------------------------
// Utility for resetting tracker center. This is only called during tracker
// startup. Button press resets are handled during filtering. (Needs refactor)
//--------------------------------------------------------------------------------------
void ResetCenter() {
    resetValues = 0;

    // Not sure what Dennis is doing here. Giving it
    // time to stabilize, since this is called at setup time?
    for (unsigned char k = 0; k < 250; k++) {
        UpdateSensors();
        GyroCalc();
        AccelCalc();
        MagCalc();
        FilterSensorData();
    }

    tiltStart = accAngleX;
    panStart = magAngleZ;
    rollStart = accAngleY;

    UpdateSensors();
    GyroCalc();
    AccelCalc();
    MagCalc();
    FilterSensorData();

    panAngle = magAngleZ;
    tiltAngle = accAngleX;
    rollAngle = accAngleY;

    TrackerStarted = 1;
}
//--------------------------------------------------------------------------------------
// Initializes the sensor board sensors.
//--------------------------------------------------------------------------------------
void InitSensors() {
    if (!I2CPresent) return;
    Serial.print("Initializing...");

    // start communication with IMU 
    int status = IMU.begin();
    if (status < 0) {
        I2CPresent = 0;
        return;
    }
    IMU.calibrateAccel();
    // setting the accelerometer full scale range to +/-16G 
    IMU.setAccelRange(MPU9250::ACCEL_RANGE_16G);
    // setting the gyroscope full scale range to +/-500 deg/s
    IMU.setGyroRange(MPU9250::GYRO_RANGE_500DPS);
    // setting Digital low pass filter bandwidth
    IMU.setDlpfBandwidth(MPU9250::DLPF_BANDWIDTH_5HZ);
    // setting Sample rate divider to 19 for a 50 Hz update rate
    IMU.setSrd( 19 );

#if (ALWAYS_CAL_GYRO)
    SetGyroOffset();
#endif
    Serial.println("Ok");
}

#endif
