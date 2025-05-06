/*
 ********************************************************************************
 * @file 	test_tft.h
 * @author  LizoBerger/SouheilBenboubaker
 * @date 	May 03, 2025
 * @brief	Fichier .h du test de l'écran tft
 *******************************************************************************
 */

#ifndef ELECTROAIMANT_H_
#define ELECTROAIMANT_H_

#include "config.h"

#if USE_TFT_TEST
#include "stm32g4xx_hal.h"

void tft_test(void);

#endif
#endif
