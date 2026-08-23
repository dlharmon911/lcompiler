/*
 * File "test.c" generated from compiled manifest
. * 2026-08-22 21:09:32
 * Do not modify this file.
 */

#include "test.h"

const char* TEST_ERROR_STRING_FAILURE = "Failed to %s %s.";
const char* TEST_ERROR_STRING_NULL_POINTER = "NULL pointer error: \"%s\".";

int32_t test_initialize(test_data_t* data)
{
	if (NULL == data)
	{
		fprintf(stderr, TEST_ERROR_STRING_NULL_POINTER, "data");
		return-1;
	}

	if (!al_init())
	{
		fprintf(stderr, TEST_ERROR_STRING_FAILURE, "initialize", "Allegro library");
		return -1;
	}

	if (!al_install_keyboard())
	{
		fprintf(stderr, TEST_ERROR_STRING_FAILURE, "install", "keyboard");
		return -1;
	}

	if (!al_install_mouse())
	{
		fprintf(stderr, TEST_ERROR_STRING_FAILURE, "install", "mouse");
		return -1;
	}

	if (!al_install_audio())
	{
		fprintf(stderr, TEST_ERROR_STRING_FAILURE, "install", "audio");
		return -1;
	}

	if (!al_init_acodec_addon())
	{
		fprintf(stderr, TEST_ERROR_STRING_FAILURE, "initialize", "acodec");
		return -1;
	}

	if (!al_init_font_addon())
	{
		fprintf(stderr, TEST_ERROR_STRING_FAILURE, "initialize", "font");
		return -1;
	}

	if (!al_init_image_addon())
	{
		fprintf(stderr, TEST_ERROR_STRING_FAILURE, "initialize", "image");
		return -1;
	}

	al_set_new_display_flags(ALLEGRO_WINDOWED|ALLEGRO_OPENGL|ALLEGRO_RESIZABLE|ALLEGRO_PROGRAMMABLE_PIPELINE);
	al_set_new_window_title(TEST_TITLE);
	al_set_new_display_option(ALLEGRO_DEPTH_SIZE, 16, ALLEGRO_SUGGEST);
	data->m_display = al_create_display(TEST_DISPLAY_WIDTH, TEST_DISPLAY_HEIGHT);
	if (NULL == data->m_display)
	{
		fprintf(stderr, TEST_ERROR_STRING_FAILURE, "create", "display");
		return -1;
	}

	data->m_timer = al_create_timer(1.0/TEST_TIMER_SPEED);
	if (NULL == data->m_timer)
	{
		fprintf(stderr, TEST_ERROR_STRING_FAILURE, "create", "timer");
		return -1;
	}

	data->m_event_queue = al_create_event_queue();
	if (NULL == data->m_event_queue)
	{
		fprintf(stderr, TEST_ERROR_STRING_FAILURE, "create", "event queue");
		return -1;
	}

	al_register_event_source(data->m_event_queue, al_get_display_event_source(data->m_display));
	al_register_event_source(data->m_event_queue, al_get_timer_event_source(data->m_timer));
	al_register_event_source(data->m_event_queue, al_get_keyboard_event_source());
	al_register_event_source(data->m_event_queue, al_get_mouse_event_source());

	return 0;
}

void test_shutdown(test_data_t* data)
{
	if (NULL == data)
	{
		fprintf(stderr, TEST_ERROR_STRING_NULL_POINTER, "data");
		return;
	}

	if (NULL != data->m_event_queue)
	{
		al_destroy_event_queue(data->m_event_queue);
		data->m_event_queue = NULL;
	}

	if (NULL != data->m_timer)
	{
		al_destroy_timer(data->m_timer);
		data->m_timer = NULL;
	}

	if (NULL != data->m_display)
	{
		al_destroy_display(data->m_display);
		data->m_display = NULL;
	}

	if (al_is_audio_installed())
	{
		al_uninstall_audio();
	}

	if (al_is_font_addon_initialized())
	{
		al_shutdown_font_addon();
	}

	if (al_is_image_addon_initialized())
	{
		al_shutdown_image_addon();
	}

	if (al_is_system_installed())
	{
		al_uninstall_system();
	}
}
