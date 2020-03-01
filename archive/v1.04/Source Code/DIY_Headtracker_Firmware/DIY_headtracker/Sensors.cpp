//-----------------------------------------------------------------------------
// File: Sensors.cpp
// Desc: Implementations sensor board functionality.
//-----------------------------------------------------------------------------
#include "config.h"
#include "Arduino.h"
#include "functions.h"
#include <Wire.h>

/*
Reference for basic sensor/IMU understanding/calculation:
http://www.starlino.com/imu_guide.html
http://www.sparkfun.com/datasheets/Sensors/Magneto/Tilt%20Compensated%20Compass.pdf
https://www.loveelectronics.co.uk/Tutorials/13/tilt-compensated-compass-arduino-tutorial
http://www.pololu.com/file/download/LSM303DLH-compass-app-note.pdf?file_id=0J434
*/


// Gyro
//
#define ITG3205_ADDR 0x68    // The address of ITG3205
#define ITG3205_X_ADDR 0x1D  // Start address for x-axis
#define SCALING_FACTOR 13     // Scaling factor - used when converting to angle

// Accelerometer
//
#define ADXL345_ADDR (0x53)  // The adress of ADXL345 
#define ADXL345_X_ADDR (0x32)// Start address for x-axis
#define ACC_SENS 256         // Sensitivity. 13 bit adc, +/- 16 g. Calculated as: (2^13)/(16*2)
#define ASSUME_1G_ACC 0      // Assuming the total gravitation is 1. True if only earth gravitation has influence.  


// Magnetometer
//
#define HMC_ADDR 0x1E        // The address of HMC5883
#define HMC_X_ADDR (0x03)    // Start address for x-axis. 

#define SAMPLERATE 128       // Samplerate of sensors (in hz, samples per second)

unsigned char ADXL345_ID = 0;
unsigned char ITG3205_ID = 0;
unsigned char HMC_ID = 0;

// Variables defined elsewhere
//
extern long channel_value[];

// Local variables
//
byte sensorBuffer[10];       // Buffer for bytes read from sensors
char resetValues = 1;        // Used to reset headtracker/re-center. 

long accRaw[3];              // Raw readings from accelerometer
float accG[3];               // G-force in each direction
float accAngle[3];           // Measured angle from accelerometer
float R;                     // Unit vector - total G.

float gyroRaw[3];            // Raw readings from gyro
float angle[3];              // Angle from gyro 
float angleRaw[3];           // Temp for angle-calculation

float magRaw[3];             // Raw readings from magnetometer
float magAngle[3];           // Measured angles from magnetometer
float mx = 0;                // Calculated magnetometer value in x-direction with pan/tilt compensation
float my = 0;                // Calculated magnetometer value in y-direction with pan/tilt compensation

int magPosOff[3];
int magNegOff[3];
float magGain[3];

#define MAG0MAX 625
#define MAG1MAX 625
#define MAG2MAX 625
#define MAG0MIN -625
#define MAG1MIN -625
#define MAG2MIN -625


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
//
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
int accOffset[3] = {0, 0, 0}; 
float magOffset[3] = {(MAG0MAX + MAG0MIN) / 2, (MAG1MAX + MAG1MIN) / 2, (MAG2MAX + MAG2MIN) / 2};
float gyroOff[3] = {0, 0, 0};
unsigned char htChannels[3] = {8, 7, 6}; // pan, tilt, roll
//
// End settings


// Function used to write to I2C:
void WriteToI2C(int device, byte address, byte val)
{
    Wire.beginTransmission(device);
    Wire.write(address);
    Wire.write(val);
    Wire.endTransmission();
}

// Function to read from I2C
void ReadFromI2C(int device, char address, char bytesToRead)
{
    Wire.beginTransmission(device);
    Wire.write(address);
    Wire.endTransmission();
  
    Wire.beginTransmission(device);
    Wire.requestFrom(device, bytesToRead);
   
    char i = 0;   
    while ( Wire.available() )
    {
        sensorBuffer[i++] = Wire.read();
    }   
    Wire.endTransmission();
}

void trackerOutput()
{
  Serial.print(tiltAngleLP - tiltStart + 90);
  Serial.print(",");
  Serial.print(rollAngleLP - rollStart + 90);
  Serial.print(",");  
  Serial.println(panAngleLP + 180);
}

void calMagOutput()
{
    Serial.print((int)magRaw[0] + 3000);
    Serial.print(",");
    Serial.print((int)magRaw[1] + 3000);
    Serial.print(",");    
    Serial.println((int)magRaw[2] + 3000);   
}

