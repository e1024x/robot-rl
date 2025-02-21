/**
 * @file delay.c
 * @authors Aymen T
 * @brief File for setup delays and timers
 * @date 2022-05-21
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "delay.h"

#define ENABLE_DELAY_TIMER (EIMSK |= _BV(INT3))
#define DISABLE_DELAY_TIMER (EIMSK &= ~_BV(INT3))

delay current_delay; // global struct containing current delay info
/**
 * @brief Construct a new ISR object
 * 
 */
ISR(TIMER2_OVF_vect) {
    if (current_delay.ticks != 0) {current_delay.ticks--;} // most occuring
    else {current_delay.state &= ~_BV(DELAY_STATUS);} 
}
/**
 * @brief Set the up delay timer object
 * 
 */
void setup_delay_timer() {
    // no prescaler, every 32ms a tick (max delay 2^6 * 32 ms == 2 seconds)
    clear_bit(TCCR1B,CS12);     
    set_bit(TCCR1B,CS11);
    clear_bit(TCCR1B,CS10);

    // normal mode
    clear_bit(TCCR3B,WGM13);    
    clear_bit(TCCR3B,WGM12);    
    clear_bit(TCCR3A,WGM11);    
    clear_bit(TCCR3A,WGM10);  
}
/**
 * @brief Setup timer_delay
 * 
 * @param ticks 
 */
void timer_delay(char ticks) { 
    current_delay.ticks = ticks;
    current_delay.state |= _BV(DELAY_STATUS);
    ENABLE_DELAY_TIMER;
    while(!(current_delay.state & _BV(DELAY_STATUS)));
    DISABLE_DELAY_TIMER;
}