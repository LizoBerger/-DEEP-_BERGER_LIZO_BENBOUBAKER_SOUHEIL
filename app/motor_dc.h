/*
 ********************************************************************************
 * @file 	motor_dc.h
 * @author  Lizo Berger
 * @date 	June 06, 2025
 * @brief	Fichier .h des commandes moteur
 *******************************************************************************
 */


#ifndef MOTOR_DC_H_
#define MOTOR_DC_H_


#include "config.h"
#include "stm32g4_motorDC.h"
#include "stm32g4xx_hal.h"

#if USE_MOTOR_DC

// Structure d'un moteur DC
typedef struct {
    GPIO_TypeDef* IN1_Port;
    uint16_t      IN1_Pin;
    GPIO_TypeDef* IN2_Port;
    uint16_t      IN2_Pin;
    TIM_HandleTypeDef* pwm_timer;
    uint32_t      pwm_channel;
} DC_Motor_t;

typedef enum {
    MOTOR_LEFT,
    MOTOR_RIGHT,
} MotorID_t;

typedef struct {
    DC_Motor_t left_motor;
    DC_Motor_t right_motor;
} Motors_Config_t;



void DC_Motor_Init(DC_Motor_t* motor);
void Motors_Config_Init(Motors_Config_t* config);



void DC_Motor_Forward(DC_Motor_t* motor, uint8_t speed_percent);
void DC_Motor_Backward(DC_Motor_t* motor, uint8_t speed_percent);
void DC_Motor_Stop(DC_Motor_t* motor);
void DC_Motor_SetSpeed(DC_Motor_t* motor, uint8_t speed_percent);
void DC_Motor_Brake(DC_Motor_t* motor);



void Robot_Forward(uint8_t speed_percent);
void Robot_Backward(uint8_t speed_percent);
void Robot_Left(uint8_t speed_percent);
void Robot_Right(uint8_t speed_percent);
void Robot_Stop(void);



void Motor_Demo_Mode(void);



#define DEFAULT_SPEED 50

#endif MOTOR_DC_H_

#endif
#endif