void calAccOutput()
{
    Serial.print((int)accRaw[0] + 3000);  
    Serial.print(",");          
    Serial.print((int)accRaw[1] + 3000);  
    Serial.print(",");              
    Serial.println((int)accRaw[2] + 3000);  
}

void calMagAccOutput()
{
    Serial.print((int)magRaw[0] + 3000);
    Serial.print(",");
    Serial.print((int)magRaw[1] + 3000);
    Serial.print(",");    
    Serial.print((int)magRaw[2] + 3000);
    Serial.print(","); 
    Serial.print((int)accRaw[0] + 3000);  
    Serial.print(",");          
    Serial.print((int)accRaw[1] + 3000);  
    Serial.print(",");              
    Serial.println((int)accRaw[2] + 3000); 
}

//--------------------------------------------------------------------------------------
// Func: UpdateSensors
// Desc: Retrieves the sensor data from the sensor board via I2C.
//--------------------------------------------------------------------------------------
void UpdateSensors()
{

    // Read x, y, z acceleration, pack the data.
    ReadFromI2C(ADXL345_ADDR, ADXL345_X_ADDR, 6);
    accRaw[0] = ((int)sensorBuffer[0] | ((int)sensorBuffer[1] << 8)) * -1;
    accRaw[1] = ((int)sensorBuffer[2] | ((int)sensorBuffer[3] << 8)) * -1;       
    accRaw[2] = (int)sensorBuffer[4] | ((int)sensorBuffer[5] << 8);       
   
   
    // Read x, y, z from gyro, pack the data
    ReadFromI2C(ITG3205_ADDR, ITG3205_X_ADDR, 6);
    gyroRaw[0] = (int)sensorBuffer[1] | ((int)sensorBuffer[0] << 8);
    gyroRaw[1] = ( (int)sensorBuffer[3] | ((int)sensorBuffer[2] << 8) ) * -1;
    gyroRaw[2] = ( (int)sensorBuffer[5] | ((int)sensorBuffer[4] << 8) ) * -1;
   
   
    // Read x, y, z from magnetometer;
    ReadFromI2C(HMC_ADDR, HMC_X_ADDR, 6);
    for (unsigned char i =0; i < 3; i++)
    {
       magRaw[i] = (int)sensorBuffer[(i * 2) + 1] | ((int)sensorBuffer[i * 2] << 8);
    }    
}

//--------------------------------------------------------------------------------------
// Func: SetGyroOffset
// Desc: Sets the gyro offset.
//--------------------------------------------------------------------------------------
void SetGyroOffset()
{
    // Not sure what the outer loops are for, Dennis. Stabilization time?
    //
    for (unsigned int i = 0; i < 100; i++)
    {
        UpdateSensors();
        for (unsigned char k = 0; k < 3; k++)
        {
            gyroOff[k] += gyroRaw[k];
        }
    }
 
    for (unsigned char k = 0; k < 3; k++)
    {
        gyroOff[k] = gyroOff[k] / 100;
    }
     
#if (DEBUG)     
    Serial.print("Gyro offset measured:");
    Serial.print(gyroOff[0]);
    Serial.print(",");   
    Serial.print(gyroOff[1]);
    Serial.print(",");      
    Serial.println(gyroOff[2]);    
#endif 
}

//--------------------------------------------------------------------------------------
// Func: CalibrateMag
// Desc: 
//--------------------------------------------------------------------------------------
void CalibrateMag()
{  
    WriteToI2C(HMC_ADDR, 0x00, 0b00010001);

    // MM: Again with the loops. Not sure what purpose this serves, Dennis.
    for (unsigned char i = 0; i < 40; i++)
    {
        UpdateSensors(); 
    }
    magPosOff[0] = magRaw[0];
    magPosOff[1] = magRaw[1];
    magPosOff[2] = magRaw[2];  
  
  
    WriteToI2C(HMC_ADDR, 0x00, 0b00010010);

    for (unsigned char i = 0; i < 40; i++)
    {
        UpdateSensors(); 
    }
    magNegOff[0] = magRaw[0];
    magNegOff[1] = magRaw[1];
    magNegOff[2] = magRaw[2];  
    
    WriteToI2C(HMC_ADDR, 0x00, 0b00010000);

    magGain[0] = -2500 / float(magNegOff[0] - magPosOff[0]);
    magGain[1] = -2500 / float(magNegOff[1] - magPosOff[1]);
    magGain[2] = -2500 / float(magNegOff[2] - magPosOff[2]); 
  
    for (unsigned char i = 0; i < 40; i++)
    {
        UpdateSensors(); 
    }  
  
#if (DEBUG)
    Serial.print("Mag cal:");
    Serial.print(magNegOff[0] - magPosOff[0]);
    Serial.print(",");   
    Serial.print(magNegOff[1] - magPosOff[1]);
    Serial.print(",");      
    Serial.print(magNegOff[2] - magPosOff[2]);
   
    Serial.print(",");      
    Serial.print(magGain[0]);
    Serial.print(",");   
    Serial.print(magGain[1]);
    Serial.print(",");      
    Serial.println(magGain[2]);   
   
   
    Serial.print("Mag offset:");
    Serial.print(magOffset[0]);
    Serial.print(",");   
    Serial.print(magOffset[1]);
    Serial.print(",");      
    Serial.println(magOffset[2]);    
#endif          
}


