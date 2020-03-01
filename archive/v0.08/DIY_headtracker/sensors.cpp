#include "config.h"
#include "Arduino.h"
#include "functions.h"
#include <Wire.h>


/* Serial chart config

[_setup_]
port=COM4
baudrate=115200

width=1200
height=301
background_color = white

[_default_]
min = -10096
max = 10096

[xAcc]
color=red
min = -400
max = 400

[yAcc]
color = blue
min = -400
max = 400

[zAcc]
color=green
min = -400
max = 400


*/


/*
Reference for basic sensor/IMU understanding/calculation:
http://www.starlino.com/imu_guide.html
http://www.sparkfun.com/datasheets/Sensors/Magneto/Tilt%20Compensated%20Compass.pdf
https://www.loveelectronics.co.uk/Tutorials/13/tilt-compensated-compass-arduino-tutorial
http://www.pololu.com/file/download/LSM303DLH-compass-app-note.pdf?file_id=0J434
*/

extern long channel_value[];


// Gyro
#define ITG3205_ADDR 0x68    // The address of ITG3205
#define ITG3205_X_ADDR 0x1D  // Start address for x-axis
//#define SCALING_FACTOR 14.375     // Scaling factor - used when converting to angle
#define SCALING_FACTOR 13     // Scaling factor - used when converting to angle

// Accelerometer address
#define ADXL345_ADDR (0x53)  // The adress of ADXL345 
#define ADXL345_X_ADDR (0x32)// Start address for x-axis
#define ACC_SENS 256         // Sensitivity. 13 bit adc, +/- 16 g. Calculated as: (2^13)/(16*2)


#define ASSUME_1G_ACC 0      // Assuming the total gravitation is 1. True if only earth gravitation has influence.  


//Magnetometer address
#define HMC_ADDR 0x1E        // The address of HMC5883
#define HMC_X_ADDR (0x03)    // Start address for x-axis. 


#define SAMPLERATE 128       // Samplerate of sensors (in hz, samples per second)

unsigned char ADXL345_ID =0;
unsigned char ITG3205_ID =0;
unsigned char HMC_ID = 0;

byte sensorBuffer[10];       // Buffer for bytes read from sensors
char resetValues = 1;        // Used to reset headtracker/re-center. 

long accRaw[3];              // Raw readings from accelerometer
float accG[3];               // G-force in each direction
float accAngle[3];           // Measured angle from accelerometer
float R;                     // Unit vector - total G.


float gyroRaw[3];            // Raw readings from gyro
float gyroOff[3];            // Gyro offset
float angle[3];              // Angle from gyro 
float angleRaw[3];           // Temp for angle-calculation

float magRaw[3];             // Raw readings from magnetometer
float Rmag;                  // Unit vector
float magAngle[3];           // Measured angles from magnetometer
float mx =0;                 // Calculated magnetometer value in x-direction with pan/tilt compensation
float my =0;                 // Calculated magnetometer value in y-direction with pan/tilt compensation

int magPosOff[3];
int magNegOff[3];
float magGain[3];

int accOffset[3] = {0,0,0}; 

//My calibration:
/*
float mag0Max = 730;
float mag1Max = 630;
float mag2Max = 1010;

float mag0Min = -540;
float mag1Min = -580;
float mag2Min = -250;
*/


float mag0Max = 625;
float mag1Max = 625;
float mag2Max = 625;

float mag0Min = -625;
float mag1Min = -625;
float mag2Min = -625;


float magOffset[3] = {(mag0Max+mag0Min)/2,(mag1Max+mag1Min)/2,(mag2Max+mag2Min)/2};


// Final angles for headtracker:
float tiltAngle=90;           // Tilt angle
float tiltAngleLP=90;         // Tilt angle with lowpass-filter
float lastTiltAngle =90;      // Used in lowpass-filter.

float rollAngle =0;          // Roll angle
float rollAngleLP=90;         // Roll angle with lowpass-filter
float lastRollAngle =90;      // Used in lowpass-filter

float panAngle = 90;              // Pan angle
float panAngleLP=90;          // Pan angle with lowpass-filter
float lastPanAngle =90;       // Used in lowpass-filter

// Start values - center position for headtracker
float tiltStart =0;
float panStart = 0;
float rollStart =0;

int temp =0; // Can't update array directly, variable for calculations. 

float tiltBeta = 0.75;
float panBeta = 0.75;

