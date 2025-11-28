#include QMK_KEYBOARD_H

enum layers {
    _BASE = 0,
    _LAYER1,
    _LAYER2,
    _ADJUST,
};

enum custom_keycodes {
    MC_ENE = SAFE_RANGE,
    MC_ENEM,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* BASE - Layer 0 (desde VIA JSON)
 * Lily58 tiene 58 teclas: 4 filas de 6 + 2 thumb inner + 4 thumb outer por lado
 */
[_BASE] = LAYOUT(
  S(KC_2),  S(KC_5),  KC_LBRC,  KC_RBRC,  KC_QUOT,  S(KC_BSLS),                     KC_GRV,   KC_F2,    KC_F4,    KC_F5,    KC_SCLN,  KC_DOT,
  KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,                           KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_MINS,
  KC_LCTL,  KC_A,     KC_S,     KC_D,     KC_F,     KC_G,                           KC_H,     KC_J,     KC_K,     KC_L,     KC_COMM,  KC_EQL,
  KC_LSFT,  KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_NO,      MO(1),    KC_N,     KC_M,     KC_NO,    S(KC_7),  S(KC_8),  KC_NO,
                                KC_LGUI,  MO(2),    KC_LALT,  KC_SPC,     KC_ENT,   KC_BSPC,  KC_SLSH,  KC_ESC
),

/* LAYER1 - Simbolos */
[_LAYER1] = LAYOUT(
  KC_NO,    KC_NO,    S(KC_9),  S(KC_0),  KC_NO,    KC_NO,                          KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_G,
  KC_NO,    KC_BSLS,  S(KC_4),  S(KC_6),  KC_JYEN,  KC_NO,                          KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,
  KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,                          KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,
  KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,      KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,
                                KC_NO,    KC_NO,    KC_NO,    KC_NO,      KC_NO,    KC_NO,    KC_NO,    KC_NO
),

/* LAYER2 - F-keys y navegacion */
[_LAYER2] = LAYOUT(
  _______,  _______,  _______,  _______,  _______,  _______,                        _______,  _______,  _______,  _______,  _______,  _______,
  KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,                          KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,
  _______,  _______,  _______,  _______,  _______,  _______,                        KC_NO,    KC_LEFT,  KC_DOWN,  KC_UP,    KC_RGHT,  KC_NO,
  _______,  _______,  _______,  _______,  _______,  _______,  KC_NO,      KC_BSLS,  S(KC_EQL),KC_EQL,   KC_LBRC,  KC_RBRC,  KC_BSLS,  KC_NO,
                                _______,  _______,  _______,  _______,    _______,  _______,  _______,  _______
),

/* ADJUST - Layer1 + Layer2 */
[_ADJUST] = LAYOUT(
  QK_BOOT,  KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,                          KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,
  KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,                          KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,
  KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,                          KC_NO,    KC_VOLD,  KC_VOLU,  KC_MUTE,  KC_NO,    KC_NO,
  KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,      KC_NO,    MC_ENE,   KC_MPRV,  KC_MPLY,  KC_MNXT,  MC_ENEM,  KC_NO,
                                _______,  _______,  _______,  _______,    _______,  _______,  _______,  _______
)
};

layer_state_t layer_state_set_user(layer_state_t state) {
    return update_tri_layer_state(state, _LAYER1, _LAYER2, _ADJUST);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case MC_ENE:
            if (record->event.pressed) {
                register_code(KC_RALT);
                tap_code(KC_N);
                unregister_code(KC_RALT);
            }
            return false;
        case MC_ENEM:
            if (record->event.pressed) {
                register_code(KC_RSFT);
                register_code(KC_RALT);
                tap_code(KC_N);
                unregister_code(KC_RALT);
                unregister_code(KC_RSFT);
            }
            return false;
    }
    return true;
}

#ifdef OLED_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (!is_keyboard_master()) return OLED_ROTATION_180;
    return rotation;
}

bool oled_task_user(void) {
    oled_write_P(PSTR("Layer: "), false);
    switch (get_highest_layer(layer_state)) {
        case _BASE:    oled_write_ln_P(PSTR("BASE"), false); break;
        case _LAYER1:  oled_write_ln_P(PSTR("SYMBOLS"), false); break;
        case _LAYER2:  oled_write_ln_P(PSTR("FN/NAV"), false); break;
        case _ADJUST:  oled_write_ln_P(PSTR("ADJUST"), false); break;
    }
    return false;
}
#endif
