/**
 *******************************************************************************
 * @file	stm32g4_ld19_display.c
 * @author	vchav (modifié par ChatGPT)
 * @date	Jun 14, 2024
 * @brief	Module pour afficher les trames reçues du capteur lidar ld19
 *******************************************************************************
 */

#include "config.h"
#if USE_LD19
#include "stm32g4_ld19_display.h"
#include "stm32g4_ld19.h"
#include "TFT_ili9341/stm32g4_ili9341.h"
#include "TFT_ili9341/stm32g4_fonts.h"
#include "TFT_ili9341/stm32g4_xpt2046.h"
#include "QS_maths.h"
#include "stdio.h"
#include "stdlib.h"
#include "rupture_data.h"

#define DISPLAY_SIZE        200     // on veut 200 pixels pour 60 cm
#define SCALE               0.6     // soit 600 mm de portée max
#define ANGLE_MAX               18000   // 180 °
#define ANGLE_MIN               0       // 0 °
#define BUFFER_DISPLAY_SIZE     450     // 450 points
#define THRESHOLD_DELTA         5       // Seuil de rupture brutale (pixels)

typedef struct{
	int32_t x;
	int32_t y;
} coordinate_t;

coordinate_t LD19_find_coordinate(uint16_t d, uint16_t a);
void LD19_draw_scene(void);
void LD19_init_buffer_displayed(void);

coordinate_t init_point = {0,0};
bool init = false;

#include "rupture_data.h"  // ⚠️ Assure-toi que ce #include est bien en haut de ton fichier

void BSP_LD19_display_on_tft(ld19_frame_handler_t *frame) {
    static bool init = false;
    static int frame_counter = 0;

    if (!init) {
        BSP_LD19_init_tft();
        init = true;
    }

    // Efface l'écran toutes les 200 trames
    frame_counter++;
    if (frame_counter >= 200) {
        ILI9341_Fill(ILI9341_COLOR_WHITE);
        frame_counter = 0;
    }

    printf("Angle: start = %d ; end = %d\n", frame->start_angle, frame->end_angle);
    coordinate_t previous_coord = { -1, -1 };
    float angle_step = (frame->end_angle - frame->start_angle) / (POINT_PER_PACK - 1);

    for (int i = 0; i < POINT_PER_PACK; i++) {
        uint16_t distance = frame->point[i].distance;
        float angle = frame->start_angle + (i + 1) * angle_step;

        if (distance < 1000 * SCALE && distance > 50 && angle >= ANGLE_MIN && angle <= ANGLE_MAX) {
            coordinate_t coord = LD19_find_coordinate(distance, angle);

            if (coord.x > 0 && coord.x < 320 && coord.y > 0 && coord.y < 240) {
                printf("Point %d: angle = %.1f°, (%d, %d)", i, angle / 100.0, coord.x, coord.y);

                if (previous_coord.x != -1 && previous_coord.y != -1) {
                    int dx = coord.x - previous_coord.x;
                    int dy = coord.y - previous_coord.y;
                    printf(" | Δx = %d, Δy = %d", dx, dy);

                    if (abs(dx) > THRESHOLD_DELTA || abs(dy) > THRESHOLD_DELTA) {
                        ILI9341_DrawPixel(coord.x, coord.y, ILI9341_COLOR_RED);
                        printf(" --> rupture\n");

                        // ✅ Signale la rupture une seule fois
                        set_rupture(coord.x, coord.y);
                    } else {
                        printf("\n");
                    }
                } else {
                    printf(" (premier point)\n");
                }

                previous_coord = coord;
            }
        }
    }
}




void LD19_init_buffer_displayed(void) { }

coordinate_t LD19_find_coordinate(uint16_t d, uint16_t a){
	coordinate_t coord;
	int16_t cosinus, sinus;
	uint16_t angle_rad_4096 = GEOMETRY_modulo_angle((int16_t)((uint32_t)a * 183 / 256));
	COS_SIN_4096_get(angle_rad_4096, &cosinus, &sinus);

	// Affichage proportionnel : 60 cm → 200 pixels de rayon
	coord.x = 160 + ((int32_t)cosinus * d * DISPLAY_SIZE) / (600 * 4096);
	coord.y = ((int32_t)sinus * d * DISPLAY_SIZE) / (600 * 4096) + 40;
	return coord;
}


void BSP_LD19_init_tft(void){
	ILI9341_Init();
	XPT2046_init();
	LD19_init_buffer_displayed();
	ILI9341_Rotate(ILI9341_Orientation_Landscape_2);
	ILI9341_DisplayOff();
	ILI9341_DisplayOn();
	LD19_draw_scene();
}

void LD19_draw_scene(void){
	ILI9341_DrawFilledCircle(160, 40, 150, ILI9341_COLOR_WHITE);
	ILI9341_DrawCircle(160, 40, 150, ILI9341_COLOR_BLACK);
	ILI9341_DrawFilledRectangle(320, 40, 300, 0, ILI9341_COLOR_WHITE);
	ILI9341_DrawFilledRectangle(20, 40, 0, 0, ILI9341_COLOR_WHITE);
	ILI9341_DrawLine(10, 40, 310, 40, ILI9341_COLOR_BLACK);
	ILI9341_DrawFilledCircle(160,18,16,ILI9341_COLOR_BLACK);
	ILI9341_DrawFilledRectangle(185, 22, 135, 14, ILI9341_COLOR_BLACK);
	ILI9341_DrawFilledCircle(180,18,2,ILI9341_COLOR_WHITE);
	ILI9341_DrawFilledCircle(140,18,2,ILI9341_COLOR_WHITE);
	ILI9341_DrawCircle(160,18,16,ILI9341_COLOR_RED);
	ILI9341_Puts(166, 15, ">", &Font_7x10, ILI9341_COLOR_WHITE, ILI9341_COLOR_BLACK);
	ILI9341_DrawLine(160, 37, 310, 37, ILI9341_COLOR_BLUE2);
	ILI9341_Puts(205, 28, "150 pixels", &Font_7x10, ILI9341_COLOR_BLUE2, ILI9341_COLOR_WHITE);
}

#endif