//--------------------------------------------------------------------------------------
// Func: GyroCalc
// Desc: Calculate angle from gyro-data
//--------------------------------------------------------------------------------------
void GyroCalc()
{    
#if (DEBUG)
    for (unsigned char i=0; i<3; i++)
    {
        angleRaw[i]+=((gyroRaw[i]-gyroOff[i]));
        angle[i] = angleRaw[i]/(SAMPLERATE*SCALING_FACTOR);
    }
#endif          
}
   
//--------------------------------------------------------------------------------------
// Func: AccelCalc
// Desc: Calculate angle from accelerometer data
//--------------------------------------------------------------------------------------
void AccelCalc()
{
    accRaw[0] += accOffset[0];
    accRaw[1] += accOffset[1];
    accRaw[2] += accOffset[2];   
  
    for (unsigned char i = 0; i<3; i++)
    {
        accG[i] = (float)accRaw[i] / ACC_SENS;
    }
     
    // So, lets calculate R
    // R^2 = Rx^2+Ry^2+Rz^2    
    #if (ASSUME_1G_ACC == 0) 
        R = sqrt((accG[0] * accG[0]) + (accG[1] * accG[1]) + (accG[2] * accG[2]));
    #else // Otherwise, just assume total G = 1.
        R = 1;
    #endif
      
    // Calculate final angles:
    if (R < 1.3 && R > 0.7)
    { 
        for (unsigned char i = 0; i<3; i++)
        {
            accAngle[i] = acos(accG[i] / R) * 57.3;
        }  
    }
}

//--------------------------------------------------------------------------------------
// Func: MagCalc
// Desc: Calculates angle from magnetometer data.
//--------------------------------------------------------------------------------------
void MagCalc()
{
    // Invert 2 axis  
    magRaw[1] *= -1;
    magRaw[2] *= -1;
    
    // Set gain:
    magRaw[0] *= magGain[0];
    magRaw[1] *= magGain[1];
    magRaw[2] *= magGain[2];    
    
    magRaw[0] -= magOffset[0];
    magRaw[1] -= magOffset[1];
    magRaw[2] -= magOffset[2];    
  
    float testAngle = tiltAngle - 90;
    mx = magRaw[0] * cos((testAngle) / 57.3)
        + magRaw[1] * sin(testAngle / 57.3);

    my = magRaw[0] * sin((rollAngle - 90) / 57.3)
        * sin((tiltAngle - 90) / 57.3)
        + magRaw[2] * cos((rollAngle - 90) / 57.3)
        - magRaw[1] * sin((rollAngle - 90) / 57.3)
        * cos((tiltAngle - 90) / 57.3);
      
    // Calculate pan-angle from magnetometer. 
    magAngle[2] = (atan(mx / my) * 57.3 + 90);

    // Get full 0-360 degrees. 
    if (my < 0)
    {
        magAngle[2] += 180;
    }
    
    float tempAngle = panStart - magAngle[2];
      
    if (tempAngle > 180)
    {
        tempAngle -= 360; 
    }  
    else if (tempAngle < -180)
    {
        tempAngle += 360; 
    }
      
    magAngle[2] = tempAngle * -1;
}


