// Copyright 2024 @lamsyl
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

#define _BASE 0
#define _FN1 1

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_BASE] = LAYOUT_ortho_4x4(
    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
    MO(_FN1), XXXXXXX,  XXXXXXX,  XXXXXXX
  ),

  [_FN1] = LAYOUT_ortho_4x4(
    _______,  _______,  _______,  _______,
    _______,  _______,  _______,  _______,
    _______,  _______,  _______,  _______,
    _______,  _______,  _______,  QK_BOOT
  )

};
