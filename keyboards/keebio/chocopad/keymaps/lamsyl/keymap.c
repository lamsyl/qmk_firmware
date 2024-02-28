// Copyright 2024 @lamsyl
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

#define _BASE 0
#define _FN1 1

enum custom_keycodes {
    NOQC = SAFE_RANGE,  // No Query Cache
    RC,                 // Rails Console
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
  case NOQC:
    if (record->event.pressed) {
      SEND_STRING("Mongoid::QueryCache.enabled = false");
    }
    return false;

  case RC:
    if (record->event.pressed) {
      SEND_STRING("OTEL_LOG_LEVEL=FATAL bundle exec rails c");
    }
    return false;
  }

  return true;
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_BASE] = LAYOUT_ortho_4x4(
    NOQC,     XXXXXXX,  XXXXXXX,  RC,
    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
    MO(_FN1), XXXXXXX,  XXXXXXX,  KC_ENT
  ),

  [_FN1] = LAYOUT_ortho_4x4(
    _______,  _______,  _______,  _______,
    _______,  _______,  _______,  _______,
    _______,  _______,  _______,  _______,
    _______,  _______,  _______,  QK_BOOT
  )

};
