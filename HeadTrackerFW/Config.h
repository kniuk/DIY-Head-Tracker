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
// See: http:/e/www.rcgroups.com/forums/showpost.php?p=23051198&postcount=573
#define FATSHARK_HT_MODULE 0

// Since there are differences in pin assignement between Quanum HT and newer DIY HT with BT support
// Set to 0 to use on hardware according to DIY project with BT support, set to 1 to use with older DIY hardware, or ready made Quanum Head Tracker
#define QUANUM_HT_MODULE 1

// Normally set to zero to use 16MHz arduino board
// For BLUETOOTH_MODE_RECEIVER using 8MHZ 3.3V board set to 1. It will allow to use smaller raw BT module without mother PCB with 5V to 3.3V voltage regulator
// For 3.3V@8MHz Arduino Pro Mini supply RAW pin from 5V SMART Port pin in your radio
// Pay attention to set in Arduino PC Software: Tools -> Processor -> ATmega328P(3.3V, 8MHz) or ATmega328P(5V, 16MHz) correspondingly
#define ARDUINO_8MHZ 1

// If you use BT module HM10 or HM11, uncomment init strings to properly set the modules, then comment it again after confrmed that modules work OK
#define BT_HM10_HM11 1

//when you use bare HM10/HM11 modules requiring 3.3V supply, connect module's VCC to 3.3V (add 100nF cap) and this Arduino pin via NPN transistor inverter to RESETB pin on the module. This will hold module's TX and RX pins high with internal pullups of about 100k
#define BT_DISABLE_BY_RESET_PIN 1

// Uncomment next line to use MPU9250 sensor board 
//#define SENSOR_MPU9250

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
#define FIRMWARE_VERSION_FLOAT  1.09    // 2 decimal places

// Number of PPM channels out. 1 - 12 channels supported. 
#define NUMBER_OF_CHANNELS 8

// Define for extra debug serial info
//#define DEBUG 0

// Output serial data to host every X frames
#define SERIAL_OUTPUT_FRAME_INTERVAL    10

// Serial communication speed. 
#define SERIAL_BAUD 57600

#define BLUETOOTH_SERIAL_BAUD 57600  //57600 appears to be max for SoftwareSerial, otherwise 115200 OK

#if ARDUINO_8MHZ
  #define MHZ_DIVIDER 2
#else
  #define MHZ_DIVIDER 1
#endif

// Dead-time between each channel in the PPM-stream. 
#define DEAD_TIME 900 / MHZ_DIVIDER //it was 800, perhaps 2100+900 = 3000/2 = 1500us

// Sets the frame-length .
#define FRAME_LENGTH (unsigned int)((5000L + NUMBER_OF_CHANNELS * 5000L) / MHZ_DIVIDER)

// TOP (timer rollover) used for PPM pulse time measurement
#define TOP (unsigned int)(5000L + NUMBER_OF_CHANNELS * 5000L)

// Set to 0, stored gyro calibration is used. If 1, gyro is calibrated at powerup  
#define ALWAYS_CAL_GYRO 1

// Center/pause input button pin number, pin 11 for Quanum Head Tracker and older DIY project, pin 10 for newer DIY project (with BT support)
#if QUANUM_HT_MODULE
  #define BUTTON_INPUT 11
#else
  #define BUTTON_INPUT 10
#endif

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

#if BT_DISABLE_BY_RESET_PIN
  #define BT_RESET_PIN 12
#else
  #if (QUANUM_HT_MODULE == 0)
    #define BT_POWER_PIN_1 11
    #define BT_POWER_PIN_2 12 
  #endif
#endif

#define BLUETOOTH_MODE_DISABLED 0
#define BLUETOOTH_MODE_TRACKER 1
#define BLUETOOTH_MODE_RECEIVER 2

#define BLUETOOTH_RESEND_DELAY    250    // used on Bluetooth receiver: milis to wait for acknowledgement before retransmitting command
#define BLUETOOTH_RESEND_COUNT    2    // used on Bluetooth receiver: how many times to retransmit command before giving up
#define BUTTON_DEBOUNCE_DELAY 50  //button debounce time

#endif
