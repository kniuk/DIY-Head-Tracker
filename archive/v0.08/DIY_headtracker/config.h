
#ifndef config_h
#define config_h

//Serial communication speed. 
#define SERIAL_BAUD 57600

// Sensor board update-rate. Not done yet. 
#define UPDATE_RATE 50

// Dead-time between each channel in the PPM-stream. 
#define DEAD_TIME 800

// Number of PPM channels out. 1 - 12 channels supported (both incl). 
#define NUMBER_OF_CHANNELS 8

// Sets the frame-length .
//#define FRAME_LENGTH (5000*NUMBER_OF_CHANNELS+5003)

//#define FRAME_LENGTH_TEMP (5000*NUMBER_OF_CHANNELS+5003)
//#define FRAME_LENGTH 45003
#define FRAME_LENGTH 5003+NUMBER_OF_CHANNELS*5000

//#define TOP 65535
#define TOP 5003+NUMBER_OF_CHANNELS*5000

// If defined, it will use stored gyro-calibration.  
#define ALWAYS_CAL_GYRO 0

// Button input:
#define BUTTON_INPUT 11

// Is PPM input used? 
#define PPM_IN 0

#define PPM_IN_MIN 1000 // 0.5 ms
#define PPM_IN_MAX 4000 // 2 ms

#define DEBUG 0

#endif
