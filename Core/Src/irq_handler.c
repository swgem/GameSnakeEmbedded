/*
 * irq_handler.c
 *
 *  Created on: 11 de set de 2022
 *      Author: eric_
 */

#include "main.h"
#include "stm32f1xx_it.h"
#include "hw_manager.h"
#include "led_matrix_manager.h"
#include "AppCore.h"

//// INTERNAL MACRO

#define FRAME_RATE 10 // fps

//// INTERNAL FUNCTION DECLARATION

static void update_led_matrix();

//// OVERWRITE FUNCTION IMPLEMENTATION

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
    switch (hw_input_pin(GPIO_Pin)) {
        case HW_PIN_IN_B0:
            push_event(SYS_EVENT_CHANGE_DIRECTION_UP);
            break;
        case HW_PIN_IN_B1:
            push_event(SYS_EVENT_CHANGE_DIRECTION_DOWN);
            break;
        case HW_PIN_IN_B2:
            push_event(SYS_EVENT_CHANGE_DIRECTION_RIGHT);
            break;
        case HW_PIN_IN_B3:
            push_event(SYS_EVENT_CHANGE_DIRECTION_LEFT);
            break;
        default:
            break;
    }
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
    static int tick_count0 = 0;
    static int tick_count1 = 0;
    static int tick_count2 = 0;
    if (htim == hw_main_timer()) {
        run_leds_state_machine(); // must run every 1ms

        if (++tick_count0 >= (1000 / FRAME_RATE)) {
            tick_count0 = 0;
            update_led_matrix();
        }

        if (++tick_count1 >= 100) {
            tick_count1 = 0;
            push_event(SYS_EVENT_TIMER_100_MSEC);
        }

        if (++tick_count2 >= 250) {
            tick_count2 = 0;
            push_event(SYS_EVENT_TIMER_250_MSEC);
        }
    }
}

//// FUNCTION IMPLEMENTATION

static void update_led_matrix() {
    int* buf = get_matrix_buf();
    if (buf != (void*)0) {
        set_led_matrix(buf);
    }
}
