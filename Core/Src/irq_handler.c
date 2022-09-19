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

}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
    static int tick_count = 0;
    static int tick_count_sec = 0;
    if (htim == hw_main_timer()) {
        if (++tick_count >= (1000 / FRAME_RATE)) {
            tick_count = 0;
            update_led_matrix();
        }
        run_leds_state_machine();

        if (++tick_count_sec >= 300) {
            tick_count_sec = 0;
            push_event(SYS_EVENT_TIMER_300_MSEC);
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
