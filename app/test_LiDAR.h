/*
 ********************************************************************************
 * @file 	test_LiDAR.h
 * @author  Lizo Berger
 * @date 	May 07, 2025
 * @brief	Fichier .h du test du LiDAR
 *******************************************************************************
 */

#ifndef TEST_LIDAR_H_
#define TEST_LIDAR_H_

#include "config.h"

#if USE_LIDAR_TEST
#include "stm32g4xx_hal.h"
#include "stm32g4_ld19.h"

void LiDAR_test(void);

#endif
#endif
