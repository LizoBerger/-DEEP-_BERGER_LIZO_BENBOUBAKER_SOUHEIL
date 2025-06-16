/*******************************************************************************
* @file    main.c
* @author  jjo
* @date    Mar 29, 2024
* @brief   Fichier principal de votre projet sur carte Nucleo STM32G431KB
*******************************************************************************/

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
#include "test_LiDAR.h"
#include "MotorDC/stm32g4_motorDC.h"
#include "rupture_data.h"
#include "motion_control.h"

#include <stdio.h>
#include <stdbool.h>

// Machine à états
typedef enum {
    STATE_WAIT_FOR_RUPTURE,
    STATE_MOVE_TO_OBJECT,
    STATE_ACTIVATE_ELECTRO,
    STATE_RETURN,
    STATE_IDLE
} State;

State state = STATE_WAIT_FOR_RUPTURE;

void write_LED(bool b) {
    HAL_GPIO_WritePin(LED_GREEN_GPIO, LED_GREEN_PIN, b);
}

bool char_received(uart_id_t uart_id) {
    if (BSP_UART_data_ready(uart_id)) {
        BSP_UART_get_next_byte(uart_id);
        return true;
    }
    return false;
}

void heartbeat(void) {
    while (!char_received(UART2_ID)) {
        write_LED(true);
        HAL_Delay(50);
        write_LED(false);
        HAL_Delay(1500);
    }
}

// ✅ Fonction de test indépendante pour diagnostiquer les moteurs
void test_moteurs_simple() {
    printf("Moteur gauche AVANT\n");
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_SET);     // IN1 gauche
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, GPIO_PIN_RESET);  // IN2 gauche
    HAL_Delay(2000);

    printf("Moteur gauche ARRIÈRE\n");
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, GPIO_PIN_SET);
    HAL_Delay(2000);

    printf("Moteur droit AVANT\n");
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_SET);     // IN1 droite
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_RESET);   // IN2 droite
    HAL_Delay(2000);

    printf("Moteur droit ARRIÈRE\n");
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_SET);
    HAL_Delay(2000);

    printf("STOP\n");
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_RESET);
}

int main(void) {
    HAL_Init();
    BSP_UART_init(UART2_ID, 115200);
    BSP_SYS_set_std_usart(UART2_ID, UART2_ID, UART2_ID);

    BSP_GPIO_pin_config(LED_GREEN_GPIO, LED_GREEN_PIN, GPIO_MODE_OUTPUT_PP,
                        GPIO_NOPULL, GPIO_SPEED_FREQ_HIGH, GPIO_NO_AF);

    // Configurations moteurs
    BSP_GPIO_pin_config(GPIOB, GPIO_PIN_0, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_HIGH, GPIO_NO_AF); // gauche IN1
    BSP_GPIO_pin_config(GPIOA, GPIO_PIN_12, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_HIGH, GPIO_NO_AF); // gauche IN2
    BSP_GPIO_pin_config(GPIOB, GPIO_PIN_4, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_HIGH, GPIO_NO_AF); // droite IN1
    BSP_GPIO_pin_config(GPIOB, GPIO_PIN_6, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_HIGH, GPIO_NO_AF); // droite IN2

    printf("Hi <Student>, can you read me?\n");

    ILI9341_Init();
    Motor_Init();              // Init moteurs
    test_moteurs_simple();     // Test AVANT toute logique

#if USE_LIDAR_TEST
    LD19_init();
#endif

#if USE_TFT_TEST
    tft_test();
#endif

#if USE_ELECTROAIMANT_TEST
    electro_test();
#endif

#if USE_MOTEURS_TEST
    Moteurs_test();
#endif

    printf("Démarrage OK - UART fonctionne\n");

    while (1) {
#if USE_LIDAR_TEST
        LD19_DEMO_process_main();  // met à jour rupture_detected, rupture_x, rupture_y
#endif

        switch (state) {
            case STATE_WAIT_FOR_RUPTURE:
                if (rupture_detected) {
                    printf("Rupture détectée à (%ld, %ld)\n", rupture_x, rupture_y);
                    state = STATE_MOVE_TO_OBJECT;
                }
                break;

            case STATE_MOVE_TO_OBJECT:
                printf("Déplacement vers objet...\n");
                move_to(rupture_x, rupture_y);
                state = STATE_ACTIVATE_ELECTRO;
                break;

            case STATE_ACTIVATE_ELECTRO:
                printf("Activation électroaimant...\n");
                electroaimant_on();
                HAL_Delay(1000);
                electroaimant_off();
                state = STATE_RETURN;
                break;

            case STATE_RETURN:
                printf("Retour à la position initiale...\n");
                move_to(-rupture_x, -rupture_y);
                rupture_detected = false;
                state = STATE_IDLE;
                break;
            case STATE_IDLE:
                printf("En attente d'une nouvelle rupture.\n");
                state = STATE_WAIT_FOR_RUPTURE;
                break;
        }
    }
}
