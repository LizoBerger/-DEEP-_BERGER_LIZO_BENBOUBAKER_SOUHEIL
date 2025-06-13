/*
 ********************************************************************************
 * @file 	motor_dc.c
 * @author  Lizo Berger
 * @date 	June 06, 2025
 * @brief	Fichier .c des commandes moteur
 *******************************************************************************
 */

#include "motor_dc.h"
#if USE_MOTOR_DC

static void Motor_Reset(void) {
    HAL_GPIO_WritePin(GPIOB,  GPIO_PIN_4,  GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOB ,GPIO_PIN_6,GPIO_PIN_RESET);
}

void Motor_Init(void) {
    Motor_Reset();
}

void Motor_Forward(void) {
    Motor_Reset();
    HAL_GPIO_WritePin(GPIOB,  GPIO_PIN_4,  GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, GPIO_PIN_SET);
}

void Motor_Backward(void) {
    Motor_Reset();
    HAL_GPIO_WritePin(GPIOB,  GPIO_PIN_0,  GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_SET);
}

void Motor_Left(void) {
    Motor_Reset();
    HAL_GPIO_WritePin(GPIOB,  GPIO_PIN_0,  GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOA,  GPIO_PIN_12,  GPIO_PIN_SET);
}

void Motor_Right(void) {
    Motor_Reset();
    HAL_GPIO_WritePin(GPIOB,  GPIO_PIN_4,  GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_SET);
}

void Motor_Stop(void) {
    Motor_Reset();
}

void Motor_Demo(void) {
    Motor_Forward();
    HAL_Delay(1000);

    Motor_Backward();
    HAL_Delay(1000);

    Motor_Left();
    HAL_Delay(1000);

    Motor_Right();
    HAL_Delay(1000);

    Motor_Stop();
}

#endif
