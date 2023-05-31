#include "window.h"
#include "containers.h"
#include "input.h"

#if defined(COMPILER_MSVC) /* MSVC */

//#define WIN32_LEAN_AND_MEAN 1

#include <Windows.h>

#endif /* MSVC */

/*************************************************************************************************/

typedef struct keyboard_t
{
	/* bitmap of 256 bits */
	u32_t keys[8];
} keyboard_t;

typedef struct mouse_t
{
	i32_t pos_x;
	i32_t pos_y;
	i32_t delta_x;
	i32_t delta_y;
	i32_t wheel;
	u32_t buttons;
} mouse_t;

typedef struct keyboard_mouse_t
{
	u32_t device;
	keyboard_t keyboard;
	mouse_t mouse;
} keyboard_mouse_t;

keyboard_mouse_t keyboard_and_mouse_device;

/*************************************************************************************************/

#if defined(COMPILER_MSVC) /* MSVC */

i32_t window_input_get_int_value(keyboard_mouse_t* device, u32_t id)
{
	u32_t* keys, mouse_buttons;

	keys = device->keyboard.keys;
	mouse_buttons = device->mouse.buttons;

	switch (id)
	{
	case INPUT_KEY_A: return (keys['A' >> 5] & (1 << ('A' & 0x1F))) != 0;
	case INPUT_KEY_B: return (keys['B' >> 5] & (1 << ('B' & 0x1F))) != 0;
	case INPUT_KEY_C: return (keys['C' >> 5] & (1 << ('C' & 0x1F))) != 0;
	case INPUT_KEY_D: return (keys['D' >> 5] & (1 << ('D' & 0x1F))) != 0;
	case INPUT_KEY_E: return (keys['E' >> 5] & (1 << ('E' & 0x1F))) != 0;
	case INPUT_KEY_F: return (keys['F' >> 5] & (1 << ('F' & 0x1F))) != 0;
	case INPUT_KEY_G: return (keys['G' >> 5] & (1 << ('G' & 0x1F))) != 0;
	case INPUT_KEY_H: return (keys['H' >> 5] & (1 << ('H' & 0x1F))) != 0;
	case INPUT_KEY_I: return (keys['I' >> 5] & (1 << ('I' & 0x1F))) != 0;
	case INPUT_KEY_J: return (keys['J' >> 5] & (1 << ('J' & 0x1F))) != 0;
	case INPUT_KEY_K: return (keys['K' >> 5] & (1 << ('K' & 0x1F))) != 0;
	case INPUT_KEY_L: return (keys['L' >> 5] & (1 << ('L' & 0x1F))) != 0;
	case INPUT_KEY_M: return (keys['M' >> 5] & (1 << ('M' & 0x1F))) != 0;
	case INPUT_KEY_N: return (keys['N' >> 5] & (1 << ('N' & 0x1F))) != 0;
	case INPUT_KEY_O: return (keys['O' >> 5] & (1 << ('O' & 0x1F))) != 0;
	case INPUT_KEY_P: return (keys['P' >> 5] & (1 << ('P' & 0x1F))) != 0;
	case INPUT_KEY_Q: return (keys['Q' >> 5] & (1 << ('Q' & 0x1F))) != 0;
	case INPUT_KEY_R: return (keys['R' >> 5] & (1 << ('R' & 0x1F))) != 0;
	case INPUT_KEY_S: return (keys['S' >> 5] & (1 << ('S' & 0x1F))) != 0;
	case INPUT_KEY_T: return (keys['T' >> 5] & (1 << ('T' & 0x1F))) != 0;
	case INPUT_KEY_U: return (keys['V' >> 5] & (1 << ('V' & 0x1F))) != 0;
	case INPUT_KEY_W: return (keys['W' >> 5] & (1 << ('W' & 0x1F))) != 0;
	case INPUT_KEY_X: return (keys['X' >> 5] & (1 << ('X' & 0x1F))) != 0;
	case INPUT_KEY_Y: return (keys['Y' >> 5] & (1 << ('Y' & 0x1F))) != 0;
	case INPUT_KEY_Z: return (keys['Z' >> 5] & (1 << ('Z' & 0x1F))) != 0;
	case INPUT_KEY_0: return (keys['0' >> 5] & (1 << ('0' & 0x1F))) != 0;
	case INPUT_KEY_1: return (keys['1' >> 5] & (1 << ('1' & 0x1F))) != 0;
	case INPUT_KEY_2: return (keys['2' >> 5] & (1 << ('2' & 0x1F))) != 0;
	case INPUT_KEY_3: return (keys['3' >> 5] & (1 << ('3' & 0x1F))) != 0;
	case INPUT_KEY_4: return (keys['4' >> 5] & (1 << ('4' & 0x1F))) != 0;
	case INPUT_KEY_5: return (keys['5' >> 5] & (1 << ('5' & 0x1F))) != 0;
	case INPUT_KEY_6: return (keys['6' >> 5] & (1 << ('6' & 0x1F))) != 0;
	case INPUT_KEY_7: return (keys['7' >> 5] & (1 << ('7' & 0x1F))) != 0;
	case INPUT_KEY_8: return (keys['8' >> 5] & (1 << ('8' & 0x1F))) != 0;
	case INPUT_KEY_9: return (keys['9' >> 5] & (1 << ('9' & 0x1F))) != 0;
	case INPUT_KEY_ADD: return (keys[VK_ADD >> 5] & (1 << (VK_ADD & 0x1F))) != 0;
	case INPUT_KEY_SUBTRACT: return (keys[VK_SUBTRACT >> 5] & (1 << (VK_SUBTRACT & 0x1F))) != 0;
	case INPUT_KEY_MULTIPLY: return (keys[VK_MULTIPLY >> 5] & (1 << (VK_MULTIPLY & 0x1F))) != 0;
	case INPUT_KEY_DIVIDE: return (keys[VK_DIVIDE >> 5] & (1 << (VK_DIVIDE & 0x1F))) != 0;
	case INPUT_KEY_ESC: return (keys[VK_ESCAPE >> 5] & (1 << (VK_ESCAPE & 0x1F))) != 0;
	case INPUT_KEY_CAPS: return (keys[VK_CAPITAL >> 5] & (1 << (VK_CAPITAL & 0x1F))) != 0;
	case INPUT_KEY_TAB: return (keys[VK_TAB >> 5] & (1 << (VK_TAB & 0x1F))) != 0;
	case INPUT_KEY_SPACE: return (keys[VK_SPACE >> 5] & (1 << (VK_SPACE & 0x1F))) != 0;
	case INPUT_KEY_LSHIFT: return (keys[VK_SHIFT >> 5] & (1 << (VK_SHIFT & 0x1F))) != 0;
	case INPUT_KEY_RSHIFT: return (keys[VK_RSHIFT >> 5] & (1 << (VK_RSHIFT & 0x1F))) != 0;
	case INPUT_KEY_LALT: return (keys[VK_MENU >> 5] & (1 << (VK_MENU & 0x1F))) != 0;
	case INPUT_KEY_RALT: return (keys[VK_RMENU >> 5] & (1 << (VK_RMENU & 0x1F))) != 0;
	case INPUT_KEY_LSTRG: return (keys[VK_CONTROL >> 5] & (1 << (VK_CONTROL & 0x1F))) != 0;
	case INPUT_KEY_RSTRG: return (keys[VK_RCONTROL >> 5] & (1 << (VK_RCONTROL & 0x1F))) != 0;
	case INPUT_KEY_ENTER: return (keys[VK_RETURN >> 5] & (1 << (VK_RETURN & 0x1F))) != 0;
	case INPUT_KEY_BACKSPACE: return (keys[VK_BACK >> 5] & (1 << (VK_BACK & 0x1F))) != 0;
	case INPUT_KEY_ARROW_UP: return (keys[VK_UP >> 5] & (1 << (VK_UP & 0x1F))) != 0;
	case INPUT_KEY_ARROW_DOWN: return (keys[VK_DOWN >> 5] & (1 << (VK_DOWN & 0x1F))) != 0;
	case INPUT_KEY_ARROW_LEFT: return (keys[VK_LEFT >> 5] & (1 << (VK_LEFT & 0x1F))) != 0;
	case INPUT_KEY_ARROW_RIGHT: return (keys[VK_RIGHT >> 5] & (1 << (VK_RIGHT & 0x1F))) != 0;
	case INPUT_KEY_NUM_0: return (keys[VK_NUMPAD0 >> 5] & (1 << (VK_NUMPAD0 & 0x1F))) != 0;
	case INPUT_KEY_NUM_1: return (keys[VK_NUMPAD1 >> 5] & (1 << (VK_NUMPAD1 & 0x1F))) != 0;
	case INPUT_KEY_NUM_2: return (keys[VK_NUMPAD2 >> 5] & (1 << (VK_NUMPAD2 & 0x1F))) != 0;
	case INPUT_KEY_NUM_3: return (keys[VK_NUMPAD3 >> 5] & (1 << (VK_NUMPAD3 & 0x1F))) != 0;
	case INPUT_KEY_NUM_4: return (keys[VK_NUMPAD4 >> 5] & (1 << (VK_NUMPAD4 & 0x1F))) != 0;
	case INPUT_KEY_NUM_5: return (keys[VK_NUMPAD5 >> 5] & (1 << (VK_NUMPAD5 & 0x1F))) != 0;
	case INPUT_KEY_NUM_6: return (keys[VK_NUMPAD6 >> 5] & (1 << (VK_NUMPAD6 & 0x1F))) != 0;
	case INPUT_KEY_NUM_7: return (keys[VK_NUMPAD7 >> 5] & (1 << (VK_NUMPAD7 & 0x1F))) != 0;
	case INPUT_KEY_NUM_8: return (keys[VK_NUMPAD8 >> 5] & (1 << (VK_NUMPAD8 & 0x1F))) != 0;
	case INPUT_KEY_NUM_9: return (keys[VK_NUMPAD9 >> 5] & (1 << (VK_NUMPAD9 & 0x1F))) != 0;
	case INPUT_KEY_F1: return (keys[VK_F1 >> 5] & (1 << (VK_F1 & 0x1F))) != 0;
	case INPUT_KEY_F2: return (keys[VK_F2 >> 5] & (1 << (VK_F2 & 0x1F))) != 0;
	case INPUT_KEY_F3: return (keys[VK_F3 >> 5] & (1 << (VK_F3 & 0x1F))) != 0;
	case INPUT_KEY_F4: return (keys[VK_F4 >> 5] & (1 << (VK_F4 & 0x1F))) != 0;
	case INPUT_KEY_F5: return (keys[VK_F5 >> 5] & (1 << (VK_F5 & 0x1F))) != 0;
	case INPUT_KEY_F6: return (keys[VK_F6 >> 5] & (1 << (VK_F6 & 0x1F))) != 0;
	case INPUT_KEY_F7: return (keys[VK_F7 >> 5] & (1 << (VK_F7 & 0x1F))) != 0;
	case INPUT_KEY_F8: return (keys[VK_F8 >> 5] & (1 << (VK_F8 & 0x1F))) != 0;
	case INPUT_KEY_F9: return (keys[VK_F9 >> 5] & (1 << (VK_F9 & 0x1F))) != 0;
	case INPUT_KEY_F10: return (keys[VK_F10 >> 5] & (1 << (VK_F10 & 0x1F))) != 0;
	case INPUT_KEY_F11: return (keys[VK_F11 >> 5] & (1 << (VK_F11 & 0x1F))) != 0;
	case INPUT_KEY_F12: return (keys[VK_F12 >> 5] & (1 << (VK_F12 & 0x1F))) != 0;
	case INPUT_MOUSE_LEFT: return (mouse_buttons & 1) != 0;
	case INPUT_MOUSE_RIGHT: return (mouse_buttons & 2) != 0;
	case INPUT_MOUSE_MIDDLE: return (mouse_buttons & 4) != 0;
	}

	return 0;
}

