/**
 *******************************************************************************
 * @file 	wall_calibration.c
 * @author  Lizo Berger/Souheil Benboubaker
 * @date 	May 14, 2025
 * @brief	Fichier .c du calibrage x/y
 *******************************************************************************
 */

#include "wall_calibration.h"

static uint8_t origin_set = 0; //on se sert d'un flag pour ne pas repeter l'opération
static float origin_x = 0;
static float origin_y = 0;
static float offset_x = 0.20;
static float offset_y = 0.10;

void WallCalibration_check_origin(float x, float y) {
    if (!origin_set) {
        origin_x = x + offset_x;
        origin_y = y + offset_y;
        origin_set = 1;
    }
}
