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

//// FUNCTION IMPLEMENTATION

void app_init() {
    g_matrix_buf[0] |= (0x1 << 0);
	g_matrix_buf[0] |= (0x1 << 1);
    //g_matrix_buf[1] |= (0x1 << 0);
	g_matrix_buf[1] |= (0x1 << 1);
	g_matrix_buf[2] |= (0x1 << 0);
}

void app_loop() {
    while (1) {
        
    }
}

int* get_matrix_buf() {
    int* ret = (void*)0;
    if (!g_matrix_buf_lock) {
        ret = g_matrix_buf;
    }
    return ret;
}