//--------------------------------------------------------------------------------------
// Func: Filter
// Desc: Filters / merges sensor data. 
//--------------------------------------------------------------------------------------
void FilterSensorData()
{
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
        tiltStart = accAngle[0];
        panStart = magAngle[2];
        rollStart = accAngle[1];

#if FATSHARK_HT_MODULE
        digitalWrite(BUZZER, LOW);
#endif
    }

    // Simple FilterSensorData, uses mainly gyro-data, but uses accelerometer to compensate for drift
    rollAngle = (rollAngle + ((gyroRaw[0] - gyroOff[0]) * cos((tiltAngle - 90) / 57.3) + (gyroRaw[2] - gyroOff[2]) * sin((tiltAngle - 90) / 57.3)) / (SAMPLERATE * SCALING_FACTOR)) * gyroWeightTiltRoll + accAngle[1] * (1 - gyroWeightTiltRoll);
    tiltAngle = (tiltAngle + ((gyroRaw[1] - gyroOff[1]) * cos((rollAngle - 90) / 57.3) + (gyroRaw[2] - gyroOff[2]) * sin((rollAngle - 90) / 57.3) * -1) / (SAMPLERATE * SCALING_FACTOR)) * gyroWeightTiltRoll + accAngle[0] * (1 - gyroWeightTiltRoll);
    panAngle  = (panAngle + ((gyroRaw[2] - gyroOff[2]) * cos((tiltAngle - 90) / 57.3) + (((gyroRaw[0] - gyroOff[0]) * -1) * (sin((tiltAngle - 90) / 57.3)) ) + ( ((gyroRaw[1] - gyroOff[1]) * 1) * (sin((rollAngle - 90) / 57.3)))) / (SAMPLERATE * SCALING_FACTOR)) * GyroWeightPan + magAngle[2] * (1 - GyroWeightPan);

    if (TrackerStarted)
    {
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
// Func: InitSensors
// Desc: Initializes the sensor board sensors.
//--------------------------------------------------------------------------------------
void InitSensors()
{
    ReadFromI2C(ITG3205_ADDR, 0x00, 1);
    ITG3205_ID = sensorBuffer[0];
 
#if (DEBUG)    
    Serial.print("ITG3205: ");
    Serial.print(sensorBuffer[0]);
#endif 
 
    ReadFromI2C(ADXL345_ADDR, 0x00, 1);
    ADXL345_ID = sensorBuffer[0];
 
#if (DEBUG)     
    Serial.print("    ADXL: ");
    Serial.print(sensorBuffer[0]); 
#endif  

    // Accelerometer increase G-range (+/- 16G)
    WriteToI2C(ADXL345_ADDR, 0x31, 0b00001011);        
    ReadFromI2C(HMC_ADDR, 0x00, 1);
    HMC_ID = sensorBuffer[0];
 
#if (DEBUG)     
    Serial.print("    HMC: ");
    Serial.println(sensorBuffer[0]); 
#endif  

    WriteToI2C(ITG3205_ADDR, 22, 24);

    //  ADXL345 POWER_CTL
    WriteToI2C(ADXL345_ADDR, 0x2D, 0); 
    WriteToI2C(ADXL345_ADDR, 0x2D, 16);
    WriteToI2C(ADXL345_ADDR, 0x2D, 8);

    // HMC5883
    // Run in continuous mode
    WriteToI2C(HMC_ADDR, 0x02, 0x00);    
 
#if (ALWAYS_CAL_GYRO)
    // Set sensor offset
    SetGyroOffset();
#endif 
}

//--------------------------------------------------------------------------------------
// Func: ResetCenter
// Desc: Utility for resetting tracker center. This is only called during tracker
//       startup. Button press resets are handled during filtering. (Needs refactor)
//--------------------------------------------------------------------------------------
void ResetCenter()
{
    resetValues = 0; 
    
    // Not sure what Dennis is doing here. Giving it
    // time to stabilize, since this is called at setup time?
    for (unsigned char k = 0; k < 250; k++)
    {
        UpdateSensors();    
        GyroCalc();
        AccelCalc();
        MagCalc();
        FilterSensorData();    
    }
    
    tiltStart = accAngle[0];
    panStart = magAngle[2];
    rollStart = accAngle[1];  
  
    UpdateSensors();    
    GyroCalc();
    AccelCalc();
    MagCalc();
    FilterSensorData();    
  
    panAngle = magAngle[2];
    tiltAngle = accAngle[0];
    rollAngle = accAngle[1];
    
    TrackerStarted = 1;
}

//--------------------------------------------------------------------------------------
// Func: SensorInfoPrint
// Desc: Prints the mag sensor data.
//--------------------------------------------------------------------------------------
void SensorInfoPrint()
{ 
   Serial.print("Mag cal:");
   Serial.print(magNegOff[0] - magPosOff[0]);
   Serial.print(",");   
   Serial.print(magNegOff[1] - magPosOff[1]);
   Serial.print(",");      
   Serial.print(magNegOff[2] - magPosOff[2]);
   
   Serial.print(",");      
   Serial.print(magGain[0]);
   Serial.print(",");   
   Serial.print(magGain[1]);
   Serial.print(",");      
   Serial.println(magGain[2]);   

   Serial.print("ADXL345 ID: ");
   Serial.println((int)ADXL345_ID); 
   Serial.print("ITG3205 ID: ");
   Serial.println((int)ITG3205_ID); 
   Serial.print("HMC ID: ");
   Serial.println((int)HMC_ID);   
}


// ===============================================
//      ---------- Test functions -----------
// ===============================================
/*
void testAccOutput()
{
    Serial.print("RAW: ");  
    Serial.print(accRaw[0]);  
    Serial.print(" ");          
    Serial.print(accRaw[1]);  
    Serial.print(" ");              
    Serial.print(accRaw[2]);  

    Serial.print("\t G: ");        
    Serial.print(accG[0]); 
    Serial.print(" ");    
    Serial.print(accG[1]); 
    Serial.print(" "); 
    Serial.print(accG[2]); 

    Serial.print("\t Ang: ");        
    Serial.print(accAngle[0]); 
    Serial.print(" ");    
    Serial.print(accAngle[1]); 
    Serial.print(" "); 
    Serial.println(accAngle[2]);
}

void testGyroOutput()
{  
    Serial.print("RAW: ");  
    Serial.print(gyroRaw[0]);  
    Serial.print(",");          
    Serial.print(gyroRaw[1]);  
    Serial.print(",");              
    Serial.print(gyroRaw[2]);   

    Serial.print(",");        
    Serial.print(angle[0]);  
    Serial.print(",");          
    Serial.print(angle[1]);  
    Serial.print(",");              
    Serial.println(angle[2]);
}

void testMagOutput()
{
    Serial.print(magRaw[0]);
    Serial.print(",");
    Serial.print(magRaw[1]);
    Serial.print(",");    
    Serial.print(magRaw[2]);    

    Serial.print(",");              
    Serial.print(magAngle[0]);  
    Serial.print(",");          
    Serial.print(magAngle[1]);  
    Serial.print(",");              
    Serial.println(magAngle[2]);      
}

void testTiltOutput()
{ 
    Serial.print(angle[1]);
    Serial.print(",");          
    Serial.print(accAngle[0]-tiltStart);
    Serial.print(",");          
    Serial.println(tiltAngle-tiltStart);
}

void testRollOutput()
{
    Serial.print(angle[0]);
    Serial.print(",");          
    Serial.print(accAngle[1]-rollStart);
    Serial.print(",");          
    Serial.println(rollAngle-rollStart);  
}

void testPanOutput()
{
    Serial.print(angle[2]);
    Serial.print(",");                  
    Serial.print(magAngle[2]);
    Serial.print(",");                  
    Serial.println(panAngle);
}

// output calculated values, output as "csv"
void testAllData()
{  
    // x
  Serial.print(angle[1]);
  Serial.print(",");          
  Serial.print(accAngle[0]-90);
  Serial.print(",");          
  Serial.print(tiltAngle-90);
  Serial.print(",");      
  
    // y
  Serial.print(angle[0]);
  Serial.print(",");          
  Serial.print(accAngle[1]-90);
  Serial.print(",");          
  Serial.print(rollAngle-90);  
  Serial.print(",");     
    
    // z
  Serial.print(angle[2]);
  Serial.print(",");                  
  Serial.print(magAngle[2]-panStart);
  Serial.print(",");                  
  Serial.println(panAngle);
}

// All sensor output as "csv". 
void testAllSensors()
{  
    Serial.print(accRaw[0]);  
    Serial.print(",");          
    Serial.print(accRaw[1]);  
    Serial.print(",");              
    Serial.print(accRaw[2]);  

    Serial.print(",");            
    Serial.print(gyroRaw[0]);  
    Serial.print(",");          
    Serial.print(gyroRaw[1]);  
    Serial.print(",");              
    Serial.print(gyroRaw[2]);  

    Serial.print(",");               
    Serial.print(magRaw[0]);  
    Serial.print(",");          
    Serial.print(magRaw[1]);  
    Serial.print(",");              
    Serial.println(magRaw[2]);      
}
*/
