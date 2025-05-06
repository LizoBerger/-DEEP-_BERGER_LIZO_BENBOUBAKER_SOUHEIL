/**
*******************************************************************************
* @file main.c
* @author jjo
* @date Mar 29, 2024
* @brief Fichier principal de votre projet sur carte Nucléo STM32G431KB
*******************************************************************************
*/

#include "config.h"
#include "stm32g4_sys.h"

#include "stm32g4_systick.h"
#include "stm32g4_gpio.h"
#include "stm32g4_uart.h"
#include "stm32g4_utils.h"
#include "tft_ili9341/stm32g4_ili9341.h"
#include "tft_ili9341/stm32g4_fonts.h"
#include "Electroaimant.h"
#include "test_tft.h"

#include <stdio.h>




// Déclaration des fonctions de test des moteurs
void motor_forward(void);
void motor_reverse(void);
void motor_stop(void);


uint8_t lidar_data[9]; // Par exemple pour TFmini
int i = 0;

void write_LED(bool b)
{
    HAL_GPIO_WritePin(LED_GREEN_GPIO, LED_GREEN_PIN, b);
}


bool char_received(uart_id_t uart_id)
{
    if (BSP_UART_data_ready(uart_id)) /* Si un caractère est reçu sur l'UART 2 */
    {
        /* On "utilise" le caractère pour vider le buffer de réception */
        BSP_UART_get_next_byte(uart_id);
        return true;
    }
    else
        return false;
}

void heartbeat(void)
{
    while (!char_received(UART2_ID))
    {
        write_LED(true);
        HAL_Delay(50);
        write_LED(false);
        HAL_Delay(1500);
    }
}



/**
* @brief Point d'entrée de votre application
*/
int main(void)
{
    /* Cette ligne doit rester la première de votre main !
    * Elle permet d'initialiser toutes les couches basses des drivers (Hardware Abstraction Layer),
    * condition préalable indispensable à l'exécution des lignes suivantes.
    */
    HAL_Init();

    /* Initialisation des périphériques utilisés dans votre programme */
    BSP_GPIO_enable();

    BSP_UART_init(UART2_ID, 115200);

    /* Indique que les printf sont dirigés vers l'UART2 */
    BSP_SYS_set_std_usart(UART2_ID, UART2_ID, UART2_ID);

    /* Initialisation du port de la LED verte (carte Nucleo) */
    BSP_GPIO_pin_config(LED_GREEN_GPIO, LED_GREEN_PIN, GPIO_MODE_OUTPUT_PP,
                          GPIO_NOPULL, GPIO_SPEED_FREQ_HIGH, GPIO_NO_AF);

    BSP_GPIO_pin_config(GPIOB, GPIO_PIN_5, GPIO_MODE_OUTPUT_PP,
                              GPIO_NOPULL, GPIO_SPEED_FREQ_HIGH, GPIO_NO_AF);
    /* Hello student */
    printf("Hi <Student>, can you read me?\n");

	#if USE_TFT_TEST
    tft_test();
	#endif

	#if USE_ELECTROAIMANT_TEST
    electro_test();
	#endif

	#if USE_LIDAR_TEST
    LiDAR_test();
	#endif

	#if USE_MOTEURS_TEST
    Moteurs_test();
	#endif

    // heartbeat(); // Fonction heartbeat désactivée pour le test

    /* Boucle infinie */
    while (1)
    {


    }
}
