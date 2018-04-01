#include "dz60.h"

#define MODS_CTRL_MASK  (MOD_BIT(KC_LSHIFT)|MOD_BIT(KC_RSHIFT))

#define ____ KC_TRNS
#define xxxx KC_NO

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    /* ,-----------------------------------------------------------.
     * |Esc|  1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|  `|DEL|
     * |-----------------------------------------------------------|
     * |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|   \ |
     * |-----------------------------------------------------------|
     * |Contro|  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '| Enter  |
     * |-----------------------------------------------------------|
     * |LShift  |  Z|  X|  C|  V|  B|  N|  M|  ,|  .|  /|RShift|Fn1|
     * |-----------------------------------------------------------'
     * |FN  |Gui |Alt  |BackSP |FN |Space      |Alt |Gui |FN  |CTRL|
     * `-----------------------------------------------------------'
     */

    KEYMAP(
           F(0),    KC_1,    KC_2,    KC_3,    KC_4,   KC_5,   KC_6,    KC_7,  KC_8,  KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_GRV,  KC_DEL,
           KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,   KC_T,   KC_Y,    KC_U,  KC_I,  KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,
           KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,   KC_G,   KC_H,    KC_J,  KC_K,  KC_L,    KC_SCLN, KC_QUOT, KC_ENT,
           KC_LSFT, xxxx,    KC_Z,    KC_X,    KC_C,   KC_V,   KC_B,    KC_N,  KC_M,  KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, xxxx,
           KC_LCTL, KC_LGUI, KC_LALT, KC_BSPC, KC_SPC, KC_SPC, KC_RALT, MO(2), KC_NO, MO(1),   KC_RCTL),

    /* ,-----------------------------------------------------------.
     * |  `| F1| F2| F3| F4| F5| F6| F7| F8| F9|F10|F11|F12|Ins|Bsp|
     * |-----------------------------------------------------------|
     * |     |TOG|MOD|HUI|HUD|SAI|SAD|VAI|VAD|   |  | Up|   | RST  |
     * |-----------------------------------------------------------|
     * |      |   |   |   |   |   |   |   |Hom|PgU|Lft|Rgt|        |
     * |-----------------------------------------------------------|
     * |        |   |   |   |DEC|TOG|INC|STP|End|PgD|Dwn|      |   |
     * |-----------------------------------------------------------'
     * |    |    |     |       |   |           |    |    |    |    |
     * `-----------------------------------------------------------'
     */

    KEYMAP(
           KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12, KC_INS, KC_BSPC,
           ____,    RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, RGB_VAI, RGB_VAD, ____,    ____,    KC_UP,   ____,   RESET,
           ____,    ____,    ____,    ____,    ____,    ____,    ____,    ____,    KC_HOME, KC_PGUP, KC_LEFT, KC_RGHT, ____,
           ____,    ____,    ____,    ____,    BL_DEC,  BL_TOGG, BL_INC,  BL_STEP, ____,    KC_END,  KC_PGDN, KC_DOWN, ____,   xxxx,
           ____,    ____,    ____,    ____,    ____,    ____,    ____,    ____,    ____,    ____,    ____),

    /* ,-----------------------------------------------------------.
     * |   |M01|M02|M03|M04|M05|M06|M07|M08|M09|M10|M11|M12|   |   |
     * |-----------------------------------------------------------|
     * |     |   |   |   |   |   |   |   |   |   |  |   |   |      |
     * |-----------------------------------------------------------|
     * |      |   |   |   |   |   |   |   |   |   |   |   |        |
     * |-----------------------------------------------------------|
     * |        |   |   |   |   |   |   |   |   |   |   |      |   |
     * |-----------------------------------------------------------'
     * |    |    |     |       |   |           |    |    |    |    |
     * `-----------------------------------------------------------'
     */

    KEYMAP(
           ____, M(1), M(2), M(3), M(4), M(5), M(6), M(7), M(8), M(9), M(10), M(11), M(12), ____, ____,
           ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____,  ____,  ____,  ____,
           ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____,  ____,  ____,
           ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____,  ____,  ____,  xxxx,
           ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____),
};

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
}
