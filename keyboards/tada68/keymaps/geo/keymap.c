#include "tada68.h"

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _BL 0
#define _FL 1

#define _______ KC_TRNS
#define _4SPACE M(0)
#define LOCK M(1)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /* Keymap _BL: (Base Layer) Default Layer
   * ,----------------------------------------------------------------.
   * |~ ` | 1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|Backsp |Esc |
   * |----------------------------------------------------------------|
   * |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|  \  |Del |
   * |----------------------------------------------------------------|
   * |FN/F2  |  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '|Enter  |PgUp|
   * |----------------------------------------------------------------|
   * |Shift   |  Z|  X|  C|  V|  B|  N|  M|  ,|  .|  /|Shift | Up|PgDn|
   * |----------------------------------------------------------------|
   * |Ctrl|Win |Alt |        Space          |Alt| FN|Ctrl|Lef|Dow|Rig |
   * `----------------------------------------------------------------'
   */
[_BL] = KEYMAP_ANSI(
  KC_GRV,    KC_1,   KC_2,   KC_3,   KC_4,   KC_5,   KC_6,   KC_7,   KC_8,   KC_9,   KC_0, KC_MINS, KC_EQL, KC_BSPC, KC_ESC, \
  KC_TAB,  KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,   KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,   KC_LBRC, KC_RBRC,KC_BSLS, KC_DEL, \
  LT(_FL,KC_F2), KC_A,   KC_S,   KC_D,   KC_F,   KC_G,   KC_H,   KC_J,   KC_K,   KC_L,   KC_SCLN,KC_QUOT, KC_ENT,   KC_PGUP, \
  KC_LSFT,         KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   KC_N,   KC_M,   KC_COMM,KC_DOT, KC_SLSH,   KC_RSFT,KC_UP,KC_PGDN, \
  KC_LCTL, KC_LGUI,KC_LALT,                KC_SPC,                       KC_RALT,MO(_FL),KC_RCTRL, KC_LEFT,KC_DOWN,KC_RGHT),

  /* Keymap _FL: Function Layer
   * ,----------------------------------------------------------------.
   * |~ `| F1|F2 |F3 |F4 |F5 |F6 |F7 |F8 |F9 |F10|F11|F12|Del    |Pwr |
   * |----------------------------------------------------------------|
   * |4*Spc|   |Up |   |   |   |   |   |   |   |   |   |   |     |Ins |
   * |----------------------------------------------------------------|
   * |      |<- |Dn | ->|   |   |   |   |   |Lck|   |   |        |Hme |
   * |----------------------------------------------------------------|
   * |        |   |   |Bl-|BL |BL+|   |   |VU-|VU+|MUT|      |   |End |
   * |----------------------------------------------------------------|
   * |    |    |    |                       |   |   |    |Hme|   |End |
   * `----------------------------------------------------------------'
   */
[_FL] = KEYMAP_ANSI(
  KC_ESC, KC_F1 ,KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_DEL,          KC_GRV, \
  _4SPACE,_______,KC_UP, _______,_______,_______,_______,_______,KC_UP,KC_INS,KC_PSCR, KC_SLCK,KC_PAUS, _______,KC_INS, \
  _______,KC_LEFT,KC_DOWN,KC_RIGHT,_______,_______,_______,KC_LEFT,KC_DOWN,KC_RIGHT,_______,KC_PGUP, _______,      _______, \
  _______,_______,_______,BL_DEC, BL_TOGG,BL_INC, _______,_______,KC_HOME,KC_END,KC_PGDN,_______,_______,         _______, \
  _______,_______,_______,                     _______,                   _______,_______,_______,_______,_______,_______),
};


const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt) // this is the function signature -- just copy/paste it into your keymap file as it is.
{
  switch(id) {
    case 0: // this would trigger when you hit a key mapped as M(0)
      if (record->event.pressed) {
        return MACRO( I(4), T(SPACE), T(SPACE), T(SPACE), T(SPACE), END); // this sends the string '    ' when the macro executes
      }
      break;
    case 1: // send win + l to lock
      if (record->event.pressed){
        return MACRO(I(5), D(LGUI), D(L), U(L), U(LGUI), END);
      }
      break;
    }
    return MACRO_NONE;
};