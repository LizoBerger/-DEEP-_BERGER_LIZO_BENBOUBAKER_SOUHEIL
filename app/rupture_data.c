#include "rupture_data.h"

volatile bool rupture_detected = false;
volatile int32_t rupture_x = 0;
volatile int32_t rupture_y = 0;

void set_rupture(int32_t x, int32_t y) {
    if (!rupture_detected) {
        rupture_detected = true;
        rupture_x = x;
        rupture_y = y;
    }
}
