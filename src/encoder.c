/**
 * @file encoder.c
 * @authors Aymen T
 * @brief Setup timers and interrupts for sensors
 * @date 2022-05-21
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "encoder.h"

encoder_info encoder; // global struct containing the previous 2 pins, the current 2 pins (PIN D 1, PIN D 0), and the pulses counted
/**
 * @brief Construct a new ISR object
 * 
 */
ISR(INT0_vect){
    const char encoder_output[15] = {0, 1, -1, 0, -1, 0, 0, 1, 1, 0, 0, -1, 0, -1, 1};
    encoder.current = (PIND&3);
    unsigned char test = ((encoder.previous<<2) | encoder.current);
    if(encoder_output[test] == 1){
        if (encoder.value < 127) {
            encoder.value++;
        } 
    }
    else if (encoder_output[test] == -1 ) {
        if (encoder.value > -127) { /* char 8 bits */
            encoder.value--;
        }
    }      
    encoder.previous = encoder.current;
}
/**
 * @brief Setup timing for calculating the reward of the robot
 * 
 * @return char 
 */
char calculate_raw_reward() {
    encoder.value = 0;
    ENABLE_ENCODER;
    timer_delay(100); // delay for 20 * 32 ms, this is for how long we will be calculating reward for 
    DISABLE_ENCODER;
    return encoder.value;
}   
/**
 * @brief Set the up encoder sensor object
 * 
 */
void setup_encoder_sensor() {
    DDRD |= _BV(DDD0);
    DDRD |= _BV(DDD1);
    PORTD = _BV(PD0)|_BV(PD1);
    EICRA &= ~_BV(ISC01); // falling en rising edge
    EICRA |= _BV(ISC00);
    encoder.current = 0; 
    encoder.previous = 0;
    encoder.value = 0;
}
