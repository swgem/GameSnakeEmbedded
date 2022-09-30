/*
 * AppCore.c
 *
 *  Created on: 28 de ago de 2022
 *      Author: eric_
 */

#include "AppCore.h"
#include "GameConfig.h"
#include "GameController.h"
#include "Tools.h"

//// INTERNAL MACRO

#define COL_LENGTH 10
#define ROW_LENGTH 10

//// INTERNAL VARIABLE

static int g_matrix_buf_lock = 0; // cannot get matrix when '1'
static int g_matrix_buf[COL_LENGTH] = {0}; // column pin is represented as a single bit

static SYS_EVENT g_event = SYS_EVENT_NONE;

//// INTERNAL FUNCTION DECLARATION

// static void swap_led_example();

static void system_fatal_impl();
static void* mem_alloc_impl(int size);
static int generate_random_impl();
static void mem_free_impl(void* addr);

static void refresh_buf();

//// FUNCTION IMPLEMENTATION

void app_init() {
    set_game_config(100, 5, 5, 10000, 3, 1, 2, 2, MOVEMENT_DIRECTION_RIGHT);
    set_system_fatal_func(system_fatal_impl);
    set_mem_alloc_func(mem_alloc_impl);
    set_generate_random_func(generate_random_impl);
    set_mem_free_func(mem_free_impl);

    game_restart();

    //g_matrix_buf[0] |= (0x1 << 0);
	//g_matrix_buf[0] |= (0x1 << 1);
}

void app_loop() {
    while (1) {
        switch(g_event) {
            case SYS_EVENT_NONE:
                break;
            case SYS_EVENT_TIMER_100_MSEC:
                g_event = SYS_EVENT_NONE;
                game_run();
                refresh_buf();
                break;
            case SYS_EVENT_TIMER_250_MSEC:
                break;
            case SYS_EVENT_CHANGE_DIRECTION_UP:
                set_snake_direction(MOVEMENT_DIRECTION_UP);
                break;
            case SYS_EVENT_CHANGE_DIRECTION_DOWN:
                set_snake_direction(MOVEMENT_DIRECTION_DOWN);
                break;
            case SYS_EVENT_CHANGE_DIRECTION_RIGHT:
                set_snake_direction(MOVEMENT_DIRECTION_RIGHT);
                break;
            case SYS_EVENT_CHANGE_DIRECTION_LEFT:
                set_snake_direction(MOVEMENT_DIRECTION_LEFT);
                break;
            default:
                break;
        }
    }
}

static void system_fatal_impl() {
    while(1);
}

static void* mem_alloc_impl(int size) {
    static SNAKE_SEG buf[5];
    static int i = 0;
    void* ret = (void*)&buf[i];
    i++;
    return ret;
}

static int generate_random_impl() {
    static int i = 0;
    i++;
    return i;
}

static void mem_free_impl(void* addr) {
    
}

static void refresh_buf() {
    const SNAKE* snake = get_snake();

    // Make sure matrix is not being printed and then lock resource
    while (g_matrix_buf_lock);
    g_matrix_buf_lock = 1;

    // Clear current buffer
    for (int i = 0; i < COL_LENGTH; i++) {
        g_matrix_buf[i] = 0;
    }

    // Print snake
    g_matrix_buf[snake->head.pos_x] = 0x1 << snake->head.pos_y;
    SNAKE_SEG* iter = snake->head.next_seg;
    while (iter != (void*)0) {
        g_matrix_buf[iter->pos_x] |= 0x1 << iter->pos_y;
        iter = iter->next_seg;
    }

    // Unlock resource
    g_matrix_buf_lock = 0;
}

// static void swap_led_example() {
//     static int st = 0;
//     if (st == 0) {
//         g_matrix_buf[0] = 0b10101;
//         g_matrix_buf[1] = 0b01010;
//         g_matrix_buf[2] = 0b10101;
//         g_matrix_buf[3] = 0b01010;
//         g_matrix_buf[4] = 0b10101;

//         st = 1;
//     }
//     else {
//         g_matrix_buf[0] = 0b01010;
//         g_matrix_buf[1] = 0b10101;
//         g_matrix_buf[2] = 0b01010;
//         g_matrix_buf[3] = 0b10101;
//         g_matrix_buf[4] = 0b01010;

//         st = 0;
//     }
// }

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
