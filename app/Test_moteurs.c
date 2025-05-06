/**
 *******************************************************************************
 * @file 	test_moteurs.c
 * @author  LizoBerger/SouheilBenboubaker
 * @date 	May 03, 2025
 * @brief	Fichier .c du test des moteurs
 *******************************************************************************
 */


#include "config.h"

#if USE_MOTEURS_TEST
#include "stm32g4_motorDC.h"
#include "stm32g4xx_hal.h"


void Moteurs_test(){
	BSP_MOTOR_demo();
}
#endif
