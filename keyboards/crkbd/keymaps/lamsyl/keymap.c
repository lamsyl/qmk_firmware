// Copyright 2023 @lamsyl
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

#define OSM_CAG OSM(MOD_LCTL|MOD_LALT|MOD_LGUI)

enum custom_keycodes {
    CAP3 = SAFE_RANGE,
    CAP4,
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    // Cmd [+ Shift] + Esc -> Cmd [+ Shift] + Tab
    // Ctrl [+ Shift] + Esc -> Ctrl [+ Shift] + Tab
    // Use ` (KC_GRV) to escape
    case KC_ESC:
        if (
            get_mods() ==   MOD_BIT(KC_LCMD)                      ||
            get_mods() == ( MOD_BIT(KC_LCMD) | MOD_BIT(KC_LSFT) ) ||
            get_mods() ==   MOD_BIT(KC_LCTL)                      ||
            get_mods() == ( MOD_BIT(KC_LCTL) | MOD_BIT(KC_LSFT) )
        ) {
            if (record->event.pressed) {
                register_code(KC_TAB);
            } else {
                unregister_code(KC_TAB);
            }
            return false;
        }
        return true;

    case KC_GRV:
        if (
            get_mods() == MOD_BIT(KC_LCMD) ||
            get_mods() == MOD_BIT(KC_LCTL)
        ) {
            if (record->event.pressed) {
                SEND_STRING(SS_TAP(X_ESC));
            }
            return false;
        }
        return true;

    case CAP3:
        if (record->event.pressed) {
            SEND_STRING(SS_LCMD(SS_LSFT("3")));
        }
        return false;

    case CAP4:
        if (record->event.pressed) {
            SEND_STRING(SS_LCMD(SS_LSFT("4")));
        }
        return false;
    }
    return true;
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_ESC,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,   KC_GRV,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LCTL,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                         KC_H,    KC_J,    KC_K,    KC_L,   KC_UP, KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_N,    KC_M,  KC_TAB, KC_LEFT, KC_DOWN, KC_RGHT,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LOPT, KC_LCMD,  OSL(3),     KC_ENT,  KC_SPC,   MO(1)
                                      //`--------------------------'  `--------------------------'

  ),

    [1] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
        TO(0),    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                      KC_BSLS,   KC_LT,   KC_GT, KC_SLSH, KC_QUOT, OSM_CAG,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,                      KC_PIPE, KC_LPRN, KC_RPRN, KC_COLN, KC_SCLN,  KC_DEL,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, KC_MINS, KC_PLUS, KC_UNDS,  KC_EQL, KC_MUTE,                      KC_COMM, KC_LBRC, KC_RBRC,  KC_DOT, KC_QUES,   TO(2),
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______, _______, KC_MUTE,    _______, _______, _______
                                      //`--------------------------'  `--------------------------'
  ),

    [2] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
        TO(0), XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_VOLU,                        KC_P7,   KC_P8,   KC_P9, KC_PMNS, KC_PSLS, _______,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_VOLD,                        KC_P4,   KC_P5,   KC_P6, KC_PPLS, KC_PAST, KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_MUTE,                        KC_P1,   KC_P2,   KC_P3, KC_COMM, KC_QUES, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______,  KC_SPC,  KC_ENT,    KC_PEQL,   KC_P0, KC_PDOT
                                      //`--------------------------'  `--------------------------'
  ),

    [3] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
        TO(0), KC_EXLM,   KC_AT, KC_HASH, KC_DLR,  KC_PERC,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_HOME,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, KC_CIRC, KC_AMPR, KC_ASTR,    CAP3,    CAP4,                      XXXXXXX, KC_PGDN, KC_PGUP, XXXXXXX,   KC_UP,  KC_END,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, KC_MINS, KC_PLUS, KC_UNDS,  KC_EQL, KC_RSFT,                      XXXXXXX, XXXXXXX, XXXXXXX, KC_LEFT, KC_DOWN, KC_RGHT,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          XXXXXXX, XXXXXXX,   TO(1),     KC_ESC, _______, KC_RCTL
                                      //`--------------------------'  `--------------------------'
  ),
};
