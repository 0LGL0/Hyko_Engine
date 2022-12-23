#pragma once
#include <stdint.h>

namespace Hyko {
	using keyCode = uint16_t;

	namespace Key {
		enum : keyCode {
			HK_KEYBORD_SPACE		   = 32,	/* SPACE */
			HK_KEYBORD_APOSTROPHE      = 39,	/* ` */
			HK_KEYBORD_COMMA		   = 44,	/* , */
			HK_KEYBORD_MINUS		   = 45,	/* - */
			HK_KEYBORD_PERIOD		   = 46,	/* . */
			HK_KEYBORD_SLASH		   = 47,	/* / */
			HK_KEYBORD_0			   = 48,	/* 0 */
			HK_KEYBORD_1			   = 49,	/* 1 */
			HK_KEYBORD_2			   = 50,	/* 2 */
			HK_KEYBORD_3			   = 51,	/* 3 */
			HK_KEYBORD_4			   = 52,	/* 4 */
			HK_KEYBORD_5			   = 53,	/* 5 */
			HK_KEYBORD_6			   = 54,	/* 6 */
			HK_KEYBORD_7			   = 55,	/* 7 */
			HK_KEYBORD_8			   = 56,	/* 8 */
			HK_KEYBORD_9			   = 57,	/* 9 */
			HK_KEYBORD_SEMICOLON	   = 59,	/* ; */
			HK_KEYBORD_EQUAL		   = 61,	/* = */
			HK_KEYBORD_A			   = 65,	/* A */
			HK_KEYBORD_B			   = 66,	/* B */
			HK_KEYBORD_C			   = 67,	/* C */
			HK_KEYBORD_D			   = 68,	/* D */
			HK_KEYBORD_E			   = 69,	/* E */
			HK_KEYBORD_F			   = 70,	/* F */
			HK_KEYBORD_G			   = 71,	/* G */
			HK_KEYBORD_H			   = 72,	/* H */
			HK_KEYBORD_I			   = 73,	/* I */
			HK_KEYBORD_J			   = 74,	/* J */
			HK_KEYBORD_K			   = 75,	/* K */
			HK_KEYBORD_L			   = 76,	/* L */
			HK_KEYBORD_M			   = 77,	/* M */
			HK_KEYBORD_N			   = 78,	/* N */
			HK_KEYBORD_O			   = 79,	/* O */
			HK_KEYBORD_P			   = 80,	/* P */
			HK_KEYBORD_Q			   = 81,	/* Q */
			HK_KEYBORD_R			   = 82,	/* R */
			HK_KEYBORD_S			   = 83,	/* S */
			HK_KEYBORD_T			   = 84,	/* T */
			HK_KEYBORD_U			   = 85,	/* U */
			HK_KEYBORD_V			   = 86,	/* V */
			HK_KEYBORD_W			   = 87,	/* W */
			HK_KEYBORD_X			   = 88,	/* X */
			HK_KEYBORD_Y			   = 89,	/* Y */
			HK_KEYBORD_Z			   = 90,	/* Z */
			HK_KEYBORD_LEFT_BRACKET    = 91,	/* [ */
			HK_KEYBORD_BACKSLASH	   = 92,	/* \*/
			HK_KEYBORD_RIGHT_BRACKET   = 93,	/* ] */
			HK_KEYBORD_GRAVE_ACCENT    = 96,	/* ' */
			HK_KEYBORD_WORLD_1		   = 161,   /* non-US #1 */
			HK_KEYBORD_WORLD_2		   = 162,   /* non-US #2 */
			HK_KEYBORD_ESCAPE		   = 256,	/* ESCAPE */
			HK_KEYBORD_ENTER		   = 257,	/* ENTER */
			HK_KEYBORD_TAB			   = 258,	/* TAB */
			HK_KEYBORD_BACKSPACE	   = 259,	/* BACKSPACE */
			HK_KEYBORD_INSERT		   = 260,	/* INSERT */
			HK_KEYBORD_DELETE		   = 261,	/* DELETE */
			HK_KEYBORD_RIGHT		   = 262,	/* RIGHT ARROW */
			HK_KEYBORD_LEFT			   = 263,	/* LEFT ARROW */
			HK_KEYBORD_DOWN			   = 264,	/* DOWN ARROW */
			HK_KEYBORD_UP			   = 265,	/* UP ARROW */
			HK_KEYBORD_PAGE_UP		   = 266,	/* PAGE_UP */
			HK_KEYBORD_PAGE_DOWN	   = 267,	/* PAGE_DOWN */
			HK_KEYBORD_HOME			   = 268,	/* HOME */
			HK_KEYBORD_END			   = 269,	/* END */
			HK_KEYBORD_CAPS_LOCK	   = 280,	/* CAPS_LOCK */
			HK_KEYBORD_SCROLL_LOCK     = 281,	/* SCROLL_LOCK */
			HK_KEYBORD_NUM_LOCK        = 282,	/* NUM_LOCK */
			HK_KEYBORD_PRINT_SCREEN    = 283,	/* PRINT_SCREEN */
			HK_KEYBORD_PAUSE		   = 284,	/* PAUSE */
			HK_KEYBORD_F1			   = 290,	/* F1 */
			HK_KEYBORD_F2			   = 291,	/* F2 */
			HK_KEYBORD_F3			   = 292,	/* F3 */
			HK_KEYBORD_F4			   = 293,	/* F4 */
			HK_KEYBORD_F5			   = 294,	/* F5 */
			HK_KEYBORD_F6			   = 295,	/* F6 */
			HK_KEYBORD_F7			   = 296,	/* F7 */
			HK_KEYBORD_F8			   = 297,	/* F8 */
			HK_KEYBORD_F9			   = 298,	/* F9 */
			HK_KEYBORD_F10			   = 299,	/* F10 */
			HK_KEYBORD_F11			   = 300,	/* F11 */
			HK_KEYBORD_F12			   = 301,	/* F12 */
			HK_KEYBORD_F13			   = 302,	/* F13 */
			HK_KEYBORD_F14			   = 303,	/* F14 */
			HK_KEYBORD_F15			   = 304,	/* F15 */
			HK_KEYBORD_F16			   = 305,	/* F16 */
			HK_KEYBORD_F17			   = 306,	/* F17 */
			HK_KEYBORD_F18			   = 307,	/* F18 */
			HK_KEYBORD_F19			   = 308,	/* F19 */
			HK_KEYBORD_F20			   = 309,	/* F20 */
			HK_KEYBORD_F21			   = 310,	/* F21 */
			HK_KEYBORD_F22			   = 311,	/* F22 */
			HK_KEYBORD_F23			   = 312,	/* F23 */
			HK_KEYBORD_F24			   = 313,	/* F24 */
			HK_KEYBORD_F25			   = 314,	/* F25 */
			HK_KEYBORD_KEYPAD_0		   = 320,	/* KEYPAD 0 */
			HK_KEYBORD_KEYPAD_1		   = 321,	/* KEYPAD 1 */
			HK_KEYBORD_KEYPAD_2		   = 322,	/* KEYPAD 2 */
			HK_KEYBORD_KEYPAD_3		   = 323,	/* KEYPAD 3 */
			HK_KEYBORD_KEYPAD_4		   = 324,	/* KEYPAD 4 */
			HK_KEYBORD_KEYPAD_5		   = 325,	/* KEYPAD 5 */
			HK_KEYBORD_KEYPAD_6		   = 326,	/* KEYPAD 6 */
			HK_KEYBORD_KEYPAD_7		   = 327,	/* KEYPAD 7 */
			HK_KEYBORD_KEYPAD_8		   = 328,	/* KEYPAD 8 */
			HK_KEYBORD_KEYPAD_9		   = 329,	/* KEYPAD 9 */
			HK_KEYBORD_KEYPAD_DECIMAL  = 330,	/* DECIMAL */
			HK_KEYBORD_KEYPAD_DIVIDE   = 331,	/* DIVIDE */
			HK_KEYBORD_KEYPAD_MULTIPLY = 332,	/* MULTIPLY */
			HK_KEYBORD_KEYPAD_SUBTRACT = 333,	/* SUBTRACT */
			HK_KEYBORD_KEYPAD_ADD	   = 334,	/* ADD */
			HK_KEYBORD_KEYPAD_ENTER    = 335,	/* ENTER */
			HK_KEYBORD_KEYPAD_EQUAL    = 336,	/* EQUAL */
			HK_KEYBORD_LEFT_SHIFT      = 340,	/* L_SHIFT */
			HK_KEYBORD_LEFT_CONTROL    = 341,	/* L_CONTROL */
			HK_KEYBORD_LEFT_ALT		   = 342,	/* L_ALT */
			HK_KEYBORD_LEFT_SUPER	   = 343,	/* L_SUPER */
			HK_KEYBORD_RIGHT_SHIFT	   = 344,	/* R_SHIFT */
			HK_KEYBORD_RIGHT_CONTROL   = 345,	/* R_CONTROL */
			HK_KEYBORD_RIGHT_ALT       = 346,	/* R_ALT */
			HK_KEYBORD_RIGHT_SUPER	   = 347,	/* R_SUPER */
			HK_KEYBORD_MENU			   = 348,	/* MENU */
			HK_KEYBORD_LAST			   = 315,	/* LAST */
		};
	}
}