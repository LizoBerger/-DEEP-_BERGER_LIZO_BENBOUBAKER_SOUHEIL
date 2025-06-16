/**
 ********************************************************************************
 * @file    motion_control.c
 * @author  ChatGPT
 * @date    June 15, 2025
 * @brief   Fonctions de déplacement du robot
 ********************************************************************************
 */

#include "motion_control.h"
#include "motor_dc.h"
#include "stm32g4xx_hal.h"
#include <stdlib.h>  // pour abs()

#define SPEED       50      // Vitesse entre 0 et 100
#define MM_PAR_MS   0.5f    // Distance en millimètres parcourue par milliseconde (à ajuster)
#define DEG_PAR_MS  1.0f    // Vitesse de rotation : degrés par milliseconde (à ajuster)

/**
 * @brief Avance en ligne droite pendant un temps proportionnel à la distance
 * @param distance_mm Distance à parcourir en mm (positive = avant, négative = arrière)
 */
void move_forward(int32_t distance_mm)
{
    if (distance_mm >= 0) {
        Motor_Forward();
    } else {
        Motor_Backward();
        distance_mm = -distance_mm;  // prendre la valeur absolue pour la durée
    }

    uint32_t delay_ms = (uint32_t)(distance_mm / MM_PAR_MS);
    HAL_Delay(delay_ms);

    Motor_Stop();
}

/**
 * @brief Effectue une rotation du robot
 * @param angle_deg Angle en degrés (positif = droite, négatif = gauche)
 */
void turn_angle(int32_t angle_deg)
{
    if (angle_deg > 0) {
        Motor_Right();
    } else {
        Motor_Left();
        angle_deg = -angle_deg;
    }

    uint32_t delay_ms = (uint32_t)(angle_deg / DEG_PAR_MS);
    HAL_Delay(delay_ms);

    Motor_Stop();
}

/**
 * @brief Se déplace vers une position (x, y) en mm par translation puis rotation (approche simple)
 * @param x_mm Coordonnée x en mm
 * @param y_mm Coordonnée y en mm
 */
void move_to(int32_t x_mm, int32_t y_mm)
{
    // Distance et angle à parcourir (approche simplifiée en deux étapes)
    if (x_mm != 0) {
        turn_angle((x_mm > 0) ? 0 : 180);  // 0° = avant, 180° = arrière
        move_forward(abs(x_mm));
    }

    if (y_mm != 0) {
        turn_angle((y_mm > 0) ? 90 : -90);  // 90° = droite, -90° = gauche
        move_forward(abs(y_mm));
    }

    Motor_Stop();
}
