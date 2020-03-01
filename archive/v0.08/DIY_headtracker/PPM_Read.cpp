
#include "config.h"
#include "Arduino.h"

extern long channel_value[];

  // Variables used:
  unsigned int pulseTime = 0; 
  unsigned int lastTime = 0; 
  unsigned int timeRead; 
  
  int channelsDetected =0;
  
  // PPM signal high or Low?
  char state =0;
  
  extern unsigned char PpmIn_PpmOut[]; 
  
// Values used for PPM-signal:
char channel = 0;
int channelValues[20]; 

void detectPPM() {
  
  // If a new frame is detected (3600 is just a quick picked value - should probably be a lot higher)
  if (pulseTime > 5500) {
    
    // Save total channels detected
     channelsDetected = channel; 
     
     // Reset channel-count
     channel = 0; 
  }
  
  // If the pulse is recognised as servo-pulse:
  else if (channel < 20 && pulseTime > PPM_IN_MIN && pulseTime < PPM_IN_MAX) {
     channelValues[channel++] = pulseTime;
//     channel_value[channel] = pulseTime;      
     
     channel_value[PpmIn_PpmOut[channel]] = pulseTime;
  }
  
  else if (pulseTime > PPM_IN_MIN) {
    channel++;
  }
  
}  
  
  
  
// ===========================
// Read PPM
// ===========================  
  
  // The interrupt vector used when an edge is detected
  // Interrupt vector, see page 57
  // Interrupt for input capture
  ISR(TIMER1_CAPT_vect) {

    // Disable interrupt first, too avoid multiple interrupts causing hanging/restart - or just weird behavior:
    TIMSK1 &= ~(1<<ICIE1);
    
    state = TCCR1B & (1<<ICES1);
    
    //Toggle interrupt to detect falling/rising edge:
    TCCR1B ^= (1<<ICES1);
    
    // Read the time-value stored in ICR1 register (will be the time copied from TCNT1 at input-capture event). 
    timeRead = ICR1;    
    
    pulseTime= timeRead; 
    
    // Check if the timer have reached top/started over:
    if (lastTime > pulseTime) {
       pulseTime += (TOP-lastTime); 
    }
    
    else {
      // Substract last time to get the time:
      pulseTime -= lastTime;
    }
    
    // Save current timer-value to be used in next interrupt:
    lastTime = timeRead;
    
    // If we are detecting a PPM input signal
    detectPPM(); 
    
    //Enable interrupt again:
    TIMSK1 |= (1<<ICIE1);
    
  }
  
  
  /*
  
  // Interrupt used for pin-change interrupt:
void pinChangeInterrupt() {

  // Read timer as quick as possible, as it's still counting. 
 timeRead = TCNT1; 
 
 // Check if the signal is high or low (alternative one could toggle between detecting falling and rising edge (like used in input-capture)
 state = digitalRead(2); 
 
  pulseTime= timeRead; 
    
    // Check if the timer have reached top/started over:
    if (lastTime > pulseTime) {
         pulseTime += (TOP-lastTime); 
    }
    
    else {
        // Substract last time to get the time:
        pulseTime -= lastTime;
    }
    
    // Save this time to be used in next interrupt:
    lastTime = timeRead;
    
    // Used detected time to calculate PPM-signal
    detectPPM();  
 
}  
  
  
 
*/
