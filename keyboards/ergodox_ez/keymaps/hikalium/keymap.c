#include "action_layer.h"
#include "debug.h"
#include "ergodox_ez.h"
#include "keymap_german.h"
#include "keymap_nordic.h"
#include "version.h"

enum custom_keycodes {
  PLACEHOLDER = SAFE_RANGE,  // can always be here
  EPRM,
  RGB_SLD,
};

//  0  1  2  3  4  5  6                 38 39 40 41 42 43 44
//
//  7  8  9 10 11 12 13                 45 46 47 48 48 50 51
//                   ||                 ||
// 14 15 16 17 18 19                       52 53 54 55 56 57
//                   ||                 ||
// 20 21 22 23 24 25 26                 58 59 60 61 62 63 64
//
// 27 28 29 30 31                             65 66 67 68 69
//                       32 33    70 71
//
//                    || || 34    72 || ||
//                    35 36          74 75
//                    || || 37    73 || ||

#define KX KC_TRANSPARENT

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_ergodox(
        // L
        KC_EQUAL, KC_1, KC_2, KC_3, KC_4, KC_5, KC_LEFT,    // +0
        KC_BSLASH, KC_Q, KC_W, KC_E, KC_R, KC_T, MO(2),     // +7
        KC_LCTRL, KC_A, KC_S, KC_D, KC_F, KC_G,             // +14
        KC_LSHIFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_LANG2,  // +20
        MO(1), KC_LALT, KX, KC_LEFT, KC_RIGHT,              // +27
        KC_ESCAPE, KC_LGUI,                                 // +32
        MO(1), KC_SPACE, KC_BSPACE, LCTL(KC_B),             // +34
        // R
        KC_RIGHT, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINUS,             // +38
        MO(2), KC_Y, KC_U, KC_I, KC_O, KC_P, KC_QUOTE,                // +45
        /**/ KC_H, KC_J, KC_K, KC_L, KC_SCOLON, KC_RCTRL,             // +52
        KC_LANG1, KC_N, KC_M, KC_COMMA, KC_DOT, KC_SLASH, KC_RSHIFT,  // +58
        KC_UP, KC_DOWN, KX, KC_RALT, MO(1),                           // +65
        KC_LALT, KC_COLN,                                             // +70
        MO(1), RCTL(KC_B), KC_TAB, KC_ENTER                           // +72
        ),

    [1] = LAYOUT_ergodox(
        // L
        KC_ESCAPE, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KX,             // +0
        KX, KC_EXLM, KC_AT, KC_LCBR, KC_RCBR, KC_PIPE, KX,            // +7
        KX, KC_HASH, KC_DLR, KC_LPRN, KC_RPRN, KC_GRAVE,              // +14
        KX, KC_PERC, KC_CIRC, KC_LBRACKET, KC_RBRACKET, KC_TILD, KX,  // +20
        KX, KX, KX, KX, KX,                                           // +27
        RGB_MOD, KX,                                                  // +32
        KX, RGB_VAD, RGB_VAI, KX,                                     // +34
        // R
        KX, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11,  // +38
        KX, KC_UP, KC_7, KC_8, KC_9, KC_ASTR, KC_F12,    // +45
        /**/ KC_DOWN, KC_4, KC_5, KC_6, KC_PLUS, KX,     // +52
        KX, KC_AMPR, KC_1, KC_2, KC_3, KC_BSLASH, KX,    // +58
        KX, KC_DOT, KC_0, KC_EQUAL, KX,                  // +65
        RGB_TOG, RGB_SLD,                                // +70
        KX, KX, RGB_HUD, RGB_HUI                         // +72
        ),

    // RESET: Reset the keyboard (for flashing firmware)
    [2] = LAYOUT_ergodox(
        // L
        KX, KX, KX, KX, KX, KX, KX,          // +0
        KX, KX, KX, KX, KX, KX, KX,          // +7
        KX, KX, KX, KX, KX, KX,              // +14
        KX, KX, KX, KX, KX, KX, KX,          // +20
        KX, KX, KX, KC_MS_BTN1, KC_MS_BTN2,  // +27
        KX, KX,                              // +32
        KX, KC_MEDIA_PLAY_PAUSE, KX, KX,     // +34
        // R
        KX, KX, KX, KX, KX, KX, RESET,                               // +38
        KX, KX, KC_MS_BTN1, KC_MS_BTN2, KX, KX, KX,                  // +45
        /**/ KC_MS_LEFT, KC_MS_DOWN, KC_MS_UP, KC_MS_RIGHT, KX, KX,  // +52
        KX, KX, KX, KX, KX, KX, KX,                                  // +58
        KC_AUDIO_VOL_UP, KC_AUDIO_VOL_DOWN, KC_AUDIO_MUTE, KX, KX,   // +65
        KX, KX,                                                      // +70
        KX, KX, KC_MS_BTN2, KC_MS_BTN1                               // +72
        ),

};

