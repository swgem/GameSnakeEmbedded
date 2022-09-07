/*
 * hw_manager.h
 *
 *  Created on: 7 de set de 2022
 *      Author: eric_
 */

#ifndef INC_HW_MANAGER_H_
#define INC_HW_MANAGER_H_

#include "main.h"

//// ENUM

typedef enum {
    HW_PIN_OUT_H0 = 0,
    HW_PIN_OUT_H1,
    HW_PIN_OUT_H2,
    HW_PIN_OUT_H3,
    HW_PIN_OUT_H4,
    HW_PIN_OUT_H5,
    HW_PIN_OUT_H6,
    HW_PIN_OUT_H7,
    HW_PIN_OUT_H8,
    HW_PIN_OUT_H9,
    HW_PIN_OUT_L0,
    HW_PIN_OUT_L1,
    HW_PIN_OUT_L2,
    HW_PIN_OUT_L3,
    HW_PIN_OUT_L4,
    HW_PIN_OUT_L5,
    HW_PIN_OUT_L6,
    HW_PIN_OUT_L7,
    HW_PIN_OUT_L8,
    HW_PIN_OUT_L9,
} HW_PIN;

//// EXTERNAL FUNCTION DECLARATION

void hw_set_main_timer(TIM_HandleTypeDef* tim);

const GPIO_TypeDef* hw_GPIOx(HW_PIN pin);
const uint16_t hw_GPIO_Pin(HW_PIN pin);
const TIM_HandleTypeDef* hw_main_timer();

void hw_set_pin(HW_PIN pin);
void hw_reset_pin(HW_PIN pin);

#endif /* INC_HW_MANAGER_H_ */
