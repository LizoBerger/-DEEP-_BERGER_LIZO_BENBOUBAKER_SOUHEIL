/**
 *******************************************************************************
 * @file 	test_electroaimant.c
 * @author  LizoBerger/SouheilBenboubaker
 * @date 	May 03, 2025
 * @brief	Fichier .c du test de l'électroaimant
 *******************************************************************************
 */

#include "config.h"
#include "Electroaimant.h"
#include <stdio.h>

#if USE_ELECTROAIMANT_TEST

#include "stm32g4xx_hal.h"

void electro_test(void){
	//Activation
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_SET);
	printf("Electroaimant activé\n");
	HAL_Delay(2000);

	//Désactivation
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_RESET);
	printf("Electroaimant désactivé");

}

#endif
