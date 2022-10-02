/*
 * AppCore.c
 *
 *  Created on: 28 de ago de 2022
 *      Author: eric_
 */

#include "AppCore.h"
#include <stdint.h>
#include "GameConfig.h"
#include "GameController.h"
#include "Tools.h"

//// INTERNAL MACRO

#define COL_LENGTH 5
#define ROW_LENGTH 5
#define MEM_BLOCK_SIZE 32 // byte (must be multiple of 4)
#define MEM_BUF_SIZE (COL_LENGTH * ROW_LENGTH) // number of blocks
#define EVENT_BUF_SIZE 10

//// INTERNAL STRUCT

typedef struct {
    int32_t data[MEM_BLOCK_SIZE / 4];
} MEM_BLOCK;

//// INTERNAL VARIABLE

static MEM_BLOCK g_mem_buf[MEM_BUF_SIZE] = { 0 };
static int g_mem_buf_availability[MEM_BUF_SIZE] = { 0 }; // Content indicates number of following
                                                         // continuous memory allocated

static int g_matrix_buf_lock = 0; // cannot get matrix when '1'
static int g_matrix_buf[COL_LENGTH] = {0}; // column pin is represented as a single bit

static int g_new_event = 0;
static SYS_EVENT g_event_buf[EVENT_BUF_SIZE] = { SYS_EVENT_NONE };

static int g_blink_food = 0;

//// INTERNAL FUNCTION DECLARATION

static void system_fatal_impl();
static void* mem_alloc_impl(int size);
static int generate_random_impl();
static void mem_free_impl(void* addr);

static void refresh_buf();

//// FUNCTION IMPLEMENTATION

void app_init() {
    set_game_config(100, COL_LENGTH, ROW_LENGTH, 10000, 3, 1, 2, 2, MOVEMENT_DIRECTION_RIGHT);
    set_system_fatal_func(system_fatal_impl);
    set_mem_alloc_func(mem_alloc_impl);
    set_generate_random_func(generate_random_impl);
    set_mem_free_func(mem_free_impl);

    game_restart();
}

void app_loop() {
    while (1) {
        if (g_new_event) {
            SYS_EVENT ev = pop_event();
            switch(ev) {
                case SYS_EVENT_NONE:
                    break;
                case SYS_EVENT_TIMER_100_MSEC:
                    game_run();
                    refresh_buf();
                    break;
                case SYS_EVENT_TIMER_250_MSEC:
                    g_blink_food = (g_blink_food) ? 0 : 1;
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
}

static void system_fatal_impl() {
    while (1);
}

static void* mem_alloc_impl(int size) {
    void* ret = (void*)0;

    if (size > 0) {
        // Find available continuous memory space
        int block_number = (size + (MEM_BLOCK_SIZE - 1)) / MEM_BLOCK_SIZE; // round up
        for (int i = 0; i < MEM_BUF_SIZE; i++) {
            int block_count = 0;
            for (int j = 0; j < block_number; j++) {
                if (g_mem_buf_availability[i + j] == 0) {
                    block_count++;
                }
                else {
                    i += block_count + (g_mem_buf_availability[i + j] - 1); // no need to recheck blocks
                    break;
                }
                if ((block_count == block_number) && ((i + j) < MEM_BUF_SIZE)) {
                    ret = &g_mem_buf[i];
                }
            }

            // If found enough space, reserve them and leave
            if (ret != (void*)0) {
                for (int j = 0; j < block_number; j++) {
                    g_mem_buf_availability[i + j] = block_number - j;
                }
                break;
            }
        }
    }

    return ret;
}

static int generate_random_impl() {
    static int i = 0;
    i++;
    return i;
}

static void mem_free_impl(void* addr) {
    for (int i = 0; i < MEM_BUF_SIZE; i++) {
        if (&g_mem_buf[i] == addr) {
            int count = g_mem_buf_availability[i];
            for (int j = 0; j < count; j++) {
                g_mem_buf_availability[i + j] = 0;
            }
        }
    }
}

static void refresh_buf() {
    const SNAKE* snake = get_snake();
    const FOOD* food = get_food();

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

    // Print food
    if (g_blink_food) {
        g_matrix_buf[food->pos_x] |= 0x1 << food->pos_y;
    }

    // Unlock resource
    g_matrix_buf_lock = 0;
}

int* get_matrix_buf() {
    int* ret = (void*)0;
    if (!g_matrix_buf_lock) {
        ret = g_matrix_buf;
    }
    return ret;
}

void push_event(SYS_EVENT ev) {
    for (int i = 0; i < EVENT_BUF_SIZE; i++) {
        if (g_event_buf[i] == SYS_EVENT_NONE) {
            g_event_buf[i] = ev;
            break;
        }
    }
    g_new_event = 1;
}

SYS_EVENT pop_event() {
    SYS_EVENT ret = g_event_buf[0];
    
    for (int i = 1; i < EVENT_BUF_SIZE; i++) {
        g_event_buf[i - 1] = g_event_buf[i];
        if (g_event_buf[i] == SYS_EVENT_NONE) {
            break;
        }
    }

    g_event_buf[EVENT_BUF_SIZE - 1] = SYS_EVENT_NONE;
    if (g_event_buf[0] == SYS_EVENT_NONE) g_new_event = 0;
    
    return ret;
}