flt_t window_input_get_float_value(keyboard_mouse_t* device, u32_t id)
{
	mouse_t mouse;
	
	mouse = device->mouse;
	
	switch (id)
	{
	case INPUT_MOUSE_DELTA_X: return (flt_t)mouse.delta_x;
	case INPUT_MOUSE_DELTA_Y: return (flt_t)mouse.delta_y;
	case INPUT_MOUSE_POS_X: return (flt_t)mouse.pos_x;
	case INPUT_MOUSE_POS_Y: return (flt_t)mouse.pos_y;
	case INPUT_MOUSE_WHEEL: return (flt_t)mouse.wheel;
	}

	return (flt_t)0;
}

void_t window_input_initialize()
{
	memset(&keyboard_and_mouse_device, 0, sizeof(keyboard_mouse_t));
	keyboard_and_mouse_device.device = U32_MAX;
	input_register_device(INPUT_DEVICE_TYPE_KEYBOARD_MOUSE_COMBO,
		(input_get_int_value_t)&window_input_get_int_value,
		(input_get_float_value_t)&window_input_get_float_value, &keyboard_and_mouse_device);
}

u8_t window_process_messages()
{
	MSG msg;
	keyboard_mouse_t* device;

	device = &keyboard_and_mouse_device;
	device->mouse.delta_x = 0;
	device->mouse.delta_y = 0;
	device->mouse.wheel = 0;

	while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
	{
		if (msg.message == WM_QUIT)
			return FALSE;

		TranslateMessage(&msg);
		DispatchMessageW(&msg);
	}

	return TRUE;
}

