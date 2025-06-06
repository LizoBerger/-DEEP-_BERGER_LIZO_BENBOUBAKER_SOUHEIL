/*
 ********************************************************************************
 * @file 	motor_dc.h
 * @author  Lizo Berger/Souheil Benboubaker
 * @date 	June 06, 2025
 * @brief	Fichier .h des commandes moteur
 *******************************************************************************
 */

#ifndef MOTOR_DC_H_
#define MOTOR_DC_H_

#include "config.h"


#include "stm32g4_motorDC.h"

void Motor_forward(void);
void Motor_backward(void);
void Motor_left(void);
void Motor_right(void);

#endif
