

// Written by Dennis Frie - 2012
// Contact: Dennis.frie@gmail.com

// Version 0.08

// Discussion:
// http://www.rcgroups.com/forums/showthread.php?t=1677559


/*
Channel mapping/config for PPM out:

1 = PPM CHANNEL 1
2 = PPM CHANNEL 2
3 = PPM CHANNEL 3
4 = PPM CHANNEL 4
5 = PPM CHANNEL 5
6 = PPM CHANNEL 6
7 = PPM CHANNEL 7
8 = PPM CHANNEL 8
9 = PPM CHANNEL 9
10 = PPM CHANNEL 10
11 = PPM CHANNEL 11
12 = PPM CHANNEL 12

20 = ANALOG INPUT 0
21 = ANALOG INPUT 1
22 = ANALOG INPUT 2
23 = ANALOG INPUT 3
24 = ANALOG INPUT 4
25 = ANALOG INPUT 5
26 = ANALOG INPUT 6
27 = ANALOG INPUT 7

20 = DIGITAL INPUT 0
21 = DIGITAL INPUT 1
22 = DIGITAL INPUT 2
23 = DIGITAL INPUT 3
24 = DIGITAL INPUT 4
25 = DIGITAL INPUT 5
26 = DIGITAL INPUT 6
27 = DIGITAL INPUT 7

30 = HT pan
31 = HT tilt
32 = HT roll

Mapping example:
$123456789111CH

*/
#include <Wire.h>

#include "config.h"
#include "functions.h"
#include "sensors.h"
#include "PPM_Read.h"

#include <EEPROM.h>

extern unsigned char channel_mapping[];
extern unsigned char PpmIn_PpmOut[13];
extern char read_sensors;
extern long channel_value[];

extern float gyroOff[];


int counter =0;      // Delay for serial-output. 
char printPlot = 0;  // print plot for GUI?

// External variables (from sensors.h):
extern float tiltBeta;
extern float panBeta;
extern float gyroWeight;
extern float GyroWeightPan;
extern int maxPulse;
extern int servoPanCenter;
extern int servoTiltCenter;
extern int servoRollCenter;

extern int panMaxPulse;
extern int panMinPulse;
extern int tiltMaxPulse;
extern int tiltMinPulse;
extern int rollMaxPulse;
extern int rollMinPulse;

extern float panFactor;
extern float tiltFactor;  
extern float rollFactor;  

extern char tiltInverse;
extern char rollInverse;
extern char panInverse;

extern float magOffset[];

extern int accOffset[]; 

extern unsigned char htChannels[];

extern char resetValues;           

void setup() {
  
  Serial.begin(SERIAL_BAUD);

  
  pinMode(7,OUTPUT);
  pinMode(9,OUTPUT);
  digitalWrite(2,HIGH);
  digitalWrite(3,HIGH);  
  
  pinMode(0,INPUT);
  pinMode(1,INPUT);
  pinMode(2,INPUT);
  pinMode(3,INPUT);
  pinMode(6,INPUT);
  pinMode(7,INPUT);  
  pinMode(8,INPUT);    

  //Set button pin to input:
  pinMode(BUTTON_INPUT,INPUT);
  
  //Set internal pull-up resistor. 
  digitalWrite(BUTTON_INPUT,HIGH);
  
  digitalWrite(0,LOW); // pull-down resistor
  digitalWrite(1,LOW);
  digitalWrite(2,HIGH);
  digitalWrite(3,HIGH);  
  
  
//  attachInterrupt(0,detect_PPM,CHANGE); // Interrupt to detect PPM-in. 
  init_pwm_interrupt();          // Start PWM interrupt  

  Wire.begin();                  // Start I2C


// If the device have just been programmed, write initial config/values to EEPROM:
  if (EEPROM.read(0) != 8)  {
    
 //  #if (DEBUG)
     Serial.println("New board - saving default values!");
 //  #endif    
    
      init_sensors();
   #if (ALWAYS_CAL_GYRO ==0)    
     setSensorOffset();
   #endif     

    saveSettings();
    saveMagData();
    saveAccData(); 
    EEPROM.write(0,8); 
  }
  
  

  getSettings();                 // Get settings saved in EEPROM
  
  init_sensors();                // Initialise I2C sensors
  calMag();
  resetCenter();
  init_timer_interrupt();        // Start timer interrupt (for sensors)  
  
  
}


