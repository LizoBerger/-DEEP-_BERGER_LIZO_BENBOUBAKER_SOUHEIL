/**
 ********************************************************************************
 * @file    motion_control.h
 * @author  ChatGPT
 * @date    June 15, 2025
 * @brief   En-t�te des fonctions de d�placement du robot
 ********************************************************************************
 */

#ifndef MOTION_CONTROL_H
#define MOTION_CONTROL_H

#include <stdint.h>

/**
 * @brief Avance ou recule selon la distance sp�cifi�e
 * @param distance_mm Distance en millim�tres (positive = avant, n�gative = arri�re)
 */
void move_forward(int32_t distance_mm);

/**
 * @brief Tourne � gauche ou � droite selon l'angle
 * @param angle_deg Angle en degr�s (positif = droite, n�gatif = gauche)
 */
void turn_angle(int32_t angle_deg);

/**
 * @brief Se d�place jusqu'� une position x, y (en mm) via translations simples
 * @param x_mm Position cible en X
 * @param y_mm Position cible en Y
 */
void move_to(int32_t x_mm, int32_t y_mm);

#endif // MOTION_CONTROL_H
