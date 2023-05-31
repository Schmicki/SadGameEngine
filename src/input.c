#include "input.h"
#include "engine.h"
#include "window.h"

#if defined(COMPILER_MSVC) /* MSVC */

#include <Xinput.h>

#endif /* MSVC */

/*************************************************************************************************/

#if defined(COMPILER_MSVC) /* MSVC */

typedef struct xinput_gamepad_t
{
	u32_t device;
	XINPUT_STATE state;
} xinput_gamepad_t;

xinput_gamepad_t xinput_devices[XUSER_MAX_COUNT];

i32_t xinput_get_int_value(xinput_gamepad_t* gamepad, u32_t id)
{
	u32_t buttons;

	buttons = (u32_t)gamepad->state.Gamepad.wButtons;

	switch (id)
	{
	case INPUT_GAMEPAD_START:
		return (buttons & XINPUT_GAMEPAD_START) != 0;
	case INPUT_GAMEPAD_SELECT:
		return (buttons & XINPUT_GAMEPAD_BACK) != 0;
	case INPUT_GAMEPAD_DPAD_UP:
		return (buttons & XINPUT_GAMEPAD_DPAD_UP) != 0;
	case INPUT_GAMEPAD_DPAD_DOWN:
		return (buttons & XINPUT_GAMEPAD_DPAD_DOWN) != 0;
	case INPUT_GAMEPAD_DPAD_LEFT:
		return (buttons & XINPUT_GAMEPAD_DPAD_LEFT) != 0;
	case INPUT_GAMEPAD_DPAD_RIGHT:
		return (buttons & XINPUT_GAMEPAD_DPAD_RIGHT) != 0;
	case INPUT_GAMEPAD_FACE_UP:
		return (buttons & XINPUT_GAMEPAD_Y) != 0;
	case INPUT_GAMEPAD_FACE_DOWN:
		return (buttons & XINPUT_GAMEPAD_A) != 0;
	case INPUT_GAMEPAD_FACE_LEFT:
		return (buttons & XINPUT_GAMEPAD_X) != 0;
	case INPUT_GAMEPAD_FACE_RIGHT:
		return (buttons & XINPUT_GAMEPAD_B) != 0;
	case INPUT_GAMEPAD_SHOULDER_RIGHT:
		return (buttons & XINPUT_GAMEPAD_RIGHT_SHOULDER) != 0;
	case INPUT_GAMEPAD_SHOULDER_LEFT:
		return (buttons & XINPUT_GAMEPAD_LEFT_SHOULDER) != 0;
	case INPUT_GAMEPAD_JOYSTICK_LEFT:
		return (buttons & XINPUT_GAMEPAD_LEFT_THUMB) != 0;
	case INPUT_GAMEPAD_JOYSTICK_RIGHT:
		return (buttons & XINPUT_GAMEPAD_RIGHT_THUMB) != 0;
	}

	return 0;
}

flt_t xinput_get_float_value(xinput_gamepad_t* gamepad, u32_t id)
{
	XINPUT_STATE state = gamepad->state;
	switch (id)
	{
	case INPUT_GAMEPAD_TRIGGER_LEFT:
		return (flt_t)state.Gamepad.bLeftTrigger / (flt_t)255;
	case INPUT_GAMEPAD_TRIGGER_RIGHT:
		return (flt_t)state.Gamepad.bRightTrigger / (flt_t)255;
	case INPUT_GAMEPAD_JOYSTICK_LEFT_X:
		return (flt_t)state.Gamepad.sThumbLX / (flt_t)I16_MAX;
	case INPUT_GAMEPAD_JOYSTICK_LEFT_Y:
		return (flt_t)state.Gamepad.sThumbLY / (flt_t)I16_MAX;
	case INPUT_GAMEPAD_JOYSTICK_RIGHT_X:
		return (flt_t)state.Gamepad.sThumbRX / (flt_t)I16_MAX;
	case INPUT_GAMEPAD_JOYSTICK_RIGHT_Y:
		return (flt_t)state.Gamepad.sThumbRY / (flt_t)I16_MAX;
	}

	return (flt_t)0;
}

