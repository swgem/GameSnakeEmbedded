/*
 * AppCore.c
 *
 *  Created on: 28 de ago de 2022
 *      Author: eric_
 */

#include "AppCore.h"

//// INTERNAL MACRO

#define COL_LENGTH 10
#define ROW_LENGTH 10

//// INTERNAL VARIABLE

static int g_matrix_buf_lock = 0; // cannot get matrix when '1'
static int g_matrix_buf[COL_LENGTH] = {0}; // column pin is represented as a single bit

static SYS_EVENT g_event = SYS_EVENT_NONE;

//// INTERNAL FUNCTION DECLARATION

static void swap_led_example();

//// FUNCTION IMPLEMENTATION

void app_init() {
    //g_matrix_buf[0] |= (0x1 << 0);
	//g_matrix_buf[0] |= (0x1 << 1);
}

void app_loop() {
    while (1) {
        switch(g_event) {
            case SYS_EVENT_NONE:
                break;
            case SYS_EVENT_TIMER_300_MSEC:
                g_event = SYS_EVENT_NONE;
                swap_led_example();
                break;
            default:
                break;
        }
    }
}

static void swap_led_example() {
    static int st = 0;
    if (st == 0) {
        g_matrix_buf[0] = 0b10101;
        g_matrix_buf[1] = 0b01010;
        g_matrix_buf[2] = 0b10101;
        g_matrix_buf[3] = 0b01010;
        g_matrix_buf[4] = 0b10101;

        st = 1;
    }
    else {
        g_matrix_buf[0] = 0b01010;
        g_matrix_buf[1] = 0b10101;
        g_matrix_buf[2] = 0b01010;
        g_matrix_buf[3] = 0b10101;
        g_matrix_buf[4] = 0b01010;

        st = 0;
    }
}

int* get_matrix_buf() {
    int* ret = (void*)0;
    if (!g_matrix_buf_lock) {
        ret = g_matrix_buf;
    }
    return ret;
}

void push_event(SYS_EVENT ev) {
    g_event = ev;
}
