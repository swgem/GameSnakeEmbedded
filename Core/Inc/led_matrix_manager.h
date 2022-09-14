/*
 * led_matrix_manager.h
 *
 *  Created on: 11 de set de 2022
 *      Author: eric_
 */

#ifndef INC_LED_MATRIX_MANAGER_H_
#define INC_LED_MATRIX_MANAGER_H_

//// EXTERNAL FUNCTION DECLARATION

void run_leds_state_machine();
int get_led_matrix_row_length();
int get_led_matrix_col_length();
void set_led_matrix(const int buf[]);

#endif /* INC_LED_MATRIX_MANAGER_H_ */