char serial_data[101];           // Array for serial-data 
unsigned char serial_index =0;   // How many bytes have been received?
char string_started = 0;         // Only saves data if string starts with right byte

char outputMag = 0;
char outputAcc = 0;


void loop() {
  
  // Check button
  if (digitalRead(BUTTON_INPUT)==0) {
   resetValues = 1; 
  }
  
  
// All this is used for communication with GUI  
  if (Serial.available()) {
    
    if (string_started == 1) {
      
         // Read incoming byte
           serial_data[serial_index++] = Serial.read();
           
           // If string ends with 'CH" it's channel configuration, that have been received.
           // String must always be 12 chars/bytes and ending with CH to be valid. 
           if (serial_data[serial_index-2] == 'C' && serial_data[serial_index-1] == 'H' && serial_index == 14) {
  
              // To keep it simple, we will not let the channels be 0-initialised, but start from 1 to match actual channels. 
               for (unsigned char i=0; i<13; i++) {
                  channel_mapping[i+1] = serial_data[i]-48;
                  
                  // Update the dedicated PPM-in -> PPM-out array for faster performance.
                  if (serial_data[i]-48 < 14) {
//                    PpmIn_PpmOut[i+1] =  serial_data[i]-48;
                    PpmIn_PpmOut[serial_data[i]-48] =i+1;
                  }
                  
               }
               
               Serial.println("Channel mapping received");
               
               // Reset serial_index and serial_started
               serial_index=0;
               string_started = 0;
           }
           
           
           
          if (serial_data[serial_index-2] == 'H' && serial_data[serial_index-1] == 'E') {

           
           // We need 8 parameters:
           
           // LP_tilt
           // LP_pan
           // Gyro_weight_tilt
           // Gyro_weight_pan
           // servo_max
           // servo_min
           // tilt_servo_gain
           // pan_servo_gain
           
           Serial.println("HT config received:");
           
           /*
           for (unsigned char k = 0; k< 10; k++) {
            valuesReceived[k] =0; 
           }
           */
           int valuesReceived[20] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
           int comma_index =0;



           for (unsigned char k = 0; k < serial_index-2; k++) {
             
               // Looking for comma
               if (serial_data[k] == 44) {
                 comma_index++;
               }
             
             else {
             valuesReceived[comma_index] = valuesReceived[comma_index]*10 + (serial_data[k]-48);
             }
             
             
             // Mainly for debug:
             #if (DEBUG)
             Serial.print(serial_data[k]);
             #endif
             
          }



          
          #if (DEBUG)
           Serial.println();
            for (unsigned char k = 0; k < comma_index+1; k++) {
               Serial.print(valuesReceived[k]); 
               Serial.print(",");           
            }
           Serial.println();
          #endif

         tiltBeta        = (float)valuesReceived[0] / 100;  
         panBeta         = (float)valuesReceived[1] / 100;
         gyroWeight      = (float)valuesReceived[2] / 100;
         GyroWeightPan   = (float)valuesReceived[3] / 100;

         tiltFactor     = (float)valuesReceived[4] / 10;         
         panFactor     = (float)valuesReceived[5] / 10;          
         rollFactor     = (float)valuesReceived[6] / 10;   
  

           
        tiltInverse = 1;
        rollInverse = 1;
        panInverse = 1;           
           
         if (valuesReceived[7] / 100 == 1) {
             panInverse = -1;
             valuesReceived[7]-=100;
         }  
         
         if (valuesReceived[7] / 10 == 1) {
          rollInverse = -1; 
          valuesReceived[7]-=10;
         }

         if (valuesReceived[7] / 1 == 1) {
           tiltInverse = -1;
         }
               serial_index=0;
               string_started = 0; 


         
         servoPanCenter = valuesReceived[8];
         panMinPulse = valuesReceived[9];
         panMaxPulse = valuesReceived[10];         
         
         servoTiltCenter = valuesReceived[11];
         tiltMinPulse = valuesReceived[12];
         tiltMaxPulse = valuesReceived[13];         

         servoRollCenter = valuesReceived[14];
         rollMinPulse = valuesReceived[15];
         rollMaxPulse = valuesReceived[16];              
     
         htChannels[0] = valuesReceived[17];                   
         htChannels[1] = valuesReceived[18];              
         htChannels[2] = valuesReceived[19];                       
         
         Serial.println(htChannels[0]);
         Serial.println(htChannels[1]);
         Serial.println(htChannels[2]);                
        
         saveSettings();
             
          }
          
          // Debug info
          else if (serial_data[serial_index-5] == 'D' && serial_data[serial_index-4] == 'E' && serial_data[serial_index-3] == 'B' && serial_data[serial_index-2] == 'U' && serial_data[serial_index-1] == 'G') {  
               debugOutput();
               
               serial_index=0;
               string_started = 0; 
          }                         
          

          // Start magnetometer cal
          else if (serial_data[serial_index-4] == 'C' && serial_data[serial_index-3] == 'A' && serial_data[serial_index-2] == 'S' && serial_data[serial_index-1] == 'T') {  
               outputMag = 1;
               
               serial_index=0;
               string_started = 0; 
          }        
          
          
          // Start accelerometer cal
          else if (serial_data[serial_index-4] == 'G' && serial_data[serial_index-3] == 'R' && serial_data[serial_index-2] == 'A' && serial_data[serial_index-1] == 'V') {  
               outputAcc = 1;
               
               serial_index=0;
               string_started = 0; 
          }              

          // Stop magnetometer cal
          else if (serial_data[serial_index-4] == 'C' && serial_data[serial_index-3] == 'A' && serial_data[serial_index-2] == 'E' && serial_data[serial_index-1] == 'N') {  
               outputMag = 0;
               
               serial_index=0;
               string_started = 0; 
          }
          
          // Stop accelerometer cal
          else if (serial_data[serial_index-4] == 'G' && serial_data[serial_index-3] == 'R' && serial_data[serial_index-2] == 'E' && serial_data[serial_index-1] == 'N') {  
               outputAcc = 0;
               
               serial_index=0;
               string_started = 0; 
          }

          

          
          // Start plotting if PLST received:
          else if (serial_data[serial_index-4] == 'P' && serial_data[serial_index-3] == 'L' && serial_data[serial_index-2] == 'S' && serial_data[serial_index-1] == 'T') {  
               printPlot = 1;
               
               serial_index=0;
               string_started = 0; 
          }        

          // Stop plotting if PLEN received:          
          else if (serial_data[serial_index-4] == 'P' && serial_data[serial_index-3] == 'L' && serial_data[serial_index-2] == 'E' && serial_data[serial_index-1] == 'N') {  
               printPlot = 0;
               
               serial_index=0;
               string_started = 0; 
          }
          
          // Save settings
          else if (serial_data[serial_index-4] == 'S' && serial_data[serial_index-3] == 'A' && serial_data[serial_index-2] == 'V' && serial_data[serial_index-1] == 'E') {  
               saveSettings();
               
               serial_index=0;
               string_started = 0; 
          }          
          
          //Calibrate gyro
          else if (serial_data[serial_index-4] == 'C' && serial_data[serial_index-3] == 'A' && serial_data[serial_index-2] == 'L' && serial_data[serial_index-1] == 'I') {  
               setSensorOffset();
               saveSettings();
               
                Serial.print("Gyro offset measured:");
                Serial.print(gyroOff[0]);
                Serial.print(",");   
                Serial.print(gyroOff[1]);
                Serial.print(",");      
                Serial.println(gyroOff[2]);    
               
               serial_index=0;
               string_started = 0; 
          }


            else if (serial_data[serial_index-2] == 'M' && serial_data[serial_index-1] == 'A') {
              Serial.println(serial_data);
              int valuesReceived[5] = {0,0,0,0,0};
              int comma_index =0; 
              
           for (unsigned char k = 0; k < serial_index-2; k++) {
                 
                   // Looking for comma
                   if (serial_data[k] == 44) {
                     comma_index++;
                   }
                 
                 else {
                 valuesReceived[comma_index] = valuesReceived[comma_index]*10 + (serial_data[k]-48);
                 }              
                  
                  
                  
                }
                

                  magOffset[0] = valuesReceived[0]-2000;
                  magOffset[1] = valuesReceived[2]-2000;
                  magOffset[2] = valuesReceived[1]-2000;
                  
                  saveMagData();                
            }
            
            
            else if (serial_data[serial_index-3] == 'A' && serial_data[serial_index-2] == 'C' && serial_data[serial_index-1] == 'C') {
              Serial.println(serial_data);
              int valuesReceived[5] = {0,0,0,0,0};
              int comma_index =0; 
              
           for (unsigned char k = 0; k < serial_index-3; k++) {
                 
                   // Looking for comma
                   if (serial_data[k] == 44) {
                     comma_index++;
                   }
                 
                 else {
                 valuesReceived[comma_index] = valuesReceived[comma_index]*10 + (serial_data[k]-48);
                 }              
                  
                  
                  
                }

                  accOffset[0] = valuesReceived[0]-2000;
                  accOffset[1] = valuesReceived[1]-2000;
                  accOffset[2] = valuesReceived[2]-2000;
                  
                  saveAccData();                
            }            
            
           
   
         // If more than 100 bytes have been received, the string is not valid. Reset and "try again" (wait for $ to indicate start of new string). 
           else if (serial_index > 100) {
               serial_index = 0;
               string_started = 0;
           }      
          
     }
    
    else if (Serial.read() == '$') {
        string_started = 1;
    }
    
 
     
  }
  
  // if "read_sensors" flag is set high, read sensors and update
  if (read_sensors == 1) {
    
        updateSensors();
    
        gyroCalc();
        accCalc();
        magCalc();
        filter();    
               
        if (counter++ >7) {
          
//          testGyroOutput();
       //   testMagOutput();
//           quickTest(); 
          
          if (printPlot == 1) {
             headtrackerOutput();
                  
          }
        
          else if (outputMag) {
             calMagOutput(); 
          }
          
          else if (outputAcc) {
            calAccOutput();
          }
        
            counter=0; 
        }
    
    
    // Will first update read_sensors when everything's done.  
        read_sensors = 0;
        
    }
 
  
}