void xinput_initialize()
{
	u32_t i;
	xinput_gamepad_t* gamepad;
	XINPUT_STATE state;

	for (i = 0; i < XUSER_MAX_COUNT; i++)
	{
		gamepad = xinput_devices + i;
		gamepad->device = -1;
		memset(&gamepad->state, 0, sizeof(XINPUT_STATE));

		if (XInputGetState(i, &gamepad->state) == ERROR_SUCCESS)
			gamepad->device = input_register_device(INPUT_DEVICE_TYPE_GAMEPAD,
				(input_get_int_value_t)&xinput_get_int_value,
				(input_get_float_value_t)&xinput_get_float_value, gamepad);
	}
}

void xinput_update()
{
	u32_t i;

	for (i = 0; i < XUSER_MAX_COUNT; i++)
	{
		XINPUT_STATE state;
		xinput_gamepad_t* gamepad;

		gamepad = xinput_devices + i;

		if (XInputGetState(i, &state) == ERROR_SUCCESS)
		{
			if (gamepad->device == -1)
				gamepad->device = input_register_device(INPUT_DEVICE_TYPE_GAMEPAD, (input_get_int_value_t)&xinput_get_int_value, (input_get_float_value_t)&xinput_get_float_value, gamepad);

			if (gamepad->device != -1)
			{
				/* send events */
			}

			gamepad->state = state;
		}
		else if (gamepad->device != -1)
		{
			/* unregister gamepad */
		}
	}
}

#endif /* MSVC */

/*************************************************************************************************/

input_device_t input_devices[MAX_INPUT_DEVICES + 1];
u32_t next_input_device_slot;

flt_t invalid_get_float_value(void_t* native_handle, u32_t id)
{
	return (flt_t)0;
}

i32_t invalid_get_int_value(void_t* native_handle, u32_t id)
{
	return 0;
}

u8_t input_initialize()
{
	u32_t i;
	input_device_t* device;

	next_input_device_slot = 0;

	for (i = 0; i <= MAX_INPUT_DEVICES; i++)
	{
		device = input_devices + i;
		device->player = MAX_PLAYERS;
		device->type = INPUT_DEVICE_TYPE_INVALID;
		device->native_handle = NULL;
		device->get_float_value = &invalid_get_float_value;
		device->get_int_value = &invalid_get_int_value;
	}

#if defined(OS_HAS_WINDOW) /* OS_HAS_WINDOW */

	window_input_initialize();

#endif /* OS_HAS_WINDOW */

#if defined(COMPILER_MSVC) /* MSVC */

	xinput_initialize();

#endif /* MSVC */

	return TRUE;
}

u8_t input_update()
{
#if defined(COMPILER_MSVC) /* MSVC */

	xinput_update();

#endif /* MSVC */

	return TRUE;
}

u32_t input_register_device(u32_t type, input_get_int_value_t get_int_value, input_get_float_value_t get_float_value, void_t* native_handle)
{
	u32_t i, id;
	input_device_t* device;

	if (type == INPUT_DEVICE_TYPE_INVALID)
		return U32_MAX;

	id = next_input_device_slot;

	if (id == U32_MAX)
		return U32_MAX;

	device = input_devices + id;
	device->type = type;
	device->get_int_value = get_int_value;
	device->get_float_value = get_float_value;
	device->native_handle = native_handle;

	next_input_device_slot = U32_MAX;

	for (i = 0; i < MAX_INPUT_DEVICES; i++)
	{
		device = input_devices + i;

		if (device->type == INPUT_DEVICE_TYPE_INVALID)
		{
			next_input_device_slot = i;
			break;
		}
	}

	return id;
}

flt_t input_get_device_float_value(u32_t device, u32_t id)
{
	input_device_t* _device;

	_device = input_devices + device;
	return _device->get_float_value(_device->native_handle, id);
}

i32_t input_get_device_int_value(u32_t device, u32_t id)
{
	input_device_t* _device;

	_device = input_devices + device;
	return _device->get_int_value(_device->native_handle, id);
}

flt_t input_get_float_value(u32_t player, u32_t id)
{
	input_device_t* device;

	device = input_devices + players[player].input_device;
	return device->get_float_value(device->native_handle, id);
}

i32_t input_get_int_value(u32_t player, u32_t id)
{
	input_device_t* device;

	device = input_devices + players[player].input_device;
	return device->get_int_value(device->native_handle, id);
}