<<<<<<< HEAD
/*
 ********************************************************************************
 * @file 	electroaimant.c
 * @author  Souheil Benboubaker
 * @date 	May 03, 2025
 * @brief	Fichier .c de l'electroaimant
 *******************************************************************************
 */
=======
#include "Electroaimant.h"
#include "stm32g4xx_hal.h"

void electroaimant_on(void) {
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_SET); // Ou autre pin selon câblage
}

void electroaimant_off(void) {
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_RESET);
}
>>>>>>> 710a3f5c85705c0a23fa23a1df1d7b5f78add15d
