/**
 * @file q_learning.c
 * @authors Aymen T
 * @brief Code belonging to the execution of the q-algorithm
 * @date 2022-05-21
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "q_learning.h"
/**
 * @brief Initialise q-table
 * 
 * @param qtable 
 */
void init_qtable(q_table* qtable, int epsilon, int gamma, int alpha, int big_reward, int big_punish) {
    // initialise q table with 0's 
    int i; int j; int k;
    for (i = STATES - 1; i >= 0; --i) 
    {
        for (j = STATES - 1; j >= 0; --j) 
        {
            for (k = ACTIONS - 1; k >= 0; --k) 
            {
                qtable->table[i][j][k] = 0.0F;
            }
        }
    } 

    // initialise beginning state
    qtable->current_state_a = 0;
    qtable->current_state_b = 0;
    qtable->old_state_a = 0;
    qtable->old_state_b = 0;

    // initialise rewards
    qtable->raw_reward = 0;
    qtable->final_reward = 0;

    qtable->action = DOWN;
    qtable->random_action = 0;
    qtable->iteration = 0;
}

int isValidState(unsigned char state) {
  if (state >= 0 && state < STATES) {
    return 1;
  }
  return 0;
}


int isValidStates(unsigned char state_a, unsigned char state_b) { 
  if (isValidState(state_a) && isValidState(state_b)) { 
    return 1;
  }
  else {
    return 0;
  }
}

void action_to_states(unsigned char *state_a, unsigned char *state_b, int action) {
  switch(action) {
    case UP:
      *state_a -= 1;
      break;
    case DOWN:
      *state_a += 1;            
      break;
    case LEFT:
      *state_b -= 1;          
      break;
    case RIGHT:
      *state_b += 1;
      break;
  }
}
/* q_waarde aan te passen nr 1e, anders lukken negatieve niet */
float largest_q_value(q_table* qtable, unsigned char state_a, unsigned char state_b) {
  float q_waarde = -1000.0;
  for (int action_t = 0; action_t < ACTIONS; action_t++) {
    if (qtable->table[state_a][state_b][action_t] > q_waarde) {
      q_waarde = qtable->table[state_a][state_b][action_t];
    }
  }
  return q_waarde; 
}

float look_forward(q_table* qtable, unsigned char state_a, unsigned char state_b) {
  float q_waarde = -1000.0;
  float q_temp = 0.0;
  unsigned char state_a_old = state_a;
  unsigned char state_b_old = state_b;
  for (int action = 0; action < ACTIONS; action++) {
    state_a_old = state_a; state_b_old = state_a;
    action_to_states(&state_a, &state_b, action);
    if (isValidStates(state_a, state_b)) {
      q_temp = largest_q_value(qtable, state_a, state_b);
      if (q_temp > q_waarde) {
        q_waarde = q_temp;
      }
    }
    state_a = state_a_old;
    state_b = state_b_old;
  }
  return q_waarde;
}



int getRandomAction(unsigned char state_a, unsigned char state_b) {
    int flag = 0;
    int action = 0; 
    unsigned char x = 0; unsigned char y = 0;
    do {
        action = rand()%4;
        x = state_a; y = state_b;
        action_to_states(&state_a, &state_b, action);
        if (isValidStates(state_a, state_b)) {
            flag = 1;
        }
        else {
            state_a = x;
            state_b = y;
        }
    } while (flag == 0);
    return action;
}

/* q_waarde aan te passen nr 1e, anders lukken negatieve niet */
float largest_q_value(q_table* qtable, char state_a, char state_b) {
  float q_waarde = -1000.0;
  for (int action_t = 0; action_t < ACTIONS; action_t++) {
    if (qtable->table[state_a][state_b][action_t] > q_waarde) {
      q_waarde = qtable->table[state_a][state_b][action_t];
    }
  }
  return q_waarde; 
}

float look_forward(q_table* qtable, char state_a, char state_b) {
  float q_waarde = -1000.0;
  float q_temp = 0.0;
  int state_a_old = state_a;
  int state_b_old = state_b;
  for (int action = 0; action < ACTIONS; action++) {
    state_a_old = state_a; state_b_old = state_a;
    action_to_states(&state_a, &state_b, action);
    if (isValidStates(state_a, state_b)) {
      q_temp = largest_q_value(qtable, state_a, state_b);
      if (q_temp > q_waarde) {
        q_waarde = q_temp;
      }
    }
    state_a = state_a_old;
    state_b = state_b_old;
  }
  return q_waarde;
}



int getRandomAction(char state_a, char state_b) {
    int flag = 0;
    int action = 0; 
    char x = 0; char y = 0;
    do {
        action = rand()%4;
        x = state_a; y = state_b;
        action_to_states(&state_a, &state_b, action);
        if (isValidStates(state_a, state_b)) {
            flag = 1;
        }
        else {
            state_a = x;
            state_b = y;
        }
    } while (flag == 0);
    return action;
}
void choose_next_action(q_table* qtable) {
    int t = rand() % 100;
    if  (t > (1-EPSILON)*100   || qtable->iteration < RAND_ITERATIONS) {
        qtable->action = getRandomAction(qtable->state_a_now, qtable->state_b_now);
        qtable->random_action = 1;
    }  
    else {
        int action_t = 0;
        qtable->random_action = 0;
        float q_waarde = -1000.0;
        for (action_t = 0; action_t < 4; action_t++) {
            if (qtable->table[qtable->state_a_now][qtable->state_b_now][action_t] > q_waarde) {
                q_waarde = qtable->table[qtable->state_a_now][qtable->state_b_now][action_t];
                qtable->action = action_t;
            }
        } 
    }
}

void check_if_valid_action(q_table* qtable) {
    action_to_states(&qtable->state_a_now, &qtable->state_b_now, qtable->action);
    new_random_action:
    if (!isValidStates(qtable->state_a_now, qtable->state_b_now)) {
        qtable->state_a_now = qtable->state_a, qtable->state_b_now = qtable->state_b;
        qtable->action = getRandomAction(qtable->state_a_now, qtable->state_b_now);
        qtable->random_action = 1;
        action_to_states(&qtable->state_a_now, &qtable->state_b_now, qtable->action);
        if (!isValidStates(qtable->state_a_now, qtable->state_b_now)) {
            goto new_random_action;
        }
    }
}

void process_raw_reward_qtable(q_table* qtable) {
    qtable->final_reward = qtable->raw_reward;
    if (qtable->raw_reward == 0) {
        qtable->final_reward = -4;
    }
    else if (qtable->raw_reward > 10) {
        qtable->final_reward = 100;
    }
    else if(qtable->raw_reward > 0) {
        qtable->final_reward = qtable->raw_reward * qtable->raw_reward;
    }
    else if (qtable->raw_reward < -7) {
        qtable->final_reward = -100;
    }
}

void update_q_table(q_table* qtable) {
    float max_future_q = look_forward(qtable, qtable->state_a_now, qtable->state_b_now);
    float deel_1 = (1-ALPHA) * qtable->table[qtable->state_a][qtable->state_b][qtable->action];
    float deel_2 = ALPHA * (qtable->final_reward + GAMMA * max_future_q);
    qtable->table[qtable->state_a][qtable->state_b][qtable->action] = deel_1 + deel_2;

    qtable->state_a = qtable->state_a_now; 
    qtable->state_b = qtable->state_b_now;

    qtable->iteration++;
}
