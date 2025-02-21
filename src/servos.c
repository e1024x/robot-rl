/**
 * @file servos.c
 * @authors Aymen T
 * @brief Setup timers and code for the motors
 * @date 2022-05-21
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "servo.h"


void moveServos(char state_a, char state_b) {
    OCR1A = waarden_servo_A[state_a];
    OCR1B = waarden_servo_B[state_b];
}

void delay(int max_ticks) {
    start_counting();
    toggle_led(PA7);
    while (get_ticks() < max_ticks);
    //stop_counting();
    toggle_led(PA7);
}

void start_counting() {
    counter_ticks.active = 1;
    counter_ticks.ticks = 0;
}

void stop_counting() {
    counter_ticks.active = 0;
}


unsigned char get_ticks() {
    return counter_ticks.ticks;
}

void setup_servos(char steps) { 
    
    servos.delta_a = delta_A;
    servos.delta_b = delta_B;
    servos.steps = steps;
    servos.delta_a_step = servos.delta_a / steps;
    servos.delta_b_step = servos.delta_b / steps;

    counter_ticks.active = 0;
    counter_ticks.ticks = 0;

    //ICR1 = 15999; // 8 ms breedte
    ICR1 = 39999; // 4 ms breedte
    //ICR1 = 39999; // 20 ms breedte
    TCNT1 = 0;
    set_bit(TCCR1A,COM1A1);   /* clear OC1A op compare en set wanneer top wordt bereikt */
    clear_bit(TCCR1A,COM1A0);
    set_bit(TCCR1A,COM1B1);   /* clear OC1B op compare en set wanneer top wordt bereikt */
    clear_bit(TCCR1A,COM1B0);

    set_bit(TCCR1B,WGM13);    /* komt overeen met 1110 fast pwm waarbij de top waarde in het ICR1 register zit        */
    set_bit(TCCR1B,WGM12);    /* en de waarde waarmee wordt vergeleken (CTC) in het OCR1A register zit. daardoor      */
    set_bit(TCCR1A,WGM11);    /*   kunnen we vlot veranderen tussen pulsbreedtes door te kijken naar de flag die wordt*/
    clear_bit(TCCR1A,WGM10);    /*  gezet wanneer top wordt bereikt, op dat moment kunnen we via interrupt CTC updaten  */

    clear_bit(TCCR1B,CS12);     /* prescaler op 8 */
    set_bit(TCCR1B,CS11);
    clear_bit(TCCR1B,CS10);

    set_bit(TIMSK1, TOIE1);   /* activeren van TOV1 interrupt */

    set_bit(TIMSK1, OCIE1A); 
    set_bit(TIMSK1, OCIE1B);

    PORTC |= _BV(PC1);
    PORTC |= _BV(PC0);
    DDRB = 0xFF;     /* zet de DDR_OC1A bits op 1 zodat de output zichtbaar is op poort B */

    EIMSK |= _BV(INT1);
}

ISR(TIMER1_COMPA_vect) {
    PORTC &= ~_BV(PC0);
}

ISR(TIMER1_COMPB_vect) {
    PORTC &= ~_BV(PC1);
}

ISR(TIMER1_OVF_vect) {
    PORTC |= _BV(PC0);
    PORTC |= _BV(PC1); 
    if(counter_ticks.active) {
        counter_ticks.ticks++;
    } 
}


void move_servos_and_interpolate(int state_a_now, int state_b_now, int state_b, int state_a, int action, int use_sinus) {
    set_bit(EIMSK, INT0);
    for (int i = 0; i < servos.steps + 1; i++) {
        if (action == INTERPOL_DOWN) {OCR1A += servos.delta_a_step;}
        else if (action == INTERPOL_UP) {OCR1A -= servos.delta_a_step;}
        else if (action == INTERPOL_LEFT) {OCR1B -= servos.delta_b_step;}
        else if (action == INTERPOL_RIGHT) {OCR1B += servos.delta_b_step;}
        delay(use_sinus);
    }
    delay(20);
    clear_bit(EIMSK, INT0);
}
