/* Copyright 2015-2017 Jack Humbert
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

#include "preonic.h"
#include "action_layer.h"

#define _BL 0
#define _FL 1
#define _ML 2
enum satan_keycodes
{
  FAKE = SAFE_RANGE,
  DYNAMIC_MACRO_RANGE,
};
#include "dynamic_macro.h"

#define _4SPACE M(0)
#define LOCK M(1)
// Fillers to make layering more clear
#define _______ KC_TRNS
#define DANCE_LAYERS 0
#define NKTG MAGIC_TOGGLE_NKRO
#define NKON MAGIC_HOST_NKRO
#define NKOFF MAGIC_UNHOST_NKRO

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * ,-----------------------------------------------------------------------------------.
 * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Del  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Esc  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  "   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Brite| Ctrl | Alt  | GUI  |Lower |    Space    |Raise | Left | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 */
[_BL] = {
  {KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC},
  {KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_DEL },
{LT(_FL,KC_F2),KC_A, KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_ENT},
  {KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT },
  {KC_LCTL,KC_LGUI ,KC_LALT,KC_LBRC,KC_RBRC,KC_SPC,TD(DANCE_LAYERS),KC_MINS,KC_EQL,KC_QUOT,KC_BSLS,KC_ESC }
},

[_FL] = {
  {KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,     KC_F8,   KC_F9,   KC_F10, KC_F11},
  {_4SPACE, _______, KC_UP, _______, _______, _______,   _______,  _______,   KC_PSCR, KC_SLCK, KC_PAUS, KC_F12},
  {_______, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______, _______, _______, KC_INS, KC_HOME, KC_PGUP, _______},
  {_______, _______, _______, _______, _______, _______, NKTG,   _______,  KC_HOME,  KC_END, KC_PGDN, _______},
  {_______, _______, _______, _______, _______, _______, _______, _______,  _______, _______, _______, _______}
},


[_ML] = {
  {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______},
  {_______, KC_BTN1, KC_MS_U, KC_BTN2, _______, _______, _______, KC_BTN1, KC_WH_U, KC_BTN2, _______, _______},
  {_______, KC_MS_L, KC_MS_D, KC_MS_R, _______, _______, _______, KC_WH_L, KC_WH_D, KC_WH_R, _______, _______},
  {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______},
  {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______}
}

};
bool fn_held;
void dance_layers(qk_tap_dance_state_t *state, void *user_data)
{

  if (state->pressed)
  {
    layer_on(_FL);
    fn_held = true;
  }
  switch (state->count)
  {
  case 1: //off all layers, just base on
    if (!state->pressed)
    {
      layer_off(_ML);
      layer_off(_FL);
      fn_held = false;
    }
    break;
  case 2: //function layer on
    layer_on(_FL);
    layer_off(_ML);
    break;
  case 3: //mouse layeron
    layer_on(_ML);
    layer_off(_FL);
    break;
  }
}
void dance_layers_finish(qk_tap_dance_state_t *state, void *user_data)
{
  if (fn_held)
  {
    layer_off(_FL);
    fn_held = false;
  }
}
qk_tap_dance_action_t tap_dance_actions[] = {
        [DANCE_LAYERS] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_layers, dance_layers_finish)};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt) // this is the function signature -- just copy/paste it into your keymap file as it is.
{
  switch (id)
  {
  case 0: // this would trigger when you hit a key mapped as M(0)z
    if (record->event.pressed)
    {
      return MACRO(I(4), T(SPACE), T(SPACE), T(SPACE), T(SPACE), END); // this sends the string '    ' when the macro executes
    }
    break;
  case 1: // send win + l to lock
    if (record->event.pressed)
    {
      return MACRO(I(5), D(LGUI), D(L), U(L), U(LGUI), END);
    }
    break;
  }
  return MACRO_NONE;
};

bool process_record_user(uint16_t keycode, keyrecord_t *record)
{
  if (!process_record_dynamic_macro(keycode, record))
  {
    return false;
  }
  return true;
}