/*************************************************************************************************/

LRESULT CALLBACK main_window_proc(HWND wnd, UINT msg, WPARAM wp, LPARAM lp)
{
	keyboard_mouse_t* device;

	device = &keyboard_and_mouse_device;

	switch (msg)
	{
	case WM_CREATE:
		SetWindowLongPtr(wnd, 0, (LONG_PTR)((CREATESTRUCT*)lp)->lpCreateParams);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_KEYUP:
	case WM_SYSKEYUP:
	{
		u32_t key;

		key = (u32_t)wp;
		device->keyboard.keys[key >> 5] &= ~(1 << (key & 0x1F));
		break;
	}

	case WM_KEYDOWN:
	case WM_SYSKEYDOWN:
	{
		u32_t key;

		key = (u32_t)wp;
		device->keyboard.keys[key >> 5] |= (1 << (key & 0x1F));
		break;
	}

	case WM_MOUSEWHEEL:
	{
		i32_t wheel_delta;

		wheel_delta = (i32_t)GET_WHEEL_DELTA_WPARAM(wp);

		if (wheel_delta != 0)
			device->mouse.wheel = (wheel_delta > 0) ? 1 : -1;

		break;
	}

	case WM_MOUSEMOVE:
	{
		i32_t pos_x, pos_y;

		pos_x = LOWORD(lp);
		pos_y = HIWORD(lp);
		
		device->mouse.delta_x += pos_x - device->mouse.pos_x;
		device->mouse.delta_y += pos_y - device->mouse.pos_y;
		
		device->mouse.pos_x = pos_x;
		device->mouse.pos_y = pos_y;

		break;
	}

	case WM_LBUTTONDOWN:
	case WM_LBUTTONUP:
	{
		if (msg == WM_LBUTTONDOWN)
			device->mouse.buttons |= 1;
		else
			device->mouse.buttons &= ~1;
		break;
	}

	case WM_RBUTTONDOWN:
	case WM_RBUTTONUP:
	{
		if (msg == WM_RBUTTONDOWN)
			device->mouse.buttons |= 2;
		else
			device->mouse.buttons &= ~2;
		break;
	}

	case WM_MBUTTONDOWN:
	case WM_MBUTTONUP:
	{
		if (msg == WM_MBUTTONDOWN)
			device->mouse.buttons |= 4;
		else
			device->mouse.buttons &= ~4;
		break;
	}

	default:
		return DefWindowProc(wnd, msg, wp, lp);
	}

	return 0;
}