void saveSettings() {
  
// This is the necessary head-tracler settings:
/*
         tiltBeta        = (float)valuesReceived[0] / 100;  
         panBeta         = (float)valuesReceived[1] / 100;
         gyroWeight      = (float)valuesReceived[2] / 100;
         GyroWeightPan   = (float)valuesReceived[3] / 100;  
         maxPulse        = valuesReceived[4];
         servoCenter     = valuesReceived[5];         
         tiltFactor     = (float)valuesReceived[6] / 10;         
         panFactor     = (float)valuesReceived[7] / 10;  
*/         
  
  // Chars
  EEPROM.write(1,(unsigned char) (tiltBeta*100));
  EEPROM.write(2,(unsigned char) (panBeta*100));
  EEPROM.write(3,(unsigned char) (gyroWeight*100));
  EEPROM.write(4,(unsigned char) (GyroWeightPan*100));
  
  // And some integers 
  EEPROM.write(5,(unsigned char)maxPulse);
  EEPROM.write(6,(unsigned char)(maxPulse>>8));
  
  EEPROM.write(7,(unsigned char)servoPanCenter);
  EEPROM.write(8,(unsigned char)(servoPanCenter>>8));  
  
  EEPROM.write(9,(unsigned char) (tiltFactor*10));
  EEPROM.write(10,(int)((tiltFactor*10))>>8);  

  EEPROM.write(11,(unsigned char) (panFactor*10));
  EEPROM.write(12,(int)((panFactor*10))>>8);  

  // Channel inverse settings:
  EEPROM.write(13,(unsigned char)(tiltInverse+1));
  EEPROM.write(14,(unsigned char)(rollInverse+1));    
  EEPROM.write(15,(unsigned char)(panInverse+1));  

  EEPROM.write(16,(unsigned char)servoTiltCenter);
  EEPROM.write(17,(unsigned char)(servoTiltCenter>>8));  

  EEPROM.write(18,(unsigned char)servoRollCenter);
  EEPROM.write(19,(unsigned char)(servoRollCenter>>8));  


  EEPROM.write(20,(unsigned char)panMaxPulse);
  EEPROM.write(21,(unsigned char)(panMaxPulse>>8));  
  
  EEPROM.write(22,(unsigned char)panMinPulse);
  EEPROM.write(23,(unsigned char)(panMinPulse>>8));    

  EEPROM.write(24,(unsigned char)tiltMaxPulse);
  EEPROM.write(25,(unsigned char)(tiltMaxPulse>>8));    

  EEPROM.write(26,(unsigned char)tiltMinPulse);
  EEPROM.write(27,(unsigned char)(tiltMinPulse>>8));    


  EEPROM.write(28,(unsigned char)rollMaxPulse);
  EEPROM.write(29,(unsigned char)(rollMaxPulse>>8));    

  EEPROM.write(30,(unsigned char)rollMinPulse);
  EEPROM.write(31,(unsigned char)(rollMinPulse>>8)); 
  
  
  EEPROM.write(32,(unsigned char)htChannels[0]);
  EEPROM.write(33,(unsigned char)htChannels[1]);
  EEPROM.write(34,(unsigned char)htChannels[2]);
  
  // Saving gyro calibration values
  int temp = (int)(gyroOff[0]+500.5);
  EEPROM.write(35,(unsigned char)temp);
  EEPROM.write(36,(unsigned char)(temp>>8));   
  
  temp = (int)(gyroOff[1]+500.5);
  EEPROM.write(37,(unsigned char)temp);
  EEPROM.write(38,(unsigned char)(temp>>8));     

  temp = (int)(gyroOff[2]+500.5);
  EEPROM.write(39,(unsigned char)temp);
  EEPROM.write(40,(unsigned char)(temp>>8));    
  
  Serial.println("Settings saved!");
}


