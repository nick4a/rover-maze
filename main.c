#define F_CPU 1000000UL
#include "motor.c"
#include "qtr_driver.c"

int main() {
  init_motors ();
  init_QTR_driver();
  
  DDRC = 0xFF;
  
  while (1) { 
    
    unsigned char checkSensorValue = get_QTR_value() & 0x03;
    
    if(checkSensorValue == 0x00){
      leftmotor_forward();
      rightmotor_reverse();
      _delay_ms(1);
      leftmotor_brake();
      rightmotor_brake();
      _delay_ms(1);  
     }
    else if(checkSensorValue == 0x01){
      leftmotor_forward();
      rightmotor_forward();
      _delay_ms(1);
      leftmotor_brake();
      rightmotor_brake();
      _delay_ms(1);
    }
    else if(checkSensorValue == 0x02){
        leftmotor_reverse();
        rightmotor_forward();
        _delay_ms(1);
        leftmotor_brake();
        rightmotor_brake();
        _delay_ms(1);
    }
    else if(checkSensorValue == 0x03){
      leftmotor_reverse();
      rightmotor_forward();
      _delay_ms(2);
      leftmotor_brake();
      rightmotor_brake();
      _delay_ms(1);
    }
    return 0;
}