float gyroWeight = 0.98;
float GyroWeightPan = 0.98;

int maxPulse = 1150;
int servoPanCenter = 2100;
int servoTiltCenter = 2100;
int servoRollCenter = 2100;

int panMaxPulse = 1150;
int panMinPulse =1150;
int tiltMaxPulse = 1150;
int tiltMinPulse =1150;
int rollMaxPulse = 1150;
int rollMinPulse =1150;

float panFactor = 17;
float tiltFactor = 17;
float rollFactor = 17;

char tiltInverse = -1;
char rollInverse = -1;
char panInverse = -1;

char TrackerStarted = 0;

unsigned char htChannels[3]={8,7,6};

float quick_test = 0;

// Function used to write to I2C:
void WriteToI2C(int device, byte address, byte val) {
  Wire.beginTransmission(device);
  Wire.write(address);
  Wire.write(val);
  Wire.endTransmission();
}

// Function to read from I2C
void ReadFromI2C(int device, char address, char bytesToRead) {
   Wire.beginTransmission(device);
   Wire.write(address);
   Wire.endTransmission();
  
   Wire.beginTransmission(device);
   Wire.requestFrom(device, bytesToRead);
   
  char i =0;   
  while(Wire.available()) {
    sensorBuffer[i++]=Wire.read();
  }   
   Wire.endTransmission();
  
}


