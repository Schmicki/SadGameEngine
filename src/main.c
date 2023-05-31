#include <time.h>

#include "platform.h"
#include "math.h"
#include "containers.h"
#include "input.h"
#include "engine.h"
#include "opengl.h"
#include "scenes.h"

#if defined(OS_WINDOWS) /* OS_WINDOWS */

/*************************************************************************************************/

u32_t u32_hash_generic(void_t* in_a)
{
    return *(u32_t*)in_a;
}

i32_t u32_cmp_generic(void_t* in_a, void_t* in_b)
{
    return *(u32_t*)in_a - *(u32_t*)in_b;
}

void_t get_input_devices(u32_t* out_gamepad, u32_t* out_keyboard)
{
    u32_t i;

    for (i = 0; i < MAX_INPUT_DEVICES; i++)
    {
        if (input_devices[i].type == INPUT_DEVICE_TYPE_KEYBOARD_MOUSE_COMBO)
        {
            printf("keyboard: %d\n", i);

            if (*out_keyboard == MAX_INPUT_DEVICES)
                *out_keyboard = i;
        }
        else if (input_devices[i].type == INPUT_DEVICE_TYPE_GAMEPAD)
        {
            printf("gamepad: %d\n", i);

            if (*out_gamepad == MAX_INPUT_DEVICES)
                *out_gamepad = i;
        }
    }
}

u8_t camera_movement(camera_t* camera, flt_t delta, u32_t gamepad, u32_t keyboard)
{
    flt_t move_x, move_y, move_z, look_x, look_y, speed;
    quat_t rotation;
    vec3_t forward, right, up, movement;

    move_x = input_get_device_float_value(gamepad, INPUT_GAMEPAD_JOYSTICK_LEFT_X);
    move_y = input_get_device_float_value(gamepad, INPUT_GAMEPAD_JOYSTICK_LEFT_Y);
    move_z = (flt_t)input_get_device_int_value(gamepad, INPUT_GAMEPAD_DPAD_UP)
        - (flt_t)input_get_device_int_value(gamepad, INPUT_GAMEPAD_DPAD_DOWN);
    look_x = -input_get_device_float_value(gamepad, INPUT_GAMEPAD_JOYSTICK_RIGHT_X);
    look_y = input_get_device_float_value(gamepad, INPUT_GAMEPAD_JOYSTICK_RIGHT_Y);

    speed = input_get_device_int_value(keyboard, INPUT_KEY_LSHIFT) ? 3.0f : 1.0f;

    if (input_get_device_int_value(keyboard, INPUT_MOUSE_RIGHT))
    {
        look_x = input_get_device_float_value(keyboard, INPUT_MOUSE_DELTA_X);
        look_y = input_get_device_float_value(keyboard, INPUT_MOUSE_DELTA_Y);

        move_x = move_x + (flt_t)input_get_device_int_value(keyboard, INPUT_KEY_D)
            - (flt_t)input_get_device_int_value(keyboard, INPUT_KEY_A);
        move_y = move_y + (flt_t)input_get_device_int_value(keyboard, INPUT_KEY_W)
            - (flt_t)input_get_device_int_value(keyboard, INPUT_KEY_S);
        move_z = move_z + (flt_t)input_get_device_int_value(keyboard, INPUT_KEY_E)
            - (flt_t)input_get_device_int_value(keyboard, INPUT_KEY_Q);
    }

    if (input_get_device_int_value(keyboard, INPUT_KEY_LALT) && input_get_device_int_value(keyboard, INPUT_KEY_G))
    {
        camera->location = vec3_set(0.0f, -2.0f, 0.0f);
        camera->scale = vec3_set(1.0f, 1.0f, 1.0f);
        camera->rotation = vec3_set(0.0f, 0.0f, 0.0f);
    }

    camera->rotation.z += look_x * 0.2f;
    camera->rotation.x += look_y * -0.2f * (16.0f / 9.0f);
    camera->rotation.x = flt_mod(camera->rotation.x, 360);
    camera->rotation.y = flt_mod(camera->rotation.y, 360);
    camera->rotation.z = flt_mod(camera->rotation.z, 360);

    rotation = quat_euler_angles(camera->rotation);
    forward = vec3_rotate(vec3_set(0, 1, 0), rotation);
    right = vec3_rotate(vec3_set(1, 0, 0), rotation);
    up = vec3_rotate(vec3_set(0, 0, 1), rotation);

    movement = vec3_add(vec3_add(vec3_mul(forward, move_y), vec3_mul(right, move_x)),
        vec3_mul(up, move_z));

    if (vec3_dot(movement, movement) > 1)
        movement = vec3_unit(movement);

    camera->location = vec3_add(camera->location, vec3_mul(movement, speed * delta * 4));
}

void main(int argc, char** args)
{
    u32_t keyboard, gamepad;
    flt_t delta, time;
    i32_t start, end;
    gl_context_t context;
    scene_light_t light_scene;
    //scene_depth_t depth_scene;

    keyboard = MAX_INPUT_DEVICES;
    gamepad = MAX_INPUT_DEVICES;
    engine_initialize();
    get_input_devices(&gamepad, &keyboard);

    start = clock();
    end = start;
    delta = 0.0;
    time = 0.0;
    context = gl_context_new(&main_window);

    if (glewInit() != GLEW_OK)
        goto end;

    printf("\n%s\n", glGetString(GL_VERSION));

    scene_light_new(&light_scene);
    //scene_depth_new(&depth_scene);

    while (engine_update() == TRUE)
    {
        /* input */

        if (input_get_device_int_value(keyboard, INPUT_KEY_ESC))
            break;

        camera_movement(&light_scene.camera, delta, gamepad, keyboard);
        //camera_movement(&depth_scene.camera, delta, gamepad, keyboard);

        /* render */

        scene_light_render(&light_scene, time, delta);
        //scene_depth_render(&depth_scene, time, delta);

        /* compute time */

        end = clock(), delta = (flt_t)(end - start) / CLOCKS_PER_SEC, time += delta;
        start = clock();

        gl_error_loop();
        window_swap_buffers(&main_window);
    }

    scene_light_free(&light_scene);
    //scene_depth_free(&depth_scene);
    gl_context_free(&main_window, context);

end:
    engine_destroy();
}

#endif /* OS_WINDOWS */