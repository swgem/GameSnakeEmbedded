/*
 * timer_handler.c
 *
 *  Created on: 28 de ago de 2022
 *      Author: eric_
 */

#include "hw_manager.h"
#include "timer_handler.h"
#include "main.h"
#include "stm32f1xx_it.h"

//// OVERWRITE FUNCTION IMPLEMENTATION

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if (htim == hw_main_timer()) {
        static int state_curr = 0;

        state_curr++;
        if (state_curr == 10) {
            state_curr = 0;
        }

        switch(state_curr) {
        case 0:
            hw_set_pin(HW_PIN_OUT_H0);
            hw_reset_pin(HW_PIN_OUT_H1);

            hw_reset_pin(HW_PIN_OUT_L0);
        break;
        case 1:
            hw_reset_pin(HW_PIN_OUT_H0);
            hw_set_pin(HW_PIN_OUT_H1);

            hw_reset_pin(HW_PIN_OUT_L0);
        break;
        default:
            hw_reset_pin(HW_PIN_OUT_H0);
            hw_reset_pin(HW_PIN_OUT_H1);

            hw_set_pin(HW_PIN_OUT_L0);
        break;
        }
    }
}
