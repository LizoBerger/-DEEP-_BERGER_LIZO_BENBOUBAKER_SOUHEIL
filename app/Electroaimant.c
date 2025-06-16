#include "Electroaimant.h"
#include "stm32g4xx_hal.h"

void electroaimant_on(void) {
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_SET); // Ou autre pin selon câblage
}

void electroaimant_off(void) {
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_RESET);
}
