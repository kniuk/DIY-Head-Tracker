#include "config.h"
#include "Arduino.h"
#include "functions.h"
#include "sensors.h"
#include <Wire.h>

char read_sensors = 0;

// Sensor_board,   x,y,z
int acc_raw[3]  = {1,2,3};  
int gyro_raw[3] = {4,5,6};
int mag_raw[3]  = {7,8,9};

unsigned char channel_mapping[13];
//unsigned char PpmIn_PpmOut[13] = {0,1,2,3,4,5,6,7,8,9,10,11,12};

unsigned char PpmIn_PpmOut[13] = {0,
1,2,3,4,5,6,7,8,9,10,11,12};

unsigned int analog_readings[4];

int test =0;
int test2 =0;

long channel_value[13] ={2100,
2100,2100,2100,2100,2100,2100,2100,2100,2100,2100,2100,2100};

long PPMIn[13] ={2100,
2100,2100,2100,2100,2100,2100,2100,2100,2100,2100,2100,2100};

unsigned char channel_number =1;

// For PPM detection
signed long last_time = 0;
signed long this_time = 0;
signed long servo_time = 0;

unsigned char read_ppm_channel =1;

int temp2 =0;

int timeTest = 0;

char shift = 0;

char time_out =0;

void printPPM() {

  for (char j =1; j<13; j++) {
  Serial.print(channel_value[j]);
  Serial.print(",");
  }
  Serial.println();
  
}

void init_pwm_interrupt() {
  
  #if (DEBUG)    
  Serial.println("PWM interrupt initialised");
  #endif
  
  
    TCCR1A = 
   (0<<WGM10) |
   (0<<WGM11) |
   (0<<COM1A1) |
   (1<<COM1A0) | // Toggle pin om compare-match
   (0<<COM1B1) |
   (0<<COM1B0);  
  
    TCCR1B =
    (1<<ICNC1)| // Input capture noise canceler - set to active 
    (1<<ICES1)| // Input capture edge select. 1 = rising, 0 = falling. We will toggle this, doesn't matter what it starts at        
    (0<<CS10) | //Prescale 8  
    (1<<CS11) | //Prescale 8  
    (0<<CS12) | //Prescale 8
    (0<<WGM13)|    
    (1<<WGM12); // CTC mode (Clear timer on compare match) with ICR1 as top.           
    
    // Not used in this case:
    TCCR1C =
    (0<<FOC1A)| // No force output compare (A)
    (0<<FOC1B); // No force output compare (B)
        
    
    TIMSK1 = 
    (PPM_IN<<ICIE1) | // Enable input capture interrupt    
    (1<<OCIE1A) | // Interrupt on compare A
    (0<<OCIE1B) | // Disable interrupt on compare B    
    (0<<TOIE1);          

   // OCR1A is used to generate PPM signal and later reset counter (to control frame-length)
    OCR1A = DEAD_TIME;    
    
}

void init_timer_interrupt() {
  
#if (DEBUG)    
    Serial.println("Timer interrupt initialised");
#endif
  
   TCCR0A = 
   (0<<WGM00) |
   (1<<WGM01) |
   (0<<COM0A1) |
   (0<<COM0A0) |
   (0<<COM0B1) |
   (0<<COM0B0);  
   
   // 61 hz update-rate:
    TCCR0B =
    (0<<FOC0A)| // 
    (0<<FOC0B)| // 
    (1<<CS00) | //Prescale 1024 
    (0<<CS01) | //Prescale 1024  
    (1<<CS02) | //Prescale 1024
    (0<<WGM02);
  
    TIMSK0 = 
    (0<<OCIE0B) |
    (1<<OCIE0A) |
    (1<<TOIE0);       

    OCR0B = 64*2; 
    OCR0A = 64*2; 



}


// ===========================
// Timer 1 overflow vector
// ===========================

// Timer 1 overflow vector - only here for debugging/testing, as it should always be reset/cleared before overflow. 
ISR(TIMER1_OVF_vect) {
  Serial.print("Timer 1 OVF");
}


// ===========================
// Timer 1 compare A vector
// ===========================

ISR(TIMER1_COMPA_vect) {

  
  if (OCR1A == FRAME_LENGTH) {
      TCCR1A = 
     (0<<WGM10) |
     (0<<WGM11) |
     (1<<COM1A1) |
     (1<<COM1A0) |
     (0<<COM1B1) |
     (0<<COM1B0);   
  
      channel_number =1;
      OCR1A = DEAD_TIME;
  
      TCCR1B &= ~(1<<WGM12);
  }
  
  
  else {
          if (channel_number == 1) {
             
            // After first time, when pin have been set hgih, we toggle the pin at each interrupt
              TCCR1A = 
             (0<<WGM10) |
             (0<<WGM11) |
             (0<<COM1A1) |
             (1<<COM1A0) |
             (0<<COM1B1) |
             (0<<COM1B0);   
          }
          
          
          if ((channel_number-1) < NUMBER_OF_CHANNELS*2) {
            
                if ((channel_number-1)%2 == 1) {
                 OCR1A += DEAD_TIME; 
                }
                
                else {
                 OCR1A += channel_value[(channel_number+1)/2];
                }
                
              channel_number++;
          }

          else {
            
            // We have to use OCR1A as top too, as ICR1 is used for input capture and OCR1B can't be used as top. 
            OCR1A = FRAME_LENGTH; //FRAME_LENGTH; //FRAME_LENGTH;
            TCCR1B |= (1<<WGM12);
          }
  
  }
  
  
}  



// ===========================
// Timer 0 compare A vector
// Sensor-interrupt
// ===========================

ISR(TIMER0_COMPA_vect) {
  
  /*
  for (unsigned char i = 0; i < 4; i++) {
    analog_readings[i]  = analogRead(i);
  }
  */
  
  // Reset counter - should be changed to CTC timer mode. 
  TCNT0= 0;

  // Used to check timing - have the previous calculations been done?
  // Will always show in start, but should stop when initialised. 
  if (shift == 1) {
//   digitalWrite(7,HIGH); 
   shift = 0;
  }
  else {
//   digitalWrite(7,LOW);
  shift = 1; 
  }
  

#if (DEBUG == 1)  
    if (read_sensors == 1) {
      time_out++;
      if (time_out > 10) {
//      Serial.println("Timing problem!!!"); 
      time_out = 0;  
    }
      
    }
#endif
       read_sensors = 1;


  }
  

void get_data() {
}

void set_pwm() {
}


// ===========================
// Test function
// ===========================

void test_output() {
 Serial.print("Acc x: ");
 Serial.print(acc_raw[0]);
 Serial.print(" y: ");  
 Serial.print(acc_raw[1]);
 Serial.print(" z: ");  
 Serial.println(acc_raw[2]); 
 
}

