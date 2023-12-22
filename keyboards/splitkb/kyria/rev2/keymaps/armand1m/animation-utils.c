/**
 * Utilities for QMK oled animations
 *
 * Copyright (c) Marek Piechut
 * MIT License
 */
#pragma once
#include <stdio.h>

#ifndef ANIM_RENDER_WPM
  #define ANIM_RENDER_WPM true
#endif
#ifndef FAST_TYPE_WPM
  #define FAST_TYPE_WPM 45 // Switch to fast animation when over words per minute
#endif
#ifndef ANIM_INVERT
  #define ANIM_INVERT false // Invert animation color and background
#endif
#ifndef ANIM_BG
  #define ANIM_BG 0x00
#endif
#ifndef ANIM_FRAME_TIME
  #define ANIM_FRAME_TIME 250
#endif

#define ANIM_WPM_WIDTH 22
#define OLED_ROWS OLED_DISPLAY_HEIGHT / 4

static void oled_render_wpm(void) {
  static char wpm_str[4];

  sprintf(wpm_str, "%03d", get_current_wpm());
  oled_set_cursor(0, 3);
  oled_write_P(PSTR("WPM"), false);
  oled_set_cursor(0, 4);
  oled_write(wpm_str, false);
}

static void oled_render_anim_frame(const char **fast_frames, const char **slow_frames, uint8_t frames_len) {
  static uint32_t anim_timer = 0;
  static uint8_t current_frame = 0;
  static int16_t frame_offset = ANIM_RENDER_WPM ? ANIM_WPM_WIDTH : 0;
  static int8_t step = 12;
  static int8_t bg = ANIM_BG;

  if (timer_elapsed32(anim_timer) > ANIM_FRAME_TIME) {
    anim_timer = timer_read32();

    const uint8_t speed = get_current_wpm();
    const bool is_fast = speed > FAST_TYPE_WPM;

    const char *frame = is_fast
      ? fast_frames[current_frame]
      : slow_frames[current_frame];

    uint8_t frame_start_offset = ANIM_RENDER_WPM ? ANIM_WPM_WIDTH : 0;
    current_frame = (current_frame + 1) % frames_len;

    // useful here:
    // https://github.com/qmk/qmk_firmware/blob/master/docs/feature_oled_driver.md#128x64--custom-sized-oled-displays
    for (int offset = 0; offset <= OLED_MATRIX_SIZE; offset++) {
      // since we're rendering content originally built for 128x32
      // we compensate here by just skipping the first and last 256
      // offsets so the 128x32 appears centralized in a 128x64 screen
      if (offset < 256 || offset > 768) {
        continue;
      }

      uint16_t col = offset % OLED_DISPLAY_WIDTH;

      if (col < frame_start_offset) {
        // skip rendering since is within the offset range
        continue;
      }

      if (col < frame_offset || col > frame_offset + ANIM_FRAME_WIDTH) {
        // repaints the background when needed.
        // also avoids a memory leak on the keyboard
        oled_write_raw_byte((ANIM_INVERT ? ~bg : bg), offset);
        continue;
      }

      if (col <= OLED_DISPLAY_WIDTH) {
        // render a frame
        // we subtract 256 from the offset here to make sure
        // that the offset range used during rendering will be
        // from 0 to 512, instead of 256 until 768.
        uint8_t row = (offset - 256) / OLED_DISPLAY_WIDTH;

        int frame_data_offset = ANIM_FRAME_WIDTH * row + col - frame_offset;
        uint8_t col_data = pgm_read_byte(frame + frame_data_offset);

        oled_write_raw_byte(ANIM_INVERT ? ~col_data : col_data, offset);
      }
    }

    #ifdef ANIM_SCROLL
    if (is_fast) {
      #ifdef ANIM_BOUNCE
      if (frame_offset + ANIM_FRAME_WIDTH > OLED_DISPLAY_WIDTH || frame_offset < frame_start_offset) {
        step = -step;
      }
      #endif

      frame_offset += step;

      if (frame_offset >= OLED_DISPLAY_WIDTH) {
        frame_offset = frame_start_offset - ANIM_FRAME_WIDTH + step;
      }
    } else if (frame_offset > (OLED_DISPLAY_WIDTH - ANIM_FRAME_WIDTH) || frame_offset < frame_start_offset) {
      frame_offset = frame_start_offset;
    }
    #endif
  }

  if (ANIM_RENDER_WPM) {
    oled_render_wpm();
  }
}
