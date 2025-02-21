/**
 * @file util.c
 * @authors Aymen T
 * @brief Overview of functions used to simplify other functions in different files
 * @date 2022-05-21
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "util.h"
/**
 * @brief Determine the maximum value of two floats
 * 
 * @param num_1 
 * @param num_2 
 * @return float* 
 */
float* max_2_floats(float* num_1, float* num_2) {
    if (fabsf(*num_1 - *num_2) > EPSILON_COMPARISON) {
        return num_1;
    }
    else {
        return num_2;
    }
}
/**
 * @brief Determine the maximum value of four floats
 * 
 * @param num_1 
 * @param num_2 
 * @param num_3 
 * @param num_4 
 * @return float 
 */
float max_4_floats(float* num_1, float* num_2, float* num_3, float* num_4) {
    float* max_value;
    max_value = max_2(max_2(num_1, num_2), 
                      max_2(num_3, num_4));
    return *max_value;
}
/**
 * @brief Setup for enabling pushing button on microcontroller
 * 
 */
void enable_push_button() {
    clear_bit(DDRE, PE5);
    set_bit(PORTE, PE5);

    set_bit(EIMSK, INT5); 

    clear_bit(EICRB, ISC50);
    set_bit(EICRB, ISC50);
    
    set_bit(PORTD, PD0);
    set_bit(PORTD, PD1);
}