// ===============================================
//      ---------- Test functions -----------
// ===============================================
void testAccOutput() {

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

void testGyroOutput() {
  
//    Serial.print("RAW: ");  
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

void testMagOutput() {

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


void testTiltOutput() { 
  Serial.print(angle[1]);
  Serial.print(",");          
  Serial.print(accAngle[0]-tiltStart);
  Serial.print(",");          
  Serial.println(tiltAngle-tiltStart);
}

void testRollOutput() {
  Serial.print(angle[0]);
  Serial.print(",");          
  Serial.print(accAngle[1]-rollStart);
  Serial.print(",");          
  Serial.println(rollAngle-rollStart);  
}

void testPanOutput() {
  Serial.print(angle[2]);
  Serial.print(",");                  
  Serial.print(magAngle[2]);
  Serial.print(",");                  
  Serial.println(panAngle);
}

void headtrackerOutput() {
  Serial.print(tiltAngleLP-tiltStart+90);
  Serial.print(",");
  Serial.print(rollAngleLP-rollStart+90);
  Serial.print(",");  
  Serial.println(panAngleLP+180);
}

void calMagOutput() {
    Serial.print((int)magRaw[0]+3000);
    Serial.print(",");
    Serial.print((int)magRaw[1]+3000);
    Serial.print(",");    
    Serial.println((int)magRaw[2]+3000);   
}

void calAccOutput() {
    Serial.print((int)accRaw[0]+3000);  
    Serial.print(",");          
    Serial.print((int)accRaw[1]+3000);  
    Serial.print(",");              
    Serial.println((int)accRaw[2]+3000);  
}

// All sensor output as "csv". 
void plot_all_sensors() {
  
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

// output calculated values, output as "csv"
void testAllData() {
  
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

void quickTest() {

  Serial.println(quick_test);
  
}


// ===============================================
//      ---------- Sensor update -----------
// ===============================================
void updateSensors() {

    // Read x, y, z acceleration: 
    ReadFromI2C(ADXL345_ADDR, ADXL345_X_ADDR, 6);
    /*
    for (unsigned char i =0; i<3; i++) {
       accRaw[i] = (int)sensorBuffer[i*2] | ((int)sensorBuffer[(i*2)+1]<<8);
    }
    */
    accRaw[0] = ((int)sensorBuffer[0*2] | ((int)sensorBuffer[(0*2)+1]<<8))*(-1);
    accRaw[1] = ((int)sensorBuffer[1*2] | ((int)sensorBuffer[(1*2)+1]<<8))*(-1);       
    accRaw[2] = (int)sensorBuffer[2*2] | ((int)sensorBuffer[(2*2)+1]<<8);       
   
   
    // Read x, y, z from gyro:     
    ReadFromI2C(ITG3205_ADDR, ITG3205_X_ADDR, 6);
   
    /*
    for (unsigned char i =0; i<3; i++) {
       gyroRaw[i] = (int)sensorBuffer[(i*2)+1] | ((int)sensorBuffer[i*2]<<8);
    }
    */
    gyroRaw[0] =( (int)sensorBuffer[(0*2)+1] | ((int)sensorBuffer[0*2]<<8) ) *(1);
    gyroRaw[1] =( (int)sensorBuffer[(1*2)+1] | ((int)sensorBuffer[1*2]<<8) ) *(-1);
    gyroRaw[2] =( (int)sensorBuffer[(2*2)+1] | ((int)sensorBuffer[2*2]<<8) ) *(-1);
   
   
    // Read x, y, z from magnetometer;
    ReadFromI2C(HMC_ADDR, HMC_X_ADDR, 6);
    for (unsigned char i =0; i<3; i++) {
       magRaw[i] = (int)sensorBuffer[(i*2)+1] | ((int)sensorBuffer[i*2]<<8);
    }    
}

// ===============================================
//      --------- Set sensor offset ----------
// ===============================================
void setSensorOffset() {
  
 for (unsigned int i =0; i< 100; i++) {
        updateSensors();
        
     for (unsigned char k =0; k < 3; k++) {
        gyroOff[k]+=gyroRaw[k];
     }
 }
 
     for (unsigned char k =0; k < 3; k++) {
        gyroOff[k]=gyroOff[k]/100;
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


void calMag() {
  
   WriteToI2C(HMC_ADDR, 0x00, 0b00010001);

  for (unsigned char i = 0; i < 40; i++) {
     updateSensors(); 
  }
  magPosOff[0] = magRaw[0];
  magPosOff[1] = magRaw[1];
  magPosOff[2] = magRaw[2];  
  
  
   WriteToI2C(HMC_ADDR, 0x00, 0b00010010);

  for (unsigned char i = 0; i < 40; i++) {
     updateSensors(); 
  }
  magNegOff[0] = magRaw[0];
  magNegOff[1] = magRaw[1];
  magNegOff[2] = magRaw[2];  
    
   WriteToI2C(HMC_ADDR, 0x00, 0b00010000);

  magGain[0] = (-2500) / float(magNegOff[0]-magPosOff[0]);
  magGain[1] = (-2500) / float(magNegOff[1]-magPosOff[1]);
  magGain[2] = (-2500) / float(magNegOff[2]-magPosOff[2]); 
  
 for (unsigned char i = 0; i < 40; i++) {
     updateSensors(); 
  }  
  
  #if (DEBUG)
   Serial.print("Mag cal:");
   Serial.print(magNegOff[0]-magPosOff[0]);
   Serial.print(",");   
   Serial.print(magNegOff[1]-magPosOff[1]);
   Serial.print(",");      
   Serial.print(magNegOff[2]-magPosOff[2]);
   
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


// Calculate angle from gyro-data:
void gyroCalc() {
    
  #if (DEBUG)
      for (unsigned char i=0; i<3; i++) {
        //  angle[i]+=((float)gyroRaw[i]*sampleRate)*57.3;
          angleRaw[i]+=((gyroRaw[i]-gyroOff[i]));
          
          #if (DEBUG)
            angle[i]= angleRaw[i]/(SAMPLERATE*SCALING_FACTOR);
          #endif
      }
          
  #endif          
}
   
//Calculate angle from accelerometer data   :
void accCalc() {
      
  
    accRaw[0] += accOffset[0];
    accRaw[1] += accOffset[1];
    accRaw[2] += accOffset[2];   
  
     for (unsigned char i = 0; i<3; i++) {
      accG[i]=(float)accRaw[i]/ACC_SENS;
     }
     
     // So, lets calculate R
     // R^2 = Rx^2+Ry^2+Rz^2    
     #if (ASSUME_1G_ACC == 0) 
       R = sqrt(accG[0]*accG[0]+accG[1]*accG[1]+accG[2]*accG[2]);
     
     // Otherwise, just assume total G = 1. 
     #else
       R = 1;
     
     #endif
      
     if (R < 1.3 && R > 0.7) { 
//      if (1==1){
       // Calculate final angles: 
       for (unsigned char i = 0; i<3; i++) {
         accAngle[i]=acos(accG[i]/R)*57.3;
       }  
    
     }
}


void magCalc() {
  
// Not really any need to normalise, but will keep the code outcommented for now. 

 #if (ASSUME_1G_ACC == 0) 
   Rmag = sqrt(magRaw[0]*magRaw[0]+magRaw[1]*magRaw[1]+magRaw[2]*magRaw[2]);
 
 #else
   Rmag = 1;
 
 #endif

/* 
 // Calculate angle
   for (unsigned char i = 0; i<3; i++) {
     magAngle[i]=acos(magRaw[i]/Rmag)*57.3;
   }
*/   

    // Invert 2 axis  
    magRaw[1]*=-1;
    magRaw[2]*=-1;
    
    // Set gain:
    magRaw[0]*=magGain[0];
    magRaw[1]*=magGain[1];
    magRaw[2]*=magGain[2];    
    
    magRaw[0]-=magOffset[0];
    magRaw[1]-=magOffset[1];
    magRaw[2]-=magOffset[2];    
  
//  if (R < 1.3 && R > 0.7) {
  if (1==1) {
      float testAngle = (tiltAngle-90);
      mx = magRaw[0]*cos((testAngle)/57.3)+magRaw[1]*sin(testAngle/57.3);
      my = magRaw[0]*sin((rollAngle-90)/57.3)*sin((tiltAngle-90)/57.3)+magRaw[2]*cos((rollAngle-90)/57.3)-magRaw[1]*sin((rollAngle-90)/57.3)*cos((tiltAngle-90)/57.3);
      
      // Calculate pan-angle from magnetometer. 
      magAngle[2] = (atan(mx/my)*57.3+90);

      // Get full 0-360 degrees. 
      if (my < 0) {
          magAngle[2] +=180;
      }
      

      float tempAngle = panStart-magAngle[2];
      
      if (tempAngle > 180) {
         tempAngle -= 360; 
      }
      
      else if (tempAngle < -180) {
         tempAngle += 360; 
      }
      
      magAngle[2] = tempAngle*(-1);
  }
}


// Filter / merge sensor data. 
void filter() {
 
 // Used to set initial values. 
   if (resetValues == 1) {
      resetValues = 0; 
      
      tiltStart =0;
      panStart = 0;
      rollStart = 0;
  
        updateSensors();    
        gyroCalc();
        accCalc();
        magCalc();
      
  /*
      for (unsigned char k = 0; k< 200;k++) {
        updateSensors();    
        gyroCalc();
        accCalc();
        magCalc();
        filter();    
      }
  */    
      panAngle = 0;
      tiltStart = accAngle[0];
      panStart = magAngle[2];
      rollStart =accAngle[1];  
      
      
   }

  // Simple filter, uses mainly gyro-data, but uses accelerometer to compensate for drift
//  rollAngle = (rollAngle+((gyroRaw[0]-gyroOff[0]))/(SAMPLERATE*SCALING_FACTOR))*gyroWeight + accAngle[1]*(1-gyroWeight);

  rollAngle = (rollAngle+((gyroRaw[0]-gyroOff[0])*cos((tiltAngle-90)/57.3) + (gyroRaw[2]-gyroOff[2])*sin((tiltAngle-90)/57.3)  )/(SAMPLERATE*SCALING_FACTOR))*gyroWeight + accAngle[1]*(1-gyroWeight);

  // Simple filter, uses mainly gyro-data, but uses accelerometer to compensate for drift
//  tiltAngle = (tiltAngle+((gyroRaw[1]-gyroOff[1]))/(SAMPLERATE*SCALING_FACTOR))*gyroWeight + accAngle[0]*(1-gyroWeight);
  tiltAngle = (tiltAngle+((gyroRaw[1]-gyroOff[1])*cos((rollAngle-90)/57.3) + (gyroRaw[2]-gyroOff[2])*sin((rollAngle-90)/57.3)*(-1)  )/(SAMPLERATE*SCALING_FACTOR))*gyroWeight + accAngle[0]*(1-gyroWeight);
  
  //panAngle  = (panAngle +((gyroRaw[2]-gyroOff[2]))/(SAMPLERATE*SCALING_FACTOR))*0.997 + magAngle[2]*0.003;
  
  
//  panAngle  = (panAngle +(( (gyroRaw[2]-gyroOff[2])*(1/cos((tiltAngle-90)/57.3)) ))/(SAMPLERATE*(SCALING_FACTOR-2)))*0.99 + magAngle[2]*0.01;

//    panAngle  = (panAngle +(( (gyroRaw[2]-gyroOff[2])))/(SAMPLERATE*(SCALING_FACTOR-2)))*0.95 + magAngle[2]*0.05;
    
    

    panAngle  = (panAngle +( (gyroRaw[2]-gyroOff[2])*cos((tiltAngle-90)/57.3) + ( ((gyroRaw[0]-gyroOff[0])*(-1))* (sin((tiltAngle-90)/57.3)) ) + ( ((gyroRaw[1]-gyroOff[1])*(1))* (sin((rollAngle-90)/57.3)) )  )/(SAMPLERATE*(SCALING_FACTOR)))*GyroWeightPan + magAngle[2]*(1-GyroWeightPan);
  
 
 
 
   
if (TrackerStarted) {
  
// All lowpass-filters.

  tiltAngleLP = tiltAngle * tiltBeta + (1-tiltBeta)*lastTiltAngle;
  lastTiltAngle = tiltAngleLP;
  
  rollAngleLP = rollAngle * tiltBeta + (1-tiltBeta)*lastRollAngle;
  lastRollAngle = rollAngleLP;
  
  panAngleLP = panAngle * panBeta + (1-panBeta)*lastPanAngle;
  lastPanAngle = panAngleLP;
  
  float panAngleTemp = (panAngleLP)*(panInverse);
    if(panAngleTemp*panFactor > -panMinPulse && panAngleTemp*panFactor < panMaxPulse) {
    temp =servoPanCenter+panAngleTemp*panFactor;
    quick_test = temp;
    channel_value[htChannels[0]] = (int)temp;
    }    
    
  
  float tiltAngleTemp = (tiltAngleLP-tiltStart)*(tiltInverse);
    if(tiltAngleTemp*tiltFactor > -tiltMinPulse && tiltAngleTemp*tiltFactor < tiltMaxPulse) {
      temp =servoTiltCenter+tiltAngleTemp*tiltFactor;
      channel_value[htChannels[1]] = temp;
    }   
  
  
  float rollAngleTemp = (rollAngleLP-rollStart)*(rollInverse);
    if(rollAngleTemp*rollFactor > -rollMinPulse && rollAngleTemp*rollFactor < tiltMaxPulse) {
      temp =servoRollCenter+rollAngleTemp*rollFactor;
      channel_value[htChannels[2]] = temp;
    }
    
  }
  
}


// ===============================================
//      -------- Initialise sensors ---------
// ===============================================
void init_sensors() {

 ReadFromI2C(ITG3205_ADDR, 0x00,1);
 ITG3205_ID = sensorBuffer[0];
 
#if (DEBUG)    
 Serial.print("ITG3205: ");
 Serial.print(sensorBuffer[0]);
#endif 
 
 
 ReadFromI2C(ADXL345_ADDR, 0x00,1);
 ADXL345_ID = sensorBuffer[0];
 
#if (DEBUG)     
 Serial.print("    ADXL: ");
 Serial.print(sensorBuffer[0]); 
#endif  

// Accelerometer increase G-range (+/- 16G)
   WriteToI2C(ADXL345_ADDR, 0x31, 0b00001011);        
   

 ReadFromI2C(HMC_ADDR, 0x00,1);
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
   // Run in continious mode
 WriteToI2C(HMC_ADDR, 0x02, 0x00);    
 
 
 #if (ALWAYS_CAL_GYRO)    
 
   // Set sensor offset
   setSensorOffset();

 #endif 
 

 
 /*
 if (resetValues == 0) {
    resetValues = 0; 
    
    for (unsigned char k = 0; k< 200;k++) {
      updateSensors();    
      gyroCalc();
      accCalc();
      magCalc();
      filter();    
    }
    
    tiltStart = accAngle[0];
    panStart = magAngle[2];
    rollStart =accAngle[1];  
 } 
 
 */
 
}


void resetCenter() {
      resetValues = 0; 
    
    for (unsigned char k = 0; k< 250;k++) {
      updateSensors();    
      gyroCalc();
      accCalc();
      magCalc();
      filter();    
    }
    
    tiltStart = accAngle[0];
    panStart = magAngle[2];
    rollStart =accAngle[1];  
  
    updateSensors();    
    gyroCalc();
    accCalc();
    magCalc();
    filter();    
  
    panAngle = magAngle[2];
    tiltAngle = accAngle[0];
    rollAngle = accAngle[1];
    
    TrackerStarted = 1;
}

void SensorInfoPrint() {
 
   Serial.print("Mag cal:");
   Serial.print(magNegOff[0]-magPosOff[0]);
   Serial.print(",");   
   Serial.print(magNegOff[1]-magPosOff[1]);
   Serial.print(",");      
   Serial.print(magNegOff[2]-magPosOff[2]);
   
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
