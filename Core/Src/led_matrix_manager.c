/*
 * led_matrix_manager.c
 *
 *  Created on: 11 de set de 2022
 *      Author: eric_
 */

#include "main.h"
#include "stm32f1xx_it.h"
#include "led_matrix_manager.h"
#include "hw_manager.h"

//// INTERNAL MACRO

#define COL_LENGTH 10
#define ROW_LENGTH 10

//// INTERNAL VARIABLE

static int g_curr_col = 0;
static int g_led_matrix[COL_LENGTH] = {0}; // row pin is represented as a single bit

//// INTERNAL FUNCTION DECLARATION

__STATIC_FORCEINLINE void leds_set_all_lpins();
__STATIC_FORCEINLINE void print_matrix(int curr_row);

//// FUNCTION IMPLEMENTATION

__STATIC_FORCEINLINE void leds_set_all_lpins() {
    hw_set_pin(HW_PIN_OUT_L0);
    hw_set_pin(HW_PIN_OUT_L1);
    hw_set_pin(HW_PIN_OUT_L2);
    hw_set_pin(HW_PIN_OUT_L3);
    hw_set_pin(HW_PIN_OUT_L4);
    hw_set_pin(HW_PIN_OUT_L5);
    hw_set_pin(HW_PIN_OUT_L6);
    hw_set_pin(HW_PIN_OUT_L7);
    hw_set_pin(HW_PIN_OUT_L8);
    hw_set_pin(HW_PIN_OUT_L9);
}

__STATIC_FORCEINLINE HW_PIN get_row_pin(int row) {
    return (HW_PIN)row;
}

__STATIC_FORCEINLINE HW_PIN get_col_pin(int col) {
    return (HW_PIN)(col + ROW_LENGTH);
}

__STATIC_FORCEINLINE void print_matrix(int curr_col) {
    // Reset only current col
    leds_set_all_lpins();
    hw_reset_pin(get_col_pin(curr_col));

    // Set active columns from current col
    for (int i = 0; i < ROW_LENGTH; i++) {
        (g_led_matrix[curr_col] & (0x1 << i)) ?
            hw_set_pin(get_row_pin(i)) : hw_reset_pin(get_row_pin(i));
    }
}

void run_leds_state_machine() {
    print_matrix(g_curr_col);

    if (++g_curr_col >= COL_LENGTH) {
        g_curr_col = 0;
    }
}

void set_led_matrix(const int buf[]) {
    for (int i = 0; i < ROW_LENGTH; i++) {
        g_led_matrix[i] = buf[i];
    }
}
