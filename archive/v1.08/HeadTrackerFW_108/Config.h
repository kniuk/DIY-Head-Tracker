//-----------------------------------------------------------------------------
// File: Config.h
// Desc: Compilation configuration file. Defines user-configurable settings
//       as well as project-wide development #defines for configuration.
//-----------------------------------------------------------------------------
#ifndef config_h
#define config_h

//-----------------------------------------------------------------------------
// These are things you can change before you compile, to enable/disable
// features.
//

// Set to 1 to enable PPM input, 0 to disable. 
#define PPM_IN  0

// Button hold time for pause/unpause
#define BUTTON_HOLD_PAUSE_THRESH    1500    // 1.5 second button hold required to pause/unpause tracking.

// Set to 1 to enable support for positive shift PPM equipment, 0 for negative.
#define POSITIVE_SHIFT_PPM  1

// Fatshark headset headtracker module support. Set to 1 to enable.
// See: http://www.rcgroups.com/forums/showpost.php?p=23051198&postcount=573
#define FATSHARK_HT_MODULE 0


// Uncomment next line to use MPU9250 sensor board 
#define SENSOR_MPU9250

// Uncomment next line to use QMC5883 
//#define SENSOR_QMC5883


//... Check definitions above and use HMC5883 mag by default
#ifdef SENSOR_MPU9250
  #define SENSOR_NAME "MPU9250"
  #undef SENSOR_HMC5883
  #undef SENSOR_QMC5883
#else
  #ifdef SENSOR_QMC5883
    #define SENSOR_NAME "QMC5883"
    #undef SENSOR_HMC5883
  #else
    #define SENSOR_NAME "HMC5883"
    #define SENSOR_HMC5883
  #endif
#endif
//
// -- End of user-configurable parameters.
//-----------------------------------------------------------------------------

//=============================================================================

//-----------------------------------------------------------------------------
// The user generally won't need to touch any of the following
//

// Firmware Version, e.g. X.YY
#define FIRMWARE_VERSION_FLOAT  1.08    // 2 decimal places

// Number of PPM channels out. 1 - 12 channels supported. 
#define NUMBER_OF_CHANNELS 8

// Define for extra debug serial info
//#define DEBUG 0

// Output serial data to host every X frames
#define SERIAL_OUTPUT_FRAME_INTERVAL    10

// Serial communication speed. 
#define SERIAL_BAUD 57600

#define BLUETOOTH_SERIAL_BAUD 57600   //57600 appears to be max for SoftwareSerial, otherwise 115200 OK

// Dead-time between each channel in the PPM-stream. 
#define DEAD_TIME 800

// Sets the frame-length .
#define FRAME_LENGTH (unsigned int)(5003L + NUMBER_OF_CHANNELS * 5000L)

// TOP (timer rollover) used for PPM pulse time measurement
#define TOP (unsigned int)(5003L + NUMBER_OF_CHANNELS * 5000L)

// Set to 0, stored gyro calibration is used. If 1, gyro is calibrated at powerup  
#define ALWAYS_CAL_GYRO 0

// Center/pause input button pin number
#define BUTTON_INPUT 10

// Arduino LED
#define  ARDUINO_LED 13

// Pin definition for LED and buzzer (Fatshark goggles)
#if FATSHARK_HT_MODULE
    #define  BUZZER      4
#endif

#define PPM_IN_MIN 1000 // 0.5 ms
#define PPM_IN_MAX 4000 // 2 ms

// Settings stuff
//
#define HT_TILT_REVERSE_BIT     0x01
#define HT_ROLL_REVERSE_BIT     0x02
#define HT_PAN_REVERSE_BIT      0x04

#define BT_POWER_PIN_1 11
#define BT_POWER_PIN_2 12

#define BLUETOOTH_MODE_DISABLED 0
#define BLUETOOTH_MODE_TRACKER 1
#define BLUETOOTH_MODE_RECEIVER 2

#endif
