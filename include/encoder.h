/**
 * @file encoder.h
 * @authors Aymen T
 * @brief Header-file for functions about the sensors
 * @date 2022-05-21
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef H_ENCODER
#define H_ENCODER

#include "util.h"

#include "delay.h"

#define ENABLE_ENCODER (EIMSK |= _BV(INT0))
#define DISABLE_ENCODER (EIMSK &= ~_BV(INT0))
#define ENCODER_STATUS 0
/**
 * @brief Struct for encoder info
 * 
 */
typedef struct encoder_info {
    volatile uint16_t previous: 2;
    volatile uint16_t current: 2;
    volatile uint16_t value: 8;
} encoder_info;
/**
 * @brief overview output encoder
 * 
 */
const signed char encoder_output[16] PROGMEM = {
    0,  // 0    invalid
    -1, // 1,   0 0 0 1
    1,  // 2,   0 0 1 0
    0,  // 3,   invalid 
    1,  // 4,   0 1 0 0
    0,  // 5,   invalid
    0,  // 6,   invalid
    -1, // 7,   invalid
    -1, // 8,   1 0 0 0 
    0,  // 9,   invalid
    0,  // 10,  invalid
    0,  // 11,  invalid
    1,  // 12,  1 0 1 0
    1,  // 13,  1 0 1 1
    -1, // 14,  1 1 1 0
    0   // 15,  invalid
};
/**
 * @brief Signature for setup sensor
 * 
 */
void setup_encoder_sensor();
/**
 * @brief Signature for function that calculates the reward
 * 
 * @return char 
 */
char calculate_raw_reward();

#endif