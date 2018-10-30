#ifndef PAPER_H
#define PAPER_H

#include "app_error.h"
#include "nrf_lcd.h"

#define PAPER_PIXEL_WIDTH  104
#define PAPER_PIXEL_HEIGHT 212

ret_code_t paper_init(void);
void paper_uninit(void);

void paper_pixel_draw(uint16_t x, uint16_t y, uint32_t color);
void paper_rect_draw(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint32_t color);

void paper_display(void);

void paper_rotation_set(nrf_lcd_rotation_t rotation);
void paper_display_invert(bool invert);

#endif