window_t window_new(const char_t* title)
{
	HMODULE instance;
	window_t window;
	wchar_t* wtitle;
	
	static u32_t registered_window_class = FALSE;

	instance = GetModuleHandle(NULL);
	
	if (registered_window_class == FALSE)
	{
		WNDCLASS window_class;
		window_class.style = CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
		window_class.lpfnWndProc = &main_window_proc;
		window_class.cbClsExtra = 0;
		window_class.cbWndExtra = sizeof(void*);
		window_class.hInstance = instance;
		window_class.hIcon = LoadIcon(NULL, IDI_APPLICATION);
		window_class.hCursor = LoadCursor(NULL, IDC_ARROW);
		window_class.hbrBackground = (HBRUSH)(COLOR_WINDOW);
		window_class.lpszMenuName = NULL;
		window_class.lpszClassName = L"main_window_class";
		if (RegisterClass(&window_class) != 0)
			registered_window_class = TRUE;
		else
			exit(101);
	}

	window.handle = CreateWindow(L"main_window_class", wtitle = utf8_to_utf16(title, NULL), WS_POPUP | WS_CAPTION | WS_VISIBLE, (1920 / 4), (1080 / 4),
		(1920 / 2), (1080 / 2), NULL, NULL, instance, NULL);
	free(wtitle);

	return window;
}

void window_free(window_t* window)
{
	DestroyWindow((HWND)window->handle);
}

void window_swap_buffers(window_t* window)
{
	HDC dc;

	dc = GetDC((HWND)window->handle);
	SwapBuffers(dc);
}

#endif /* MSVC */