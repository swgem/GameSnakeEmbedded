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

__STATIC_FORCEINLINE void leds_reset_all_hpins();
__STATIC_FORCEINLINE void print_matrix();

//// FUNCTION IMPLEMENTATION

__STATIC_FORCEINLINE void leds_reset_all_hpins() {
    hw_reset_pin(HW_PIN_OUT_H0);
    hw_reset_pin(HW_PIN_OUT_H1);
    hw_reset_pin(HW_PIN_OUT_H2);
    hw_reset_pin(HW_PIN_OUT_H3);
    hw_reset_pin(HW_PIN_OUT_H4);
    hw_reset_pin(HW_PIN_OUT_H5);
    hw_reset_pin(HW_PIN_OUT_H6);
    hw_reset_pin(HW_PIN_OUT_H7);
    hw_reset_pin(HW_PIN_OUT_H8);
    hw_reset_pin(HW_PIN_OUT_H9);
}

__STATIC_FORCEINLINE HW_PIN get_row_pin(int row) {
    return (HW_PIN)(row + COL_LENGTH);
}

__STATIC_FORCEINLINE HW_PIN get_col_pin(int col) {
    return (HW_PIN)col;
}

__STATIC_FORCEINLINE void print_matrix() {
    // Set only current column
    leds_reset_all_hpins();
    hw_set_pin(get_col_pin(g_curr_col));

    // Reset active rows from current column
    for (int i = 0; i < ROW_LENGTH; i++) {
        (g_led_matrix[g_curr_col] & (0x1 << i)) ?
            hw_reset_pin(get_row_pin(i)) : hw_set_pin(get_row_pin(i));
    }
}

void run_leds_state_machine() {
    print_matrix();

    if (++g_curr_col >= COL_LENGTH) {
        g_curr_col = 0;
    }
}

void set_led_matrix(const int buf[]) {
    for (int i = 0; i < COL_LENGTH; i++) {
        g_led_matrix[i] = buf[i];
    }
}
