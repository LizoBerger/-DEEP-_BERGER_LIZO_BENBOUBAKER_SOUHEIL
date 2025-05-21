/**
 *******************************************************************************
 * @file 	test_LiDAR.c
 * @author  Lizo Berger/Souheil Benboubaker
 * @date 	May 03, 2025
 * @brief	Fichier .c du test du LiDAR
 *******************************************************************************
 */


#include "config.h"

#if USE_LIDAR_TEST
#include "LD19/stm32g4_ld19.h"
#include "stm32g4xx_hal.h"


void LiDAR_test(){
	LD19_DEMO_process_main();
}
#endif
