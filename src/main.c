/**
 * @file main.c
 * @authors Aymen T
 * @brief Code belonging to Ingenieursproject II, Ghent University
 * @date 2022-05-21
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "servo.h"
#include "encoder.h"
#include "q_learning.h"
#include "global.h"
#include "util.h"


/**
 * @brief The main-function of this code for executing the algorithm of this project:
 * Initialise sensors, timers and q-table,
 * Performing the q-algorithm by calculations, moving the motors
 * @return int 
 */
int main(void) {
    setup_encoder_sensor();
    setup_servos();
    setup_delay_timer(); 

    q_table qtable;
    init_qtable(&qtable, 10, 99, 50, 10, -10);

    ENABLE_INTERRUPTS;
    for(;;) { 
        etup_encoder_sensor();
    set_random_seed();
    //setup_servos(4, 0, 0, 0);
    setup_delay_timer(); 
    init_servos();
    q_table qtable;
    init_qtable(&qtable, 10, 99, 50, 10, -10);
    DDRA = 0xFF;
    PORTA = 0x00;
    
    set_bit(SREG, SREG_I);
    //ENABLE_INTERRUPTS;
    char k = 0;
    for(;;) { 
        DISABLE_ENCODER;
   
        choose_next_action(&qtable);
       

  
        check_if_valid_action(&qtable);
       

     
        encoder.value = 0;
        interpolation_and_reward(qtable.state_a_now, qtable.state_b_now, qtable.state_a_now, qtable.state_b_now, qtable.action, 2);
      
        moveServos(qtable.state_a_now, qtable.state_b_now);
        qtable.raw_reward = encoder.value;
   
        process_raw_reward_qtable(&qtable);

        

        update_q_table(&qtable);

    }
}
