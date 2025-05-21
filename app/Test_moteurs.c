/**
 *******************************************************************************
 * @file 	test_moteurs.c
 * @author  Lizo Berger/Souheil Benboubaker
 * @date 	May 03, 2025
 * @brief	Fichier .c du test des moteurs
 *******************************************************************************
 */


#include "config.h"

#if USE_MOTEURS_TEST
#include "MotorDC/stm32g4_motorDC.h"
#include "stm32g4xx_hal.h"


void Moteurs_test(){
	BSP_MOTOR_demo();
}
#endif
