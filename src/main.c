#include "nrf_drv_spi.h"
#include "app_util_platform.h"
#include "nrf_gpio.h"
#include "nrf_delay.h"
#include "boards.h"
#include "app_error.h"
#include "nrf_lcd.h"
#include "nrf_gfx.h"
#include "nrf_log.h"
#include "nrf_log_ctrl.h"
#include "nrf_log_default_backends.h"

#include "paper.h"

extern const nrf_gfx_font_desc_t orkney_8ptFontInfo;

static lcd_cb_t lcd_cb = {
 .state    = NRFX_DRV_STATE_UNINITIALIZED,
 .height   = PAPER_PIXEL_HEIGHT,
 .width    = PAPER_PIXEL_WIDTH,
 .rotation = NRF_LCD_ROTATE_90
};

static const nrf_lcd_t lcd = {
  .lcd_init = paper_init,
  .lcd_uninit = paper_uninit,
  .lcd_pixel_draw = paper_pixel_draw,
  .lcd_rect_draw = paper_rect_draw,
  .lcd_display = paper_display,
  .lcd_rotation_set = paper_rotation_set,
  .lcd_display_invert = paper_display_invert,
  .p_lcd_cb = &lcd_cb
};

int main(void) {
  APP_ERROR_CHECK(NRF_LOG_INIT(NULL));
  NRF_LOG_DEFAULT_BACKENDS_INIT();

  APP_ERROR_CHECK(nrf_gfx_init(&lcd));

  NRF_LOG_INFO("paper example started");
  NRF_LOG_FLUSH();

  // draw a horizontal line
  nrf_gfx_line_t hline = NRF_GFX_LINE(
    0,
    nrf_gfx_height_get(&lcd) / 2,
    nrf_gfx_width_get(&lcd),
    nrf_gfx_height_get(&lcd) / 2,
    4
  );
  nrf_gfx_line_draw(&lcd, &hline, 1);

  // draw a vertical line
  nrf_gfx_line_t vline = NRF_GFX_LINE(
    nrf_gfx_width_get(&lcd) / 2,
    0,
    nrf_gfx_width_get(&lcd) / 2,
    nrf_gfx_height_get(&lcd),
    4
  );
  nrf_gfx_line_draw(&lcd, &vline, 1);

  nrf_gfx_display(&lcd);

  while (true)
    if(!NRF_LOG_PROCESS())
      __WFE();
}
