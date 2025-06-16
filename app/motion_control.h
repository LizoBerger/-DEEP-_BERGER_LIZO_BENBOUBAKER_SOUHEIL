/**
 ********************************************************************************
 * @file    motion_control.h
 * @author  ChatGPT
 * @date    June 15, 2025
 * @brief   En-tête des fonctions de déplacement du robot
 ********************************************************************************
 */

#ifndef MOTION_CONTROL_H
#define MOTION_CONTROL_H

#include <stdint.h>

/**
 * @brief Avance ou recule selon la distance spécifiée
 * @param distance_mm Distance en millimètres (positive = avant, négative = arrière)
 */
void move_forward(int32_t distance_mm);

/**
 * @brief Tourne à gauche ou à droite selon l'angle
 * @param angle_deg Angle en degrés (positif = droite, négatif = gauche)
 */
void turn_angle(int32_t angle_deg);

/**
 * @brief Se déplace jusqu'à une position x, y (en mm) via translations simples
 * @param x_mm Position cible en X
 * @param y_mm Position cible en Y
 */
void move_to(int32_t x_mm, int32_t y_mm);

#endif // MOTION_CONTROL_H
