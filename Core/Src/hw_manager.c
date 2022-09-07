/*
 * hw_manager.c
 *
 *  Created on: 7 de set de 2022
 *      Author: eric_
 */

#include "hw_manager.h"

//// INTERNAL VARIABLE

static const GPIO_TypeDef* g_hw_pin_GPIOx[] = {
    GPIOA,
    GPIOB,
    GPIOB,
    GPIOB,
    GPIOA,
    GPIOA,
    GPIOC,
    GPIOB,
    GPIOA,
    GPIOA,
    GPIOB,
    GPIOB,
    GPIOC,
    GPIOC,
    GPIOA,
    GPIOA,
    GPIOB,
    GPIOB,
    GPIOB,
    GPIOB
};

static const uint16_t g_hw_pin_GPIO_Pin[] = {
    GPIO_PIN_10,
    GPIO_PIN_5,
    GPIO_PIN_4,
    GPIO_PIN_10,
    GPIO_PIN_8,
    GPIO_PIN_9,
    GPIO_PIN_7,
    GPIO_PIN_6,
    GPIO_PIN_7,
    GPIO_PIN_6,
    GPIO_PIN_9,
    GPIO_PIN_8,
    GPIO_PIN_8,
    GPIO_PIN_6,
    GPIO_PIN_5,
    GPIO_PIN_12,
    GPIO_PIN_11,
    GPIO_PIN_12,
    GPIO_PIN_11,
    GPIO_PIN_2
};

static TIM_HandleTypeDef* g_main_timer = NULL;

//// FUNCTION IMPLEMENTATION

void hw_set_main_timer(TIM_HandleTypeDef* tim) {
    g_main_timer = tim;
}

const GPIO_TypeDef* hw_GPIOx(HW_PIN pin) {
    return g_hw_pin_GPIOx[pin];
}

const uint16_t hw_GPIO_Pin(HW_PIN pin) {
    return g_hw_pin_GPIO_Pin[pin];
}

const TIM_HandleTypeDef* hw_main_timer() {
    return g_main_timer;
}

void hw_set_pin(HW_PIN pin) {
    HAL_GPIO_WritePin(hw_GPIOx(pin), hw_GPIO_Pin(pin), GPIO_PIN_SET);
}

void hw_reset_pin(HW_PIN pin) {
    HAL_GPIO_WritePin(hw_GPIOx(pin), hw_GPIO_Pin(pin), GPIO_PIN_RESET);
}
