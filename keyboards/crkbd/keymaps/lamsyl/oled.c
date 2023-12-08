oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (is_keyboard_master()) {
        return OLED_ROTATION_270;
    }
    return rotation;
}

static void write_empty_line(void) {
    static const char PROGMEM empty_line[] = {
        0x20, 0x20, 0x20, 0x20, 0x20, 0
    };
    oled_write_P(empty_line, false);
}

static void render_status(void) {
    static const char PROGMEM binary_00[] = {
        0x20, 0x20, 0x30, 0x30, 0x20, 0
    };
    static const char PROGMEM binary_01[] = {
        0x20, 0x20, 0x30, 0x31, 0x20, 0
    };
    static const char PROGMEM binary_10[] = {
        0x20, 0x20, 0x31, 0x30, 0x20, 0
    };
    static const char PROGMEM binary_11[] = {
        0x20, 0x20, 0x31, 0x31, 0x20, 0
    };

    static const char PROGMEM qwerty_layer_logo[] = {
        0x20, 0x20, 0x9b, 0x9c, 0x20, 0
    };
    static const char PROGMEM code_layer_logo[] = {
        0x20, 0x9a, 0x9b, 0x9c, 0x20, 0
    };
    static const char PROGMEM numpad_layer_logo[] = {
        0x20, 0x20, 0x9b, 0x9c, 0x03, 0
    };
    static const char PROGMEM symbol_layer_logo[] = {
        0x20, 0x9a, 0x9b, 0x9c, 0x03, 0
    };

    oled_clear();
    switch (get_highest_layer(layer_state)) {
    case _QWERTY:
        write_empty_line();
        oled_write_P(binary_00, false);
        write_empty_line();
        oled_write_P(qwerty_layer_logo, false);
        break;

    case _CODE:
        write_empty_line();
        oled_write_P(binary_01, false);
        write_empty_line();
        oled_write_P(code_layer_logo, false);
        break;

    case _NUMPAD:
        write_empty_line();
        oled_write_P(binary_10, false);
        write_empty_line();
        oled_write_P(numpad_layer_logo, false);
        break;

    case _SYMBOL:
        write_empty_line();
        oled_write_P(binary_11, false);
        write_empty_line();
        oled_write_P(symbol_layer_logo, false);
        break;
    }
}

static void render_logo(void) {
    static const char PROGMEM custom_logo[] = {
        255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,127, 63,159,207,239,231,247,243,251,251,251,251,251,251,243,247,247,231,239,207, 31,127,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,
        255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,  7,241,252,254,255,255,255,211,211,223,223,223,223,223,223,223,211,243,255,255,255,255,255,255,254,240,  7,127,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,
        255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,252,129, 55,  7,247,247,195,223,223,195,247,247,247,247,195,159,159,195,247,247,247,247,247,  3,251,251,251,248,243,199,159, 63,255,255,255,255,255,255,255,255,255,255,255,255,255,255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,
        255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,248,251,251,251,227,203,211,211,211,211,219,155,187,185,187,179,147,209,209,209,212,222,223,239,231,247,243,251,252,252,255,255,255,255,255,255,255,255,255,255,255,255,255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,
    };
    oled_write_raw_P(custom_logo, sizeof(custom_logo));
}

bool oled_task_user(void) {
    if (is_keyboard_master()) {
        render_status();
    } else {
        render_logo();
    }
    return false;
}
