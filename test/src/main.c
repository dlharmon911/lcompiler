#include <stdio.h>
#include "t_manifest.h"

typedef struct data_tag_t
{
	ALLEGRO_DISPLAY* m_display;
	ALLEGRO_TIMER* m_timer;
	ALLEGRO_EVENT_QUEUE* m_event_queue;
	bool m_is_running;
	bool m_logic_update;
} data_t;

static void data_zero(data_t* data)
{
	if (NULL == data)
	{
		return;
	}

	t_manifest_zero_data((t_manifest_data_t*)data);
	data->m_is_running = true;
	data->m_logic_update = false;
} 

static int32_t initialize_app(data_t* data)
{
	if (t_manifest_install_allegro() != 0)
	{
		fprintf(stderr, "Failed to install Allegro.\n");
		return 1;
	}

	if (t_manifest_initialize_data((t_manifest_data_t*)data) != 0)
	{
		fprintf(stderr, "Failed to initialize manifest.\n");
		return 1;
	}

	return 0;
}

static void uninitialize_app(data_t* data)
{
	t_manifest_uninitialize_data((t_manifest_data_t*)data);
	t_manifest_uninstall_allegro();
}

static void input(data_t* data)
{
	ALLEGRO_EVENT event;

	while (!al_is_event_queue_empty(data->m_event_queue))
	{
		al_wait_for_event(data->m_event_queue, &event);
		switch (event.type)
		{
		case ALLEGRO_EVENT_TIMER:
		{
			data->m_logic_update = true;
		} break;
		case ALLEGRO_EVENT_DISPLAY_CLOSE:
		{
			data->m_is_running = false;
		} break;
		case ALLEGRO_EVENT_KEY_DOWN:
		{
			if (event.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
			{
				data->m_is_running = false;
			}
		}break;
		default:
			break;
		}
	}
}

static void update(data_t* data)
{
	// Update game logic here
}

static void render(data_t* data)
{
	al_clear_to_color(al_map_rgb(0, 64, 0));
	// Render game objects here
	al_flip_display();
}

static void loop(data_t* data)
{
	al_start_timer(data->m_timer);

	while (data->m_is_running)
	{
		input(data);
		if (data->m_logic_update)
		{
			update(data);
			data->m_logic_update = false;
		}
		render(data);
		al_rest(0.01);
	}

	al_stop_timer(data->m_timer);
}

int32_t main(int32_t argc, char** argv)
{
	data_t data = { 0 };

	data_zero(&data);

	if (initialize_app(&data) == 0)
	{
		loop(&data);
	}

	uninitialize_app(&data);

	return 0;
}
