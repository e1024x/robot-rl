/**
 * @file delay.h
 * @authors Aymen T
 * @brief Headerfile with struct and function for setup of delay-timer
 * @date 2022-05-21
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef H_DELAY
#define H_DELAY

#include "util.h"

#define DELAY_STATUS 0
/**
 * @brief Struct used for delay
 * 
 */
typedef struct delay {
    volatile uint8_t state: 1;
    volatile uint8_t ticks: 7;
} delay;
/**
 * @brief Set the up delay timer object
 * 
 */
void setup_delay_timer();
#endif