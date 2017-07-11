#include "satan.h"

// Used for SHIFT_ESC
#define MODS_CTRL_MASK  (MOD_BIT(KC_LSHIFT)|MOD_BIT(KC_RSHIFT))

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _BL 0
#define _FL 1
#define _4SPACE M(0)
#define LOCK M(1)
// Fillers to make layering more clear
#define _______ KC_TRNS

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /* Keymap _BL: (Base Layer) Default Layer
   * ,-----------------------------------------------------------.
   * |Esc~| 1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =| \ | ~ |
   * |-----------------------------------------------------------|
   * |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|bksp |
   * |-----------------------------------------------------------|
   * |CAPS   |  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '|Return |
   * |-----------------------------------------------------------|
   * |Shift   |  Z|  X|  C|  V|  B|  N|  M|  ,|  .|  /|Shift| fn |
   * |-----------------------------------------------------------|
   * |Ctrl|Gui |Alt |      Space            |Alt |Gui |FN  |Ctrl |
   * `-----------------------------------------------------------'
   */
[_BL] = KEYMAP_HHKB(
  KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,   KC_MINS, KC_EQL,  KC_BSPC, KC_ESC, \
  KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC,      KC_BSLS, \
  LT(_FL,KC_F2), KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,           KC_ENT,  \
  KC_LSFT,          KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,         KC_RSFT, KC_DEL, \
  KC_LCTL,  KC_LGUI,  KC_LALT,          KC_SPC,                                               KC_RALT,   MO(_FL),   KC_RGUI,   KC_RCTL),

  /* Keymap _FL: Function Layer
   * ,-----------------------------------------------------------.
   * |~ `| F1|F2 |F3 |F4 |F5 |F6 |F7 |F8 |F9 |F10|F11|F12|Del|Esc|
   * |-----------------------------------------------------------|
   * |4*Spc|   |Up |   |   |   |   |   |Up |Ins|Psc|Slk|Pus|     |
   * |-----------------------------------------------------------|
   * |      |Lft|Dn |Rit|   |   |   |Lft|Dn |Rit|   |PUp|        |
   * |-----------------------------------------------------------|
   * |        |   |   |   |   |   |   |   |Hm |End|Pdn|      |   |
   * |-----------------------------------------------------------|
   * |    |    |    |                        |    |    |    |    |
   * `-----------------------------------------------------------'
   */
[_FL] = KEYMAP_HHKB(
   KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL, KC_GRV, \
  _4SPACE,   _______, KC_UP, _______, _______, _______, _______, _______, KC_UP,   KC_INS, KC_PSCR, KC_SLCK, KC_PAUS,          _______, \
  _______,     KC_LEFT, KC_DOWN, KC_RGHT, _______, _______, _______, KC_LEFT, KC_DOWN, KC_RGHT, _______, KC_PGUP,              _______, \
  _______,        _______, _______, _______, _______, _______, _______,  _______, KC_HOME, KC_END, KC_PGDN,           _______, _______, \
  _______,   _______,   _______,                   _______,                                     _______,   _______,  _______,  _______)
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

/*
enum function_id {
    SHIFT_ESC,
};

const uint16_t PROGMEM fn_actions[] = {
  [0]  = ACTION_FUNCTION(SHIFT_ESC),
};

void action_function(keyrecord_t *record, uint8_t id, uint8_t opt) {
  static uint8_t shift_esc_shift_mask;
  switch (id) {
    case SHIFT_ESC:
      shift_esc_shift_mask = get_mods()&MODS_CTRL_MASK;
      if (record->event.pressed) {
        if (shift_esc_shift_mask) {
          add_key(KC_GRV);
          send_keyboard_report();
        } else {
          add_key(KC_ESC);
          send_keyboard_report();
        }
      } else {
        if (shift_esc_shift_mask) {
          del_key(KC_GRV);
          send_keyboard_report();
        } else {
          del_key(KC_ESC);
          send_keyboard_report();
        }
      }
      break;
  }
}*/