void getSettings() {
  
  tiltBeta = (float)EEPROM.read(1)/100;
  panBeta = (float)EEPROM.read(2)/100;
  gyroWeight = (float)EEPROM.read(3)/100;
  GyroWeightPan = (float)EEPROM.read(4)/100;  
  
  maxPulse = EEPROM.read(5)+(EEPROM.read(6)<<8);
  
  servoPanCenter = EEPROM.read(7)+(EEPROM.read(8)<<8);
  
  tiltFactor = (float)(EEPROM.read(9)+(EEPROM.read(10)<<8)) / 10;
  
  panFactor = (float)(EEPROM.read(11)+(EEPROM.read(12)<<8)) / 10;  


  servoTiltCenter = EEPROM.read(16)+(EEPROM.read(17)<<8);
  servoRollCenter = EEPROM.read(18)+(EEPROM.read(19)<<8);  
  
  panMaxPulse = EEPROM.read(20)+(EEPROM.read(21)<<8);  
  panMinPulse = EEPROM.read(22)+(EEPROM.read(23)<<8);    
  
  tiltMaxPulse = EEPROM.read(24)+(EEPROM.read(25)<<8);  
  tiltMinPulse = EEPROM.read(26)+(EEPROM.read(27)<<8);      
  
  rollMaxPulse = EEPROM.read(28)+(EEPROM.read(29)<<8);  
  rollMinPulse = EEPROM.read(30)+(EEPROM.read(31)<<8);        
  
  htChannels[0] = EEPROM.read(32);  
  htChannels[1] = EEPROM.read(33);  
  htChannels[2] = EEPROM.read(34);    
  
  gyroOff[0] = EEPROM.read(35)+(EEPROM.read(36)<<8)-500; 
  gyroOff[1] = EEPROM.read(37)+(EEPROM.read(38)<<8)-500; 
  gyroOff[2] = EEPROM.read(39)+(EEPROM.read(40)<<8)-500;   
  
  
  tiltInverse = -1;
  rollInverse = -1;
  panInverse = -1;
  
  if (EEPROM.read(13) == 2) {
      tiltInverse = 1;
  }  

  if (EEPROM.read(14) == 2) {
      rollInverse = 1;
  }  
  
  if (EEPROM.read(15) == 2) {
      panInverse = 1;
  }


  magOffset[0] = EEPROM.read(200)+(EEPROM.read(201)<<8)-2000;     
  magOffset[1] = EEPROM.read(202)+(EEPROM.read(203)<<8)-2000;     
  magOffset[2] = EEPROM.read(204)+(EEPROM.read(205)<<8)-2000;       
  
  accOffset[0] = EEPROM.read(206)+(EEPROM.read(207)<<8)-2000;     
  accOffset[1] = EEPROM.read(208)+(EEPROM.read(209)<<8)-2000;     
  accOffset[2] = EEPROM.read(210)+(EEPROM.read(211)<<8)-2000;       
  
 
#if (DEBUG)    
 
debugOutput();
 
#endif
 
}


