/**
 *******************************************************************************
 * @file 	test_tft.c
 * @author  LizoBerger
 * @date 	May 03, 2025
 * @brief	Fichier .c du test de l'écran tft
 *******************************************************************************
 */


#include "config.h"

#if USE_TFT_TEST
#include "tft_ili9341/stm32g4_ili9341.h"
#include "stm32g4xx_hal.h"


void tft_test(){
	ILI9341_demo();
}

#endif
