// Copyright 2023 @lamsyl
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

enum custom_layers {
    _QWERTY,
    _CODE,
    _NUMPAD,
    _SYMBOL,
};

#ifdef OLED_ENABLE
    #include "oled.c"
#endif

// combine with layer 1 key (same layer):
// OSL(1) -> OSM_CAG -> KC_RGHT = Ctrl+Opt+Cmd+Right
//
// combine with layer 0 key (different layer):
// OSL(1) -> OSM_CAG -> TO(0) -> KC_Q = Ctrl+Opt+Cmd+Q
#define OSM_CAG OSM(MOD_LCTL|MOD_LALT|MOD_LGUI)

#define LT3GRV  LT(3, KC_GRV)

enum custom_keycodes {
    FESC = SAFE_RANGE,  // Force escape by sending literal `ESC` without special handling
    CAP3,               // Screenshot (Cmd+Shift+3), hold ctrl to copy to clipboard
    CAP4,               // Screenshot (Cmd+Shift+4), hold ctrl to copy to clipboard
    MSCTL,              // Mission Control (Ctrl+Up)
    APPEXP,             // App Expose (Ctrl+Down)
    SWPLEFT,            // Swipe left (Ctrl+Left)
    SWPRGHT,            // Swipe right (Ctrl+Right)
    LARGER,             // Large (Cmd+=)
    SMALLER,            // Small (Cmd+-)
    RESIZE,             // Resize (Cmd+0)
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case FESC:
        if (record->event.pressed) {
            SEND_STRING(SS_TAP(X_ESC));
        }
        return false;

    // Cmd [+ Shift] + Esc -> Cmd [+ Shift] + Tab
    // Ctrl [+ Shift] + Esc -> Ctrl [+ Shift] + Tab
    // Cmd + Ctrl + Esc -> Cmd + Ctrl + Tab (Switch windows of same app, default is cmd+`)
    // Use FESC to escape
    case KC_ESC:
        if (
            get_mods() ==   MOD_BIT(KC_LCMD)                      ||
            get_mods() == ( MOD_BIT(KC_LCMD) | MOD_BIT(KC_LSFT) ) ||
            get_mods() ==   MOD_BIT(KC_LCTL)                      ||
            get_mods() == ( MOD_BIT(KC_LCTL) | MOD_BIT(KC_LSFT) ) ||
            get_mods() == ( MOD_BIT(KC_LCMD) | MOD_BIT(KC_LCTL) )
        ) {
            if (record->event.pressed) {
                register_code(KC_TAB);
            } else {
                unregister_code(KC_TAB);
            }
            return false;
        }
        if (!record->event.pressed) {
            unregister_code(KC_TAB);
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

    case MSCTL:
        if (record->event.pressed) {
            SEND_STRING(SS_LCTL(SS_TAP(X_UP)));
        }
        return false;

    case APPEXP:
        if (record->event.pressed) {
            SEND_STRING(SS_LCTL(SS_TAP(X_DOWN)));
        }
        return false;

    case SWPLEFT:
        if (record->event.pressed) {
            SEND_STRING(SS_LCTL(SS_TAP(X_LEFT)));
        }
        return false;

    case SWPRGHT:
        if (record->event.pressed) {
            SEND_STRING(SS_LCTL(SS_TAP(X_RGHT)));
        }
        return false;

    case LARGER:
        if (record->event.pressed) {
            SEND_STRING(SS_LCMD("="));
        }
        return false;

    case SMALLER:
        if (record->event.pressed) {
            SEND_STRING(SS_LCMD("-"));
        }
        return false;

    case RESIZE:
        if (record->event.pressed) {
            SEND_STRING(SS_LCMD("0"));
        }
        return false;
    }

    return true;
};

void leader_end_user(void) {
    if (leader_sequence_one_key(KC_V)) {
        // Leader, v => Move instead of paste
        SEND_STRING(SS_LCMD(SS_LOPT("v")));
    } else if (leader_sequence_one_key(KC_H)) {
        // Leader, h => HOME
        SEND_STRING(SS_TAP(X_HOME));
    } else if (leader_sequence_one_key(KC_E)) {
        // Leader, e => END
        SEND_STRING(SS_TAP(X_END));
    }
}

// Go to _QWERTY (base layer) via the same combo:
// _QWERTY => OSL(1)  -> TO(0)
// _CODE   => TO(2)   -> TO(0)
// _NUMPAD => XXXXXXX -> TO(0)
// _SYMBOL => KC_ROPT -> TO(0)
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_ESC,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,   LT3GRV,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LCTL,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                         KC_H,    KC_J,    KC_K,    KC_L,   KC_UP, KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_N,    KC_M,  KC_TAB, KC_LEFT, KC_DOWN, KC_RGHT,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LOPT, KC_LCMD,  OSL(3),     KC_ENT,  KC_SPC,  OSL(1)
                                      //`--------------------------'  `--------------------------'
  ),

    [_CODE] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
        TO(0),    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                      XXXXXXX, KC_LCBR, KC_RCBR, KC_SLSH, KC_BSLS,    FESC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,                      KC_PIPE, KC_LPRN, KC_RPRN, KC_COLN, KC_SCLN,  KC_DEL,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, KC_QUOT, KC_DQUO, KC_VOLD, KC_VOLU, KC_MUTE,                      KC_COMM, KC_LBRC, KC_RBRC,  KC_DOT, KC_QUES, OSM_CAG,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______, _______, _______,    KC_RGHT, KC_MUTE,   TO(2)
                                      //`--------------------------'  `--------------------------'
  ),

    [_NUMPAD] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
        TO(0), XXXXXXX,   KC_UP, XXXXXXX, KC_PAST, KC_PSLS,                        KC_P7,   KC_P8,   KC_P9, KC_SLSH, KC_BSLS, KC_PEQL,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       KC_TAB, KC_LEFT, KC_DOWN, KC_RGHT, KC_PPLS, KC_PMNS,                        KC_P4,   KC_P5,   KC_P6, KC_COLN, KC_SCLN, KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                        KC_P1,   KC_P2,   KC_P3,  KC_DOT, KC_QUES, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          XXXXXXX,  KC_SPC,  KC_ENT,      KC_P0, KC_COMM, XXXXXXX
                                      //`--------------------------'  `--------------------------'
  ),

    [_SYMBOL] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
        TO(0), KC_EXLM,   KC_AT, KC_HASH, KC_DLR,  KC_PERC,                      XXXXXXX, XXXXXXX, XXXXXXX, SMALLER,  LARGER,  KC_ESC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_CAPS, KC_CIRC, KC_AMPR, KC_ASTR,    CAP3,    CAP4,                      KC_LEFT, KC_DOWN,   KC_UP, KC_RGHT,   MSCTL,  RESIZE,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
        KC_LT, KC_MINS, KC_PLUS, KC_UNDS,  KC_EQL,   KC_GT,                      XXXXXXX, KC_PGDN, KC_PGUP, SWPLEFT,  APPEXP, SWPRGHT,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LCTL,  KC_SPC, QK_LEAD,    XXXXXXX, KC_RCMD, KC_ROPT
                                      //`--------------------------'  `--------------------------'
  ),
};
