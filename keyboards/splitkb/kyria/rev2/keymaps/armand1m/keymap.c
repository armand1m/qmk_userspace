/* Copyright 2019 Thomas Baart <thomas@splitkb.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H

#define ANIM_INVERT true
#define ANIM_RENDER_WPM true
#define FAST_TYPE_WPM 45 // Switch to fast animation when over words per minute

#ifdef OLED_ENABLE
    #include "demon.c"
#endif

enum custom_keycodes {
    ARROW_FUNCTION = SAFE_RANGE,
    REACT_COMPONENT
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
      case ARROW_FUNCTION:
        if (record->event.pressed) {
            SEND_STRING("() => {\n}");
        }
        return false;

      case REACT_COMPONENT:
        if (record->event.pressed) {
            SEND_STRING("const Component = (props: Props) => {\n  return <div></div>;\n}");
        }
        return false;
    }

    return true;
};

enum layers {
  _DEFAULT,
  _NUMBERS,
  _SYMBOLS,
  _COMMANDS,
};

// Aliases for readability
#define KC_NUMBERS    LT(_NUMBERS, KC_ESC)
#define KC_LSYMBOLS   LT(_SYMBOLS, KC_A)
#define KC_LCOMMANDS  LT(_COMMANDS, KC_S)
#define KC_LCTL_Z     MT(MOD_LCTL, KC_Z)
#define KC_RSFT_ENT   MT(MOD_RSFT, KC_ENT)
#define KC_RCTL_SLSH  MT(MOD_RCTL, KC_SLSH)
#define KC_SPOTLIGHT  LGUI(KC_SPACE)
#define KC_TERMINAL   LGUI(KC_ENT)
#define KC_NEXT_SPACE LGUI(LCTL(LALT(KC_N)))
#define KC_PREV_SPACE LGUI(LCTL(LALT(KC_P)))
#define KC_CMD_SPC    LGUI_T(KC_SPC)
#define KC_SCREENSHOT LGUI(LSFT(KC_4))
#define KC_ZOOM_IN    LGUI(KC_PLUS)
#define KC_ZOOM_OUT   LGUI(KC_MINS)

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_DEFAULT] = LAYOUT(
     KC_TAB  , KC_Q ,  KC_W   ,  KC_E  ,   KC_R ,   KC_T ,                                        KC_Y,   KC_U ,  KC_I ,   KC_O ,  KC_P , KC_BSPC,
     KC_NUMBERS , KC_LSYMBOLS ,  KC_LCOMMANDS  ,  KC_D  ,   KC_F ,   KC_G ,                       KC_H,   KC_J ,  KC_K ,   KC_L ,  KC_SCLN, KC_QUOT,
     KC_LSFT , KC_LCTL_Z ,  KC_X   ,  KC_C  ,   KC_V ,   KC_B , XXXXXXX,XXXXXXX,                  XXXXXXX, XXXXXXX, KC_N,   KC_M ,KC_COMM, KC_DOT ,  KC_RCTL_SLSH, KC_RSFT,
                      KC_AUDIO_MUTE , KC_LALT, KC_SPOTLIGHT, KC_CMD_SPC, KC_PREV_SPACE,          KC_NEXT_SPACE, KC_RSFT_ENT,MO(_SYMBOLS), KC_RCTL, KC_TERMINAL
    ),
    [_NUMBERS] = LAYOUT(
      _______,   KC_1,   KC_2,   KC_3,   KC_4,   KC_5,                                          KC_6,   KC_7,      KC_8,    KC_9,   KC_0, _______,
      _______,_______,_______,XXXXXXX,XXXXXXX,XXXXXXX,                                          KC_LEFT,KC_DOWN,  KC_UP,KC_RIGHT,_______, _______,
      _______,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,_______, _______,      _______,  _______, XXXXXXX,XXXXXXX,_______, _______,_______, _______,
                           _______, _______, _______, _______, _______,      _______, _______, _______, _______, _______
    ),
    [_SYMBOLS] = LAYOUT(
      _______,KC_EXLM,  KC_AT,KC_HASH,KC_DLR,KC_PERC,                                                KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, _______,
      _______,_______,_______,XXXXXXX,ARROW_FUNCTION,KC_LT,                                          KC_MINS,  KC_EQL, KC_LBRC, KC_RBRC, KC_BSLS,  KC_GRV,
      _______,XXXXXXX,XXXXXXX,REACT_COMPONENT,XXXXXXX,KC_GT,_______, _______,      _______,  _______,KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE, KC_TILD,
                                 _______, _______, _______, _______, _______,      _______, _______, _______, _______, _______
    ),
    [_COMMANDS] = LAYOUT(
        _______,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,                                         XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,
        _______,_______,_______,XXXXXXX,XXXXXXX,XXXXXXX,                                         XXXXXXX,KC_ZOOM_OUT,KC_ZOOM_IN,XXXXXXX,XXXXXXX,XXXXXXX,
        _______,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,_______,_______,         _______,_______,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,
                     _______,_______,KC_MEDIA_PREV_TRACK,_______,_______,       _______,KC_MEDIA_PLAY_PAUSE,KC_MEDIA_NEXT_TRACK,_______,_______
    ),
};

/* The default OLED and rotary encoder code can be found at the bottom of qmk_firmware/keyboards/splitkb/kyria/rev1/rev1.c
 * These default settings can be overriden by your own settings in your keymap.c
 * For your convenience, here's a copy of those settings so that you can uncomment them if you wish to apply your own modifications.
 * DO NOT edit the rev1.c file; instead override the weakly defined default functions by your own.
 */

#ifdef OLED_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) { return OLED_ROTATION_180; }

bool oled_task_user(void) {
    if (is_keyboard_master()) {
        oled_write_P(PSTR("\n\nowner: armand1m\n"), false);
        oled_write_P(PSTR("layer: "), false);
        switch (get_highest_layer(layer_state|default_layer_state)) {
            case _DEFAULT:
                oled_write_P(PSTR("default\n"), false);
                break;
            case _NUMBERS:
                oled_write_P(PSTR("numbers\n"), false);
                break;
            case _SYMBOLS:
                oled_write_P(PSTR("symbols\n"), false);
                break;
            case _COMMANDS:
                oled_write_P(PSTR("commands\n"), false);
                break;
            default:
                oled_write_P(PSTR("undefined\n"), false);
        }
        oled_write_P(PSTR("patience is key"), false);

        return false;
    }

    oled_render_animation();

    return false;
}
#endif

#ifdef ENCODER_ENABLE
bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        // Volume control
        if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
    } else if (index == 1) {
        // Switch spaces
        if (clockwise) {
            tap_code16(KC_NEXT_SPACE);
        } else {
            tap_code16(KC_PREV_SPACE);
        }
    }
    return false;
}
#endif

#ifdef RGBLIGHT_ENABLE
void keyboard_post_init_user(void) {
  rgblight_enable_noeeprom(); // Enables RGB, without saving settings
  rgblight_sethsv_noeeprom(HSV_PURPLE);
  rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
}
#endif
