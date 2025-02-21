/**
 * @file q_learning.h
 * @authors Aymen T
 * @brief Header-file with overview of q-learning functions
 * @date 2022-05-21
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef H_Q_LEARNING
#define H_Q_LEARNING

#include "util.h"

#define EPSILON 0.3
#define GAMMA 0.99
#define ALPHA 0.5
#define RAND_ITERATIONS 200

#define STATES 4
#define ACTIONS 4

#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3

#define INVALID_ACTION 0
#define VALID_ACTION 1

#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3

#define STANDING_STILL_DEC 3 // by how much to decrement when stood still
#define BIG_REWARD 150
#define BIG_PUNISHMENT -100
/**
 * @brief Struct with the characteristics of a q-table
 * 
 */
typedef struct q_table {
    float table[STATES][STATES][ACTIONS];
    char action;
    char random_action;     // 0 if current action is not random, 1 if it is
    char raw_reward;        // raw reward is capped between [-127, 127] (signed char)
    int final_reward;       // the final reward is the result of processing raw_reward in the function calculate_reward()
    unsigned char current_state_a; // states assumed between 1 and 255, so a char will suffice
    unsigned char current_state_b;
    unsigned char old_state_a; 
    unsigned char old_state_b;
    unsigned int iteration; // has to be positive
    } q_table;
/**
 * @brief Updating qtable with by replacing the old value by the new calculated value.
 * 
 * @param qtable 
 */
void update_qtable(q_table* qtable);
/**
 * @brief Performs newest action on current state pair or perform random action when an invalid action has been chosen previously
 * 
 * @param qtable 
 */
void perform_qtable_action(q_table* qtable);
/**
 * @brief Placing the reward in the q-table
 * 
 * @param qtable 
 */
void process_qtable_reward(q_table* qtable);
/**
 * @brief Computing the value of the epsilon-parameter used in the q-algorithm
 * 
 * @param qtable 
 */
void perform_epsilon_greedy(q_table* qtable);
/**
 * @brief Initialise q-table
 * 
 * @param qtable 

 */
void init_qtable(q_table* qtable);
/**
 * @brief Conversion of an action into a new state
 * 
 * @param state_a 
 * @param state_b 
 * @param action 
 * @return char 
 */
char action_to_states(char* state_a, char* state_b, const char action);
/**
 * @brief Determining the highest possible value in the table
 * 
 * @param qtable 
 * @param state_a 
 * @param state_b 
 * @return float 
 */
float highest_q_value(q_table* qtable, char state_a, char state_b);
void process_raw_reward_qtable(q_table* qtable);
void check_if_valid_action(q_table* qtable);
int isValidState(unsigned char state);

int isValidStates(unsigned char state_a, unsigned char state_b);

void action_to_states(unsigned char *state_a, unsigned char *state_b, int action);

float largest_q_value(q_table* qtable, unsigned char state_a, unsigned char state_b);
float look_forward(q_table* qtable, unsigned char state_a, unsigned char state_b) ;



int getRandomAction(unsigned char state_a, unsigned char state_b);


float largest_q_value(q_table* qtable, char state_a, char state_b);

float look_forward(q_table* qtable, char state_a, char state_b);



int getRandomAction(char state_a, char state_b);

#endif
