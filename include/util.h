/**
 * @file util.h
 * @authors Aymen T
 * @brief Header-file for functions used to smiplify other functions in different files
 * @date 2022-05-21
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef H_UTIL
#define H_UTIL

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>

#define EPSILON_COMPARISON 0.001

#define set_bit(pattern, bit) (pattern |= bit)
#define clear_bit(pattern, bit) (pattern &= ~bit)

#define ENABLE_INTERRUPTS (EIMSK |= _BV(SREG_I))
#define DISABLE_INTERRUPTS (EIMSK &= ~_BV(SREG_I))

/**
 * @brief Function for calculating the maximum value of two or four floats
 * 
 */
float* max_2_floats(float* num_1, float* num_2);
float max_4_floats(float* num_1, float* num_2, float* num_3, float* num_4);
/**
 * @brief Signature for function that enables the working of a button
 * 
 */
void enable_push_button();

#endif