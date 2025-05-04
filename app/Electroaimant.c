/**
 *******************************************************************************
 * @file 	electroaimant.c
 * @author  LizoBerger/SouheilBenboubaker
 * @date 	May 03, 2025
 * @brief	Fichier .c de l'electroaimant
 *******************************************************************************
 */

#include "config.h"

#include "electroaimant.h"
#include "stm32g4xx_hal.h"



void electro_demo(void){
	//Activation
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_SET);
	printf("Electroaimant activénnnnnn\n");
	HAL_Delay(2000);

	//Désactivation
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_RESET);
	printf("Electroaimant désactivé");
	HAL_Delay(2000);
}

