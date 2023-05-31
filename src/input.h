#pragma once

#include "platform.h"
#include "containers.h"

/*************************************************************************************************/

#define MAX_INPUT_DEVICES 16
#define MAX_KEYCODES 512

typedef flt_t(*input_get_float_value_t)(void* native_handle, u32_t id);
typedef i32_t(*input_get_int_value_t)(void* native_handle, u32_t id);

typedef struct input_device_t
{
	u32_t player;
	u32_t type;
	input_get_int_value_t get_int_value;
	input_get_float_value_t get_float_value;
	void* native_handle;
} input_device_t;

enum input_device_types_t
{
	INPUT_DEVICE_TYPE_KEYBOARD = 0,
	INPUT_DEVICE_TYPE_MOUSE = 1,
	INPUT_DEVICE_TYPE_KEYBOARD_MOUSE_COMBO = 2,
	INPUT_DEVICE_TYPE_GAMEPAD = 3,
	INPUT_DEVICE_TYPE_INVALID = U32_MAX,
};

enum input_codes_t
{
	/* gamepad int values */

	INPUT_GAMEPAD_START,
	INPUT_GAMEPAD_SELECT,
	INPUT_GAMEPAD_SHARE,
	INPUT_GAMEPAD_OPTIONS,

	INPUT_GAMEPAD_DPAD_UP,
	INPUT_GAMEPAD_DPAD_DOWN,
	INPUT_GAMEPAD_DPAD_LEFT,
	INPUT_GAMEPAD_DPAD_RIGHT,

	INPUT_GAMEPAD_FACE_UP,
	INPUT_GAMEPAD_FACE_DOWN,
	INPUT_GAMEPAD_FACE_LEFT,
	INPUT_GAMEPAD_FACE_RIGHT,

	INPUT_GAMEPAD_SHOULDER_LEFT,
	INPUT_GAMEPAD_SHOULDER_RIGHT,

	INPUT_GAMEPAD_JOYSTICK_LEFT,
	INPUT_GAMEPAD_JOYSTICK_RIGHT,

	/* gamepad float values */

	INPUT_GAMEPAD_TRIGGER_LEFT,
	INPUT_GAMEPAD_TRIGGER_RIGHT,

	INPUT_GAMEPAD_JOYSTICK_LEFT_X,
	INPUT_GAMEPAD_JOYSTICK_LEFT_Y,

	INPUT_GAMEPAD_JOYSTICK_RIGHT_X,
	INPUT_GAMEPAD_JOYSTICK_RIGHT_Y,

	/* keyboard int values */

	INPUT_KEY_A,
	INPUT_KEY_B,
	INPUT_KEY_C,
	INPUT_KEY_D,
	INPUT_KEY_E,
	INPUT_KEY_F,
	INPUT_KEY_G,
	INPUT_KEY_H,
	INPUT_KEY_I,
	INPUT_KEY_J,
	INPUT_KEY_K,
	INPUT_KEY_L,
	INPUT_KEY_M,
	INPUT_KEY_N,
	INPUT_KEY_O,
	INPUT_KEY_P,
	INPUT_KEY_Q,
	INPUT_KEY_R,
	INPUT_KEY_S,
	INPUT_KEY_T,
	INPUT_KEY_U,
	INPUT_KEY_V,
	INPUT_KEY_W,
	INPUT_KEY_X,
	INPUT_KEY_Y,
	INPUT_KEY_Z,

	INPUT_KEY_0,
	INPUT_KEY_1,
	INPUT_KEY_2,
	INPUT_KEY_3,
	INPUT_KEY_4,
	INPUT_KEY_5,
	INPUT_KEY_6,
	INPUT_KEY_7,
	INPUT_KEY_8,
	INPUT_KEY_9,

	INPUT_KEY_ADD,
	INPUT_KEY_SUBTRACT,
	INPUT_KEY_MULTIPLY,
	INPUT_KEY_DIVIDE,

	INPUT_KEY_ESC,
	INPUT_KEY_CAPS,
	INPUT_KEY_TAB,
	INPUT_KEY_SPACE,
	INPUT_KEY_LSHIFT,
	INPUT_KEY_RSHIFT,
	INPUT_KEY_LALT,
	INPUT_KEY_RALT,
	INPUT_KEY_LSTRG,
	INPUT_KEY_RSTRG,
	INPUT_KEY_ENTER,
	INPUT_KEY_BACKSPACE,

	INPUT_KEY_ARROW_UP,
	INPUT_KEY_ARROW_DOWN,
	INPUT_KEY_ARROW_LEFT,
	INPUT_KEY_ARROW_RIGHT,

	INPUT_KEY_NUM_0,
	INPUT_KEY_NUM_1,
	INPUT_KEY_NUM_2,
	INPUT_KEY_NUM_3,
	INPUT_KEY_NUM_4,
	INPUT_KEY_NUM_5,
	INPUT_KEY_NUM_6,
	INPUT_KEY_NUM_7,
	INPUT_KEY_NUM_8,
	INPUT_KEY_NUM_9,

	INPUT_KEY_F0,
	INPUT_KEY_F1,
	INPUT_KEY_F2,
	INPUT_KEY_F3,
	INPUT_KEY_F4,
	INPUT_KEY_F5,
	INPUT_KEY_F6,
	INPUT_KEY_F7,
	INPUT_KEY_F8,
	INPUT_KEY_F9,
	INPUT_KEY_F10,
	INPUT_KEY_F11,
	INPUT_KEY_F12,

	/* mouse int values */

	INPUT_MOUSE_LEFT,
	INPUT_MOUSE_RIGHT,
	INPUT_MOUSE_MIDDLE,

	/* mouse float values */

	INPUT_MOUSE_DELTA_X,
	INPUT_MOUSE_DELTA_Y,
	INPUT_MOUSE_POS_X,
	INPUT_MOUSE_POS_Y,
	INPUT_MOUSE_WHEEL,
};

extern input_device_t input_devices[MAX_INPUT_DEVICES + 1];

u8_t input_initialize();

u8_t input_update();

u32_t input_register_device(u32_t type, input_get_int_value_t get_int_value,
	input_get_float_value_t get_float_value, void_t* native_handle);

flt_t input_get_device_float_value(u32_t device, u32_t id);

i32_t input_get_device_int_value(u32_t device, u32_t id);

flt_t input_get_float_value(u32_t player, u32_t id);

i32_t input_get_int_value(u32_t player, u32_t id);