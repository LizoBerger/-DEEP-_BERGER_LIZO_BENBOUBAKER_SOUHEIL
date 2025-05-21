/*
 ********************************************************************************
 * @file 	test_moteurs.h
 * @author  LizoBerger/SouheilBenboubaker
 * @date 	May 21, 2025
 * @brief	Fichier .h du test des moteurs
 *******************************************************************************
 */


#ifndef TEST_MOTEURS_H_
#define TEST_MOTEURS_H_

#include "config.h"

#if USE_MOTEURS_TEST
#include "stm32g4xx_hal.h"
#include "stm32g4_ld19.h"

void Moteurs_test(void);

#endif
#endif