void saveMagData() {
  int temp; 
    temp = (int)(magOffset[0]+2000);
  EEPROM.write(200,(unsigned char)temp);
  EEPROM.write(201,(unsigned char)(temp>>8));   
  
    temp = (int)(magOffset[1]+2000);
  EEPROM.write(202,(unsigned char)temp);
  EEPROM.write(203,(unsigned char)(temp>>8));   
  
    temp = (int)(magOffset[2]+2000);
  EEPROM.write(204,(unsigned char)temp);
  EEPROM.write(205,(unsigned char)(temp>>8));   
  
  Serial.println("Mag-offset saved!"); 
  
}



void saveAccData() {
  int temp; 
    temp = (int)(accOffset[0]+2000);
  EEPROM.write(206,(unsigned char)temp);
  EEPROM.write(207,(unsigned char)(temp>>8));   
  
    temp = (int)(accOffset[1]+2000);
  EEPROM.write(208,(unsigned char)temp);
  EEPROM.write(209,(unsigned char)(temp>>8));   
  
    temp = (int)(accOffset[2]+2000);
  EEPROM.write(210,(unsigned char)temp);
  EEPROM.write(211,(unsigned char)(temp>>8));   
  
  Serial.println("Acc-offset saved!"); 
  Serial.print(accOffset[0]);
  Serial.print(","); 
  Serial.print(accOffset[1]);
  Serial.print(",");   
  Serial.println(accOffset[2]);
  
}



