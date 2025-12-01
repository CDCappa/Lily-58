#include QMK_KEYBOARD_H
#include "skull_anim.h"

enum layers {
    _BASE = 0,
    _LAYER1,
    _LAYER2,
    _ADJUST,
};

enum custom_keycodes {
    MC_ENE = SAFE_RANGE,
    MC_ENEM,
    MC_SENT,  // Shift+Enter
};

// Tap Dance declarations
enum {
    TD_LPRN,  // ( { [
    TD_RPRN,  // ) } ]
};

// Tap Dance definitions - using tap_code to avoid key repeat on hold
void td_lprn_finished(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        if (state->pressed) {
            tap_code(KC_LBRC);
        } else {
            tap_code16(S(KC_9));
        }
    } else if (state->count == 2) {
        tap_code16(S(KC_LBRC));
    }
}

void td_lprn_reset(tap_dance_state_t *state, void *user_data) {}

void td_rprn_finished(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        if (state->pressed) {
            tap_code(KC_RBRC);
        } else {
            tap_code16(S(KC_0));
        }
    } else if (state->count == 2) {
        tap_code16(S(KC_RBRC));
    }
}

void td_rprn_reset(tap_dance_state_t *state, void *user_data) {}

tap_dance_action_t tap_dance_actions[] = {
    [TD_LPRN] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, td_lprn_finished, td_lprn_reset),
    [TD_RPRN] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, td_rprn_finished, td_rprn_reset),
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[_BASE] = LAYOUT(
  S(KC_2),  S(KC_5),  TD(TD_LPRN), TD(TD_RPRN), KC_QUOT, S(KC_BSLS),                KC_DOT,   KC_SCLN,  KC_F5,    KC_F4,    KC_F2,    KC_GRV,
  KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,                           KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_EQL,
  KC_LCTL,  KC_A,     KC_S,     KC_D,     KC_F,     KC_G,                           KC_H,     KC_J,     KC_K,     KC_L,     KC_COMM,  KC_MINS,
  KC_LSFT,  KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_ENT,     KC_ESC,   KC_N,     KC_M,     MC_ENE,   S(KC_7),  MO(1),    S(KC_8),
                                KC_LGUI,  KC_RALT,  KC_LALT,  KC_SPC,     KC_BSPC,  KC_SLSH,  S(KC_1),  S(KC_3)
),

[_LAYER1] = LAYOUT(
  KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,                          KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,
  KC_TAB,   KC_NO,    KC_UP,    KC_NO,    KC_NO,    KC_NO,                          S(KC_7),  S(KC_6),  KC_NO,    KC_NO,    KC_NO,    KC_NO,
  KC_LCTL,  KC_LEFT,  KC_DOWN,  KC_RGHT,  KC_NO,    KC_NO,                          KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,
  KC_LSFT,  KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    MC_SENT,    KC_ESC,   KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,
                                KC_NO,    KC_RALT,  KC_LALT,  KC_SPC,     KC_DEL,   KC_NO,    KC_NO,    KC_NO
),

[_LAYER2] = LAYOUT(
  KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,                          KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,
  KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,                          KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,
  KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,                          KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,
  KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,      KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,
                                KC_NO,    KC_NO,    KC_NO,    KC_NO,      KC_NO,    KC_NO,    KC_NO,    KC_NO
),

[_ADJUST] = LAYOUT(
  KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,                          KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,
  KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,                          KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,
  KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,                          KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,
  KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,      KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,
                                KC_NO,    KC_NO,    KC_NO,    KC_NO,      KC_NO,    KC_NO,    KC_NO,    KC_NO
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
        case MC_SENT:
            if (record->event.pressed) {
                tap_code16(S(KC_ENT));
            }
            return false;
    }
    return true;
}

#ifdef OLED_ENABLE
// static uint8_t current_frame = 0;
// static uint32_t anim_timer = 0;

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (!is_keyboard_master()) return OLED_ROTATION_180;
    return rotation;
}

static void render_skull(void) {
    // Solo craneo estatico para debug
    oled_write_raw_P(skull_frames[0], SKULL_FRAME_SIZE);
}

static void render_status(void) {
    oled_write_P(PSTR("Layer: "), false);
    switch (get_highest_layer(layer_state)) {
        case _BASE:    oled_write_ln_P(PSTR("BASE"), false); break;
        case _LAYER1:  oled_write_ln_P(PSTR("SYMBOLS"), false); break;
        case _LAYER2:  oled_write_ln_P(PSTR("FN/NAV"), false); break;
        case _ADJUST:  oled_write_ln_P(PSTR("ADJUST"), false); break;
    }
    
    // Mostrar WPM
    oled_write_P(PSTR("WPM: "), false);
    oled_write(get_u8_str(get_current_wpm(), ' '), false);
}

bool oled_task_user(void) {
    // Debug: mostrar craneo en AMBOS lados
    render_skull();
    return false;
}
#endif
