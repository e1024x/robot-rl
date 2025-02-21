/**
 * @file servo.h
 * @authors Aymen T
 * @brief Headerfile with function for moving motors and interpolation
 * @date 2022-05-21
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef H_SERVO
#define H_SERVO

#include "util.h"
#include "global.h"
#include "encoder.h"

#define DELTA 5 // the delta for a given range of servo positions is stored as last element in servo_values_a, and servo_values_b
#define DELTA_A 600
#define DELTA_B 750
#define INTERPOL_STEPS 25

#define INTERPOL_UP 0
#define INTERPOL_DOWN 1
#define INTERPOL_LEFT 2
#define INTERPOL_RIGHT 3

#define INTERPOL_STATUS 0

/*
   calculated as (MAX-MIN)*(DEGREES/180) + MIN
   where max and min are calculated in function of the "top" value stored in ICR1
   top = every 20 ms in our case
*/
volatile int waarden_servo_A[5] = {2200, 3000, 3800, 4600};

volatile int delta_A = 800;
volatile int waarden_servo_B[5] = {1500, 2500, 3500, 4500};
volatile int delta_B = 1000;

/**
 * @brief Signature of functions used for the movement of the motors
 * 
 * @param action 
 */
void move_servos_and_interpolate(int state_a_now, int state_b_now, int state_b, int state_a, int action, int use_sinus);
void init_servos();

#endif
