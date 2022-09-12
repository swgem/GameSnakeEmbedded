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

//// OVERWRITE FUNCTION IMPLEMENTATION

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {

}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
    if (htim == hw_main_timer()) {
        run_leds_state_machine();
    }
}
