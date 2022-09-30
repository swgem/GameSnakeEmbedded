/*
 * hw_manager.c
 *
 *  Created on: 7 de set de 2022
 *      Author: eric_
 */

#include "hw_manager.h"

//// INTERNAL VARIABLE

static const uint32_t g_hw_pin[] = {
    (uint32_t)GPIOA, (uint32_t)GPIO_PIN_10,
    (uint32_t)GPIOB, (uint32_t)GPIO_PIN_5,
    (uint32_t)GPIOB, (uint32_t)GPIO_PIN_4,
    (uint32_t)GPIOB, (uint32_t)GPIO_PIN_10,
    (uint32_t)GPIOA, (uint32_t)GPIO_PIN_8,
    (uint32_t)GPIOA, (uint32_t)GPIO_PIN_9,
    (uint32_t)GPIOC, (uint32_t)GPIO_PIN_7,
    (uint32_t)GPIOB, (uint32_t)GPIO_PIN_6,
    (uint32_t)GPIOA, (uint32_t)GPIO_PIN_7,
    (uint32_t)GPIOA, (uint32_t)GPIO_PIN_6,
    (uint32_t)GPIOB, (uint32_t)GPIO_PIN_9,
    (uint32_t)GPIOB, (uint32_t)GPIO_PIN_8,
    (uint32_t)GPIOC, (uint32_t)GPIO_PIN_8,
    (uint32_t)GPIOC, (uint32_t)GPIO_PIN_6,
    (uint32_t)GPIOC, (uint32_t)GPIO_PIN_5,
    (uint32_t)GPIOA, (uint32_t)GPIO_PIN_12,
    (uint32_t)GPIOB, (uint32_t)GPIO_PIN_11,
    (uint32_t)GPIOB, (uint32_t)GPIO_PIN_12,
    (uint32_t)GPIOB, (uint32_t)GPIO_PIN_11,
    (uint32_t)GPIOB, (uint32_t)GPIO_PIN_2,
    (uint32_t)GPIOB, (uint32_t)GPIO_PIN_1,
    (uint32_t)GPIOB, (uint32_t)GPIO_PIN_15,
    (uint32_t)GPIOB, (uint32_t)GPIO_PIN_14,
    (uint32_t)GPIOB, (uint32_t)GPIO_PIN_13
};

static TIM_HandleTypeDef* g_main_timer = NULL;

//// INTERNAL FUNCTION DECLARATION

__STATIC_FORCEINLINE GPIO_TypeDef* hw_GPIOx(HW_PIN pin);
__STATIC_FORCEINLINE uint16_t hw_GPIO_Pin(HW_PIN pin);

//// FUNCTION IMPLEMENTATION

__STATIC_FORCEINLINE GPIO_TypeDef* hw_GPIOx(HW_PIN pin) {
    return (GPIO_TypeDef*)g_hw_pin[2*pin];
}

__STATIC_FORCEINLINE uint16_t hw_GPIO_Pin(HW_PIN pin) {
    return (uint16_t)g_hw_pin[2*pin + 1];
}

void hw_set_main_timer(TIM_HandleTypeDef* tim) {
    g_main_timer = tim;
}

const TIM_HandleTypeDef* hw_main_timer() {
    return g_main_timer;
}

__INLINE HW_PIN hw_input_pin(uint16_t GPIO_Pin) {
    HW_PIN ret;
    for (HW_PIN i = HW_PIN_IN_B0; i < HW_PIN_IN_B3; i++) {
        if (GPIO_Pin == hw_GPIO_Pin(i)) {
            ret = i;
        }
    }
    return ret;
}

__INLINE void hw_set_pin(HW_PIN pin) {
    HAL_GPIO_WritePin(hw_GPIOx(pin), hw_GPIO_Pin(pin), GPIO_PIN_SET);
}

__INLINE void hw_reset_pin(HW_PIN pin) {
    HAL_GPIO_WritePin(hw_GPIOx(pin), hw_GPIO_Pin(pin), GPIO_PIN_RESET);
}