const uint16_t PROGMEM fn_actions[] = {[1] = ACTION_LAYER_TAP_TOGGLE(1)};

// leaving this in place for compatibilty with old keymaps cloned and
// re-compiled.
const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt) {
  switch (id) {
    case 0:
      if (record->event.pressed) {
        SEND_STRING(QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
      }
      break;
  }
  return MACRO_NONE;
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    // dynamically generate these.
    case EPRM:
      if (record->event.pressed) {
        eeconfig_init();
      }
      return false;
      break;
    case RGB_SLD:
      if (record->event.pressed) {
        rgblight_mode(1);
      }
      return false;
      break;
  }
  return true;
}

void set_layer_color(uint8_t layer) {
  uint8_t r = (layer == 1) ? 255 : 0;
  uint8_t g = (layer == 2) ? 255 : 0;
  uint8_t b = (layer == 0) ? 255 : 0;
  for (int i = 0; i < DRIVER_LED_TOTAL; i++) {
    rgb_matrix_set_color(i, r, g, b);
  }
}

void set_matrix_color_at(uint8_t side, int x, int y, uint8_t r, uint8_t g,
                         uint8_t b) {
  int index;
  if (x < 0 || 4 < x || y < 0 || 4 < x) return;
  if (side == 0) {
    // right side(0-23)
    if (x == 0 && y == 4) return;
    index = y * 5 + x - (y == 4);
  } else {
    // left side (24-47)
    if (x == 4 && y == 4) return;
    index = 24 + y * 5 + (4 - x) - (y == 4);
  }
  rgb_matrix_set_color(index, r, g, b);
}

#include "logo.c"

void rgb_matrix_indicators_user(void) {
  uint32_t mode = rgblight_get_mode();
  // assign colors if the matrix is on and the current mode
  // is SOLID COLORS => No animations running
  if (mode == 1) {
    uint8_t layer = biton32(layer_state);
    if (layer == 0) {
      for (int y = 0; y < 5; y++) {
        for (int x = 0; x < 5; x++) {
          const uint8_t *c = logo_data.pixel_data + 3 * (y * 5 + x);
          set_matrix_color_at(0, x, y, c[0], c[1], c[2]);
          set_matrix_color_at(1, x, y, c[0], c[1], c[2]);
        }
      }
    } else {
      set_layer_color(layer);
    }
  }
}

uint32_t layer_state_set_user(uint32_t state) {
  uint8_t layer = biton32(state);

  ergodox_board_led_off();
  ergodox_right_led_1_off();
  ergodox_right_led_2_off();
  ergodox_right_led_3_off();
  switch (layer) {
    case 1:
      ergodox_right_led_1_on();
      break;
    case 2:
      ergodox_right_led_2_on();
      break;
    case 3:
      ergodox_right_led_3_on();
      break;
    case 4:
      ergodox_right_led_1_on();
      ergodox_right_led_2_on();
      break;
    case 5:
      ergodox_right_led_1_on();
      ergodox_right_led_3_on();
      break;
    case 6:
      ergodox_right_led_2_on();
      ergodox_right_led_3_on();
      break;
    case 7:
      ergodox_right_led_1_on();
      ergodox_right_led_2_on();
      ergodox_right_led_3_on();
      break;
    default:
      break;
  }
  return state;
};
