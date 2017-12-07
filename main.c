#define F_CPU 1000000UL
#include "motor.c"
#include "qtr_driver.c"

int main() {
  init_motors ();
  init_QTR_driver();
  
  DDRC = 0xFF;
  
  while (1) { 
    
    unsigned char checkSensorValue = get_QTR_value() & 0x03;// will only use two least significant bits in binary which hold a maximum value of 3
    
    // sensor 1 refers to the sensor all the way on the right and sensor 2 refers to the sensor directly left of it
    
    if(checkSensorValue == 0x00){ // if both sensors read white the rover will turn right
      leftmotor_forward();
      rightmotor_reverse();
      _delay_ms(1);
      leftmotor_brake();
      rightmotor_brake();
      _delay_ms(1);  
     }
    else if(checkSensorValue == 0x01){ // if sensor 1 reads black and sensor 2 reads white the rover will move forward
      leftmotor_forward();
      rightmotor_forward();
      _delay_ms(1);
      leftmotor_brake();
      rightmotor_brake();
      _delay_ms(1);
    }
    else if(checkSensorValue == 0x02){ // if sensor 1 reads white and sensor 2 reads black the rover will turn to the left
        leftmotor_reverse();
        rightmotor_forward();
        _delay_ms(1);
        leftmotor_brake();
        rightmotor_brake();
        _delay_ms(1);
    }
    else if(checkSensorValue == 0x03){ // if both sensors read black the rover will turn to the left 
      leftmotor_reverse();
      rightmotor_forward();
      _delay_ms(2);
      leftmotor_brake();
      rightmotor_brake();
      _delay_ms(1);
    }
    return 0;
}
