/**
 *******************************************************************************
 * @file 	wall_calibration.h
 * @author  LizoBerger/SouheilBenboubaker
 * @date 	May 03, 2025
 * @brief	Fichier .h du calibrage x/y
 *******************************************************************************
 *
 */

#ifndef WALL_CALIBRATION_H
#define WALL_CALIBRATION_H

#include <stdint.h>
#include "motor_dc.h"

void WallCalibration_check_origin(float x, float y);

#endif
