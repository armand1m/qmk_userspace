/*
Copyright 2019 @foostan
Copyright 2020 Drashna Jaelre <@drashna>
Copyright 2021 Armando Magalhaes <@armand1m>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H

enum custom_keycodes {
    ARROW_FUNCTION = SAFE_RANGE,
    REACT_COMPONENT
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
      case ARROW_FUNCTION:
        if (record->event.pressed) {
            SEND_STRING("() => {}");
        } else {
            SEND_STRING(SS_TAP(X_LEFT) SS_TAP(X_ENTER));
        }
        return false;

      case REACT_COMPONENT:
        if (record->event.pressed) {
            SEND_STRING("const ReactComponent: React.FC<Props> = (props) => {\n  return <p>Hello</p>;\n}");
        }
        return false;
    }

    return true;
};

enum crkbd_layers {
  _DEFAULT,
  _NUMBERS,
  _SYMBOLS,
  _COMMANDS,
  _GAMING,
};

#define KC_NUMBERS    LT(_NUMBERS, KC_ESC)
#define KC_LSYMBOLS   LT(_SYMBOLS, KC_A)
#define KC_LCOMMANDS  LT(_COMMANDS, KC_S)
#define KC_LCTL_Z     MT(MOD_LCTL, KC_Z)
#define KC_RSFT_ENT   MT(MOD_RSFT, KC_ENT)
#define KC_RCTL_SLSH  MT(MOD_RCTL, KC_SLSH)
#define KC_SPOTLIGHT  LGUI(KC_SPACE)
#define KC_CMD_SPC    LGUI_T(KC_SPC)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_DEFAULT] = LAYOUT_split_3x6_3(
          KC_TAB,        KC_Q,         KC_W,    KC_E,    KC_R,    KC_T,           KC_Y,    KC_U,    KC_I,     KC_O,          KC_P,     KC_BSPC,
      KC_NUMBERS, KC_LSYMBOLS, KC_LCOMMANDS,    KC_D,    KC_F,    KC_G,           KC_H,    KC_J,    KC_K,     KC_L,       KC_SCLN,     KC_QUOT,
         KC_LSFT,   KC_LCTL_Z,         KC_X,    KC_C,    KC_V,    KC_B,           KC_N,    KC_M, KC_COMM,   KC_DOT,  KC_RCTL_SLSH,     KC_RSFT,
                                          KC_LALT, KC_SPOTLIGHT, KC_CMD_SPC,    KC_RSFT_ENT,  MO(_SYMBOLS), KC_RALT
  ),

  [_NUMBERS] = LAYOUT_split_3x6_3(
      _______,      KC_1,      KC_2,      KC_3,      KC_4,      KC_5,                    KC_6,      KC_7,      KC_8,        KC_9,      KC_0, _______,
      _______,   _______,   _______,   XXXXXXX,   XXXXXXX,   XXXXXXX,                 KC_LEFT,   KC_DOWN,     KC_UP,    KC_RIGHT,   XXXXXXX, _______,
      _______,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,                 XXXXXXX,   XXXXXXX,   _______,     _______,   _______, _______,
                                                  _______, _______, _______,     _______, _______, _______
  ),

  [_SYMBOLS] = LAYOUT_split_3x6_3(
      _______,   KC_EXLM,     KC_AT,           KC_HASH,         KC_DLR, KC_PERC,             KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, _______,
      _______,   _______,   _______,           XXXXXXX, ARROW_FUNCTION,   KC_LT,             KC_MINS,  KC_EQL, KC_LBRC, KC_RBRC, KC_BSLS,  KC_GRV,
      _______,   XXXXXXX,   XXXXXXX,   REACT_COMPONENT,        XXXXXXX,   KC_GT,             KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE, KC_TILD,
                                                  _______, _______, _______,     _______, _______, _______
  ),

  [_COMMANDS] = LAYOUT_split_3x6_3(
      _______,   XXXXXXX,   XXXXXXX,   XXXXXXX, LALT(LSFT(KC_0)),   XXXXXXX,             XXXXXXX,       XXXXXXX,       XXXXXXX, XXXXXXX, LGUI(LSFT(KC_4)), XXXXXXX,
      _______,   _______,   _______,   XXXXXXX,          XXXXXXX,   KC_BRIGHTNESS_UP,             XXXXXXX, LGUI(KC_MINS), LGUI(KC_PLUS), XXXXXXX,          XXXXXXX, XXXXXXX,
      _______,   XXXXXXX,   XXXXXXX,   XXXXXXX,          XXXXXXX,   KC_BRIGHTNESS_DOWN,             XXXXXXX,       KC_AUDIO_MUTE,       XXXXXXX, XXXXXXX,          XXXXXXX, XXXXXXX,
                            KC_MEDIA_PREV_TRACK, KC_AUDIO_VOL_DOWN, TG(_GAMING),     KC_MEDIA_PLAY_PAUSE, KC_AUDIO_VOL_UP, KC_MEDIA_NEXT_TRACK
  ),

  [_GAMING] = LAYOUT_split_3x6_3(
     KC_TAB,        KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,           XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,                  XXXXXXX,       KC_BSPC,
     KC_ESC,        KC_A,    KC_S,    KC_D,    KC_F,    KC_G,           XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,               XXXXXXX,       XXXXXXX,
     MOD_LSFT, MT(MOD_LCTL, KC_Z),    KC_1,    KC_2,    KC_3,    KC_4,           XXXXXXX,    XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX,
                                     TG(_GAMING),       XXXXXXX,   KC_SPC,    XXXXXXX,  XXXXXXX, XXXXXXX
  ),
};

#ifdef OLED_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {

  if (!is_keyboard_master()) {
    return OLED_ROTATION_180; // flips the display 180 degrees if offhand
  }

  return rotation;
}

char wpm_str[9];

void oled_render_layer_state(void) {
    oled_write_P(PSTR("Layer: "), false);

    switch (biton32(layer_state)) {
        case _DEFAULT:
            oled_write_ln_P(PSTR("Default"), false);
            break;
        case _NUMBERS:
            oled_write_ln_P(PSTR("Numbers"), false);
            break;
        case _SYMBOLS:
            oled_write_ln_P(PSTR("Symbols"), false);
            break;
        case _COMMANDS:
            oled_write_ln_P(PSTR("Commands"), false);
            break;
        case _GAMING:
            oled_write_ln_P(PSTR("Gaming"), false);
            break;
    }
}

void oled_render_wpm(void) {
    sprintf(wpm_str, "WPM: %03d", get_current_wpm());
    oled_write(wpm_str, false);
}

void oled_render_image(void) {
    // 'Love Death Robots logo', 128x32px
    static const char PROGMEM image[] = {
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0xe0, 0xc0, 0x80, 0xc0, 0xc0, 0xe0, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x0f, 0x0f, 0x07, 0x07, 0x0f, 0x1c, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf8, 0xfc, 0xfc, 0xf8, 0xf0, 0xe0, 0xc0, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x07, 0x07, 0x07, 0x03, 0x01, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    };
    oled_write_raw_P(image, sizeof(image));
}

void oled_task_user(void) {
  if (is_master) {
        oled_render_layer_state();
        oled_render_wpm();
    } else {
        oled_render_image();
    }
}
#endif // OLED_DRIVER_ENABLE

#ifdef RGBLIGHT_ENABLE
layer_state_t layer_state_set_user(layer_state_t state) {
  switch (biton32(state)) {
    case _NUMBERS:
      rgblight_sethsv_noeeprom(HSV_AZURE);
      break;

    case _SYMBOLS:
      rgblight_sethsv_noeeprom(HSV_TEAL);
      break;

    case _COMMANDS:
      rgblight_sethsv_noeeprom(HSV_BLUE);
      break;

    case _GAMING:
      rgblight_sethsv_noeeprom(HSV_RED);
      break;

    default:
      rgblight_sethsv_noeeprom(HSV_SPRINGGREEN);
      break;
  }

  return state;
}
#endif // RGBLIGHT_ENABLE