void debugOutput() {
  
Serial.println();  
Serial.println();
Serial.println();
Serial.println("------ Debug info------");
  
 Serial.print("tiltBeta: ");
 Serial.println(tiltBeta); 

 Serial.print("panBeta: ");
 Serial.println(panBeta); 
 
 Serial.print("gyroWeight: ");
 Serial.println(gyroWeight); 

 Serial.print("GyroWeightPan: ");
 Serial.println(GyroWeightPan); 

 Serial.print("servoPanCenter: ");
 Serial.println(servoPanCenter); 
 
 Serial.print("servoTiltCenter: ");
 Serial.println(servoTiltCenter); 

 Serial.print("servoRollCenter: ");
 Serial.println(servoRollCenter); 

 Serial.print("tiltFactor: ");
 Serial.println(tiltFactor); 

 Serial.print("panFactor: ");
 Serial.println(panFactor);  
 
 Serial.print("Gyro offset saved ");
 Serial.print(gyroOff[0]);
 Serial.print(",");   
 Serial.print(gyroOff[1]);
 Serial.print(",");      
 Serial.println(gyroOff[2]);    
 
 Serial.print("Mag offset saved ");
 Serial.print(magOffset[0]);
 Serial.print(",");   
 Serial.print(magOffset[1]);
 Serial.print(",");      
 Serial.println(magOffset[2]);
 
 Serial.print("Acc offset saved ");
 Serial.print(accOffset[0]);
 Serial.print(",");   
 Serial.print(accOffset[1]);
 Serial.print(",");      
 Serial.println(accOffset[2]);
 

 SensorInfoPrint();    
 
 
}



