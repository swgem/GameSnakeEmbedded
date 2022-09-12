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

//// INTERNAL ENUM

typedef enum {
    LEDS_STATE_INIT = 0,
    LEDS_STATE_MACHINE_LINE_0,
    LEDS_STATE_MACHINE_LINE_1,
    LEDS_STATE_MACHINE_LINE_2,
    LEDS_STATE_MACHINE_LINE_3,
    LEDS_STATE_MACHINE_LINE_4,
    LEDS_STATE_MACHINE_LINE_5,
    LEDS_STATE_MACHINE_LINE_6,
    LEDS_STATE_MACHINE_LINE_7,
    LEDS_STATE_MACHINE_LINE_8,
    LEDS_STATE_MACHINE_LINE_9,

    LEDS_STATE_MACHINE_MAX = LEDS_STATE_MACHINE_LINE_9
} LEDS_STATE_MACHINE;

//// INTERNAL VARIABLE

static int state_curr = LEDS_STATE_INIT;

//// INTERNAL FUNCTION DECLARATION

static void leds_reset_all_hpins();
static void leds_set_all_lpins();

static void leds_state_machine_line_0();
static void leds_state_machine_line_1();
static void leds_state_machine_line_2();
static void leds_state_machine_line_3();
static void leds_state_machine_line_4();
static void leds_state_machine_line_5();
static void leds_state_machine_line_6();
static void leds_state_machine_line_7();
static void leds_state_machine_line_8();
static void leds_state_machine_line_9();

//// FUNCTION IMPLEMENTATION

void run_leds_state_machine() {
    state_curr++;
    if (state_curr > LEDS_STATE_MACHINE_MAX) {
        state_curr = LEDS_STATE_MACHINE_LINE_0;
    }

    switch(state_curr) {
    case LEDS_STATE_MACHINE_LINE_0:
        leds_state_machine_line_0();
    break;
    case LEDS_STATE_MACHINE_LINE_1:
        leds_state_machine_line_1();
    break;
    case LEDS_STATE_MACHINE_LINE_2:
        leds_state_machine_line_2();
    break;
    case LEDS_STATE_MACHINE_LINE_3:
        leds_state_machine_line_3();
    break;
    case LEDS_STATE_MACHINE_LINE_4:
        leds_state_machine_line_4();
    break;
    case LEDS_STATE_MACHINE_LINE_5:
        leds_state_machine_line_5();
    break;
    case LEDS_STATE_MACHINE_LINE_6:
        leds_state_machine_line_6();
    break;
    case LEDS_STATE_MACHINE_LINE_7:
        leds_state_machine_line_7();
    break;
    case LEDS_STATE_MACHINE_LINE_8:
        leds_state_machine_line_8();
    break;
    case LEDS_STATE_MACHINE_LINE_9:
        leds_state_machine_line_9();
    break;
    default:
        Error_Handler();
    break;
    }
}

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

__STATIC_FORCEINLINE void leds_state_machine_line_0() {
    leds_reset_all_hpins();
    hw_set_pin(HW_PIN_OUT_H0);
    hw_reset_pin(HW_PIN_OUT_L0);
}

__STATIC_FORCEINLINE void leds_state_machine_line_1() {
    leds_reset_all_hpins();
    hw_set_pin(HW_PIN_OUT_H1);
    hw_reset_pin(HW_PIN_OUT_L0);
}

__STATIC_FORCEINLINE void leds_state_machine_line_2() {
    leds_reset_all_hpins();
    hw_set_pin(HW_PIN_OUT_H2);
}

__STATIC_FORCEINLINE void leds_state_machine_line_3() {
    leds_reset_all_hpins();
    hw_set_pin(HW_PIN_OUT_H3);
}

__STATIC_FORCEINLINE void leds_state_machine_line_4() {
    leds_reset_all_hpins();
    hw_set_pin(HW_PIN_OUT_H4);
}

__STATIC_FORCEINLINE void leds_state_machine_line_5() {
    leds_reset_all_hpins();
    hw_set_pin(HW_PIN_OUT_H5);
}

__STATIC_FORCEINLINE void leds_state_machine_line_6() {
    leds_reset_all_hpins();
    hw_set_pin(HW_PIN_OUT_H6);
}

__STATIC_FORCEINLINE void leds_state_machine_line_7() {
    leds_reset_all_hpins();
    hw_set_pin(HW_PIN_OUT_H7);
}

__STATIC_FORCEINLINE void leds_state_machine_line_8() {
    leds_reset_all_hpins();
    hw_set_pin(HW_PIN_OUT_H8);
}

__STATIC_FORCEINLINE void leds_state_machine_line_9() {
    leds_reset_all_hpins();
    hw_set_pin(HW_PIN_OUT_H9);
}

