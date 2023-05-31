#include "engine.h"
#include "input.h"
#include "window.h"
#include "opengl.h"

/*************************************************************************************************/

player_t players[MAX_PLAYERS + 1];

#if defined(OS_HAS_WINDOW) /* OS_HAS_WINDOW */

window_t main_window;

#endif /* OS_HAS_WINDOW */

render_interface_t render_interface;

/*************************************************************************************************/

u8_t engine_initialize()
{
	if (input_initialize() == FALSE)
		return FALSE;


#if defined(OS_HAS_WINDOW) /* OS_HAS_WINDOW */

	main_window = window_new("Sad Engine");

#endif /* OS_HAS_WINDOW */

	return TRUE;
}

u8_t engine_update()
{
#if defined(OS_HAS_WINDOW) /* OS_HAS_WINDOW */

	if (window_process_messages() == FALSE)
		return FALSE;

#endif /* OS_HAS_WINDOW */

	if (input_update() == FALSE)
		return FALSE;

	return TRUE;
}

u8_t engine_destroy()
{
#if defined(OS_HAS_WINDOW) /* OS_HAS_WINDOW */

	window_free(&main_window);

#endif /* OS_HAS_WINDOW */

	return 0;
}