 /*
  * UAE - The Un*x Amiga Emulator
  *
  * Support for platform-independent key-mapping
  *
  * Copyright 2004 Richard Drummond
  */

#include "sysconfig.h"
#include "sysdeps.h"

#include "options.h"
#include "inputdevice.h"
#include "keymap.h"

/*
 * Default mapping of UAE keycodes to UAE input events
 *
 * This list is ordered by UAEKEY_#? code. Input events correspond
 * to Amiga keycodes or UAE commands.
 */
static const int default_keymap[] = {
				INPUTEVENT_ZERO,
    /* UAEKEY_ESCAPE */ 	INPUTEVENT_KEY_ESC,

    /* UAEKEY_F1 */		INPUTEVENT_KEY_F1,
    /* UAEKEY_F2 */		INPUTEVENT_KEY_F2,
    /* UAEKEY_F3 */		INPUTEVENT_KEY_F3,
    /* UAEKEY_F4 */		INPUTEVENT_KEY_F4,
    /* UAEKEY_F5 */		INPUTEVENT_KEY_F5,
    /* UAEKEY_F6 */		INPUTEVENT_KEY_F6,
    /* UAEKEY_F7 */		INPUTEVENT_KEY_F7,
    /* UAEKEY_F8 */		INPUTEVENT_KEY_F8,
    /* UAEKEY_F9 */		INPUTEVENT_KEY_F9,
    /* UAEKEY_F10 */		INPUTEVENT_KEY_F10,
    /* UAEKEY_F11 */		INPUTEVENT_ZERO,
    /* UAEKEY_F12 */		INPUTEVENT_ZERO,

    /* UAEKEY_PRINTSCR */	INPUTEVENT_SPC_SCREENSHOT,
    /* UAEKEY_SCROLL_LOCK */	INPUTEVENT_SPC_INHIBITSCREEN,
    /* UAEKEY_PAUSE */		INPUTEVENT_SPC_PAUSE,

    /* UAEKEY_1 */		INPUTEVENT_KEY_1,
    /* UAEKEY_2 */		INPUTEVENT_KEY_2,
    /* UAEKEY_3 */		INPUTEVENT_KEY_3,
    /* UAEKEY_4 */		INPUTEVENT_KEY_4,
    /* UAEKEY_5 */		INPUTEVENT_KEY_5,
    /* UAEKEY_6 */		INPUTEVENT_KEY_6,
    /* UAEKEY_7 */		INPUTEVENT_KEY_7,
    /* UAEKEY_8 */		INPUTEVENT_KEY_8,
    /* UAEKEY_9 */		INPUTEVENT_KEY_9,
    /* UAEKEY_0	*/		INPUTEVENT_KEY_0,

    /* UAEKEY_MINUS */		INPUTEVENT_KEY_SUB,
    /* UAEKEY_EQUALS */		INPUTEVENT_KEY_EQUALS,

    /* UAEKEY_BACKSPACE */	INPUTEVENT_KEY_BACKSPACE,
    /* UAEKEY_ENTER */		INPUTEVENT_KEY_RETURN,
    /* UAEKEY_SPACE */		INPUTEVENT_KEY_SPACE,

    /* UAEKEY_TAB */		INPUTEVENT_KEY_TAB,

    /* UAEKEY_A */		INPUTEVENT_KEY_A,
    /* UAEKEY_B */		INPUTEVENT_KEY_B,
    /* UAEKEY_C */		INPUTEVENT_KEY_C,
    /* UAEKEY_D */		INPUTEVENT_KEY_D,
    /* UAEKEY_E */		INPUTEVENT_KEY_E,
    /* UAEKEY_F */		INPUTEVENT_KEY_F,
    /* UAEKEY_G */		INPUTEVENT_KEY_G,
    /* UAEKEY_H */		INPUTEVENT_KEY_H,
    /* UAEKEY_I */		INPUTEVENT_KEY_I,
    /* UAEKEY_J */		INPUTEVENT_KEY_J,
    /* UAEKEY_K */		INPUTEVENT_KEY_K,
    /* UAEKEY_L */		INPUTEVENT_KEY_L,
    /* UAEKEY_M */		INPUTEVENT_KEY_M,
    /* UAEKEY_N */		INPUTEVENT_KEY_N,
    /* UAEKEY_O */		INPUTEVENT_KEY_O,
    /* UAEKEY_P */		INPUTEVENT_KEY_P,
    /* UAEKEY_Q */		INPUTEVENT_KEY_Q,
    /* UAEKEY_R */		INPUTEVENT_KEY_R,
    /* UAEKEY_S */		INPUTEVENT_KEY_S,
    /* UAEKEY_T */		INPUTEVENT_KEY_T,
    /* UAEKEY_U */		INPUTEVENT_KEY_U,
    /* UAEKEY_V */		INPUTEVENT_KEY_V,
    /* UAEKEY_W */		INPUTEVENT_KEY_W,
    /* UAEKEY_X */		INPUTEVENT_KEY_X,
    /* UAEKEY_Y */		INPUTEVENT_KEY_Y,
    /* UAEKEY_Z */		INPUTEVENT_KEY_Z,

    /* UAEKEY_LEFTBRACKET */	INPUTEVENT_KEY_LEFTBRACKET,
    /* UAEKEY_RIGHTBRACKET */	INPUTEVENT_KEY_RIGHTBRACKET,
    /* UAEKEY_SEMICOLON */	INPUTEVENT_KEY_SEMICOLON,
    /* UAEKEY_SINGLEQUOTE */	INPUTEVENT_KEY_SINGLEQUOTE,
    /* UAEKEY_GRAVE */		INPUTEVENT_KEY_BACKQUOTE,
    /* UAEKEY_BACKSLASH */	INPUTEVENT_KEY_BACKSLASH,
    /* UAEKEY_COMMA */		INPUTEVENT_KEY_COMMA,
    /* UAEKEY_PERIOD */		INPUTEVENT_KEY_PERIOD,
    /* UAEKEY_SLASH */		INPUTEVENT_KEY_DIV,
    /* UAEKEY_LTGT */		INPUTEVENT_KEY_30,

    /* UAEKEY_NUMLOCK */	INPUTEVENT_ZERO,
    /* UAEKEY_NUMPAD_1 */	INPUTEVENT_KEY_NP_1,
    /* UAEKEY_NUMPAD_2 */	INPUTEVENT_KEY_NP_2,
    /* UAEKEY_NUMPAD_3 */	INPUTEVENT_KEY_NP_3,
    /* UAEKEY_NUMPAD_4 */	INPUTEVENT_KEY_NP_4,
    /* UAEKEY_NUMPAD_5 */	INPUTEVENT_KEY_NP_5,
    /* UAEKEY_NUMPAD_6 */	INPUTEVENT_KEY_NP_6,
    /* UAEKEY_NUMPAD_7 */	INPUTEVENT_KEY_NP_7,
    /* UAEKEY_NUMPAD_8 */	INPUTEVENT_KEY_NP_8,
    /* UAEKEY_NUMPAD_9 */	INPUTEVENT_KEY_NP_9,
    /* UAEKEY_NUMPAD_0 */	INPUTEVENT_KEY_NP_0,
    /* UAEKEY_NUMPAD_PERIOD */	INPUTEVENT_KEY_NP_PERIOD,
    /* UAEKEY_NUMPAD_PLUS */	INPUTEVENT_KEY_NP_ADD,
    /* UAEKEY_NUMPAD_MINUS */	INPUTEVENT_KEY_NP_SUB,
    /* UAEKEY_NUMPAD_MULTIPLY */INPUTEVENT_KEY_NP_MUL,
    /* UAEKEY_NUMPAD_DIVIDE */	INPUTEVENT_KEY_NP_DIV,
    /* UAEKEY_NUMPAD_ENTER */	INPUTEVENT_KEY_ENTER,
    /* UAEKEY_NUMPAD_EQUALS */  INPUTEVENT_ZERO,
    /* UAEKEY_NUMPAD_LPAREN */  INPUTEVENT_KEY_NP_LPAREN,
    /* UAEKEY_NUMPAD_RPAREN */  INPUTEVENT_KEY_NP_RPAREN,

    /* UAEKEY_INSERT */		INPUTEVENT_KEY_HELP,
    /* UAEKEY_DELETE */		INPUTEVENT_KEY_DEL,
    /* UAEKEY_HOME */		INPUTEVENT_ZERO,
    /* UAEKEY_END */		INPUTEVENT_ZERO,
    /* UAEKEY_PAGEUP */ 	INPUTEVENT_KEY_AMIGA_RIGHT,
    /* UAEKEY_PAGEDOWN */	INPUTEVENT_KEY_AMIGA_LEFT,

    /* UAEKEY_CURSOR_UP */	INPUTEVENT_KEY_CURSOR_UP,
    /* UAEKEY_CURSOR_DOWN */	INPUTEVENT_KEY_CURSOR_DOWN,
    /* UAEKEY_CURSOR_LEFT */	INPUTEVENT_KEY_CURSOR_LEFT,
    /* UAEKEY_CURSOR_RIGHT */	INPUTEVENT_KEY_CURSOR_RIGHT,

    /* UAEKEY_LEFT_CTRL */	INPUTEVENT_KEY_CTRL,
    /* UAEKEY_LEFT_SHIFT */	INPUTEVENT_KEY_SHIFT_LEFT,
    /* UAEKEY_LEFT_ALT */	INPUTEVENT_KEY_ALT_LEFT,
    /* UAEKEY_LEFT_SUPER */	INPUTEVENT_KEY_AMIGA_LEFT,
    /* UAEKEY_RIGHT_SUPER */	INPUTEVENT_KEY_AMIGA_RIGHT,
    /* UAEKEY_RIGHT_ALT */	INPUTEVENT_KEY_ALT_RIGHT,
    /* UAEKEY_MENU */		INPUTEVENT_KEY_AMIGA_RIGHT,
    /* UAEKEY_RIGHT_SHIFT */	INPUTEVENT_KEY_SHIFT_RIGHT,
    /* UAEKEY_RIGHT_CTRL */	INPUTEVENT_KEY_CTRL_RIGHT,
    /* UAEKEY_CAPSLOCK */	INPUTEVENT_KEY_CAPS_LOCK,

    /* UAEKEY_HELP */		INPUTEVENT_KEY_HELP,

    /* UAEKEY_POWER */		INPUTEVENT_ZERO,
    /* UAEKEY_SLEEP */		INPUTEVENT_ZERO,
    /* UAEKEY_WAKE */		INPUTEVENT_ZERO
};


/*
 * Build a default key translation table using the
 * specified host keymap.
 */
struct uae_input_device_kbr_default *uaekey_make_default_kbr (const struct uaekey_hostmap *hostkeys)
{
    int i;
    int count;
    struct uae_input_device_kbr_default *trans;

    for (i = 0; i < 256 && hostkeys[i].hostkey != -1; i++);

    if (i == 256)
	abort ();

    count = i;

    trans = (struct uae_input_device_kbr_default*)
	    malloc (sizeof (struct uae_input_device_kbr_default) * (count + 1));

    if (trans) {
	for (i = 0; i < count; i++) {
	    trans[i].scancode = hostkeys[i].hostkey;
	    trans[i].event    = default_keymap[hostkeys[i].uaekey];
	}
	trans[i].scancode = -1;
    }

    return trans;
};
