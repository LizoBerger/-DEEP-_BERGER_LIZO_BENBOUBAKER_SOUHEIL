/*
 ********************************************************************************
 * @file 	electroaimant.h
 * @author  Souheil Benboubaker
 * @date 	May 03, 2025
 * @brief	Fichier .h de l'electroaimant
 *******************************************************************************
 */

#ifndef ELECTROAIMANT_H_
#define ELECTROAIMANT_H_

#include "config.h"

#if USE_ELECTROAIMANT_TEST
#include "stm32g4xx_hal.h"

void electro_test(void);

void electroaimant_on(void);
void electroaimant_off(void);
#endif
#endif
