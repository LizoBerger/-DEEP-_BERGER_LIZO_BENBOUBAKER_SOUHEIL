/*
 ********************************************************************************
 * @file 	motor_dc.h
 * @author  Lizo Berger / Revu par ChatGPT
 * @date 	June 06, 2025
 * @brief	Header des commandes moteur
 ********************************************************************************
 */

#ifndef MOTOR_DC_H_
#define MOTOR_DC_H_

#include "config.h"
#include "stm32g4xx_hal.h"

#if USE_MOTOR_DC

// Fonctions de contrôle moteur simples pour compatibilité avec motion_control.c
void Motor_Init(void);
void Motor_Forward(void);
void Motor_Backward(void);
void Motor_Left(void);
void Motor_Right(void);
void Motor_Stop(void);
void Motor_Demo(void);

#endif // USE_MOTOR_DC

#endif // MOTOR_DC_H_
