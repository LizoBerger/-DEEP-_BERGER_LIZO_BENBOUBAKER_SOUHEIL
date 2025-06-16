#ifndef RUPTURE_DATA_H
#define RUPTURE_DATA_H

#include <stdint.h>
#include <stdbool.h>

// Donn�es export�es
extern volatile bool rupture_detected;
extern volatile int32_t rupture_x;
extern volatile int32_t rupture_y;

// Setter appel� depuis display
void set_rupture(int32_t x, int32_t y);

#endif // RUPTURE_DATA_H
