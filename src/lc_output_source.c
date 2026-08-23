#include "lc_common.h"

#define LC_STRING_ERROR "const char* %s_ERROR_STRING_FAILURE = \"Failed to %%s %%s.\";\n" \
"const char* %s_ERROR_STRING_NULL_POINTER = \"NULL pointer error: \\\"%%s\\\".\";\n\n"


#define LC_STRING_ALLEGRO_INIT 	"\tif (!al_init())\n" \
	"\t{\n" \
	"\t\tfprintf(stderr, %s_ERROR_STRING_FAILURE, \"initialize\", \"Allegro library\");\n" \
	"\t\treturn -1;\n" \
	"\t}\n\n"

#define LC_STRING_ALLEGRO_ADDON_INSTALL	"\tif (!al_install_%s())\n" \
	"\t{\n" \
	"\t\tfprintf(stderr, %s_ERROR_STRING_FAILURE, \"install\", \"%s\");\n" \
	"\t\treturn -1;\n" \
	"\t}\n\n"

#define LC_STRING_ALLEGRO_ADDON_INIT 	"\tif (!al_init_%s_addon())\n" \
	"\t{\n" \
	"\t\tfprintf(stderr, %s_ERROR_STRING_FAILURE, \"initialize\", \"%s\");\n" \
	"\t\treturn -1;\n" \
	"\t}\n\n"

#define LC_STRING_ALLEGRO_SHUTDOWN_ADDON 	"\tif (al_is_%s_addon_initialized())\n" \
	"\t{\n" \
	"\t\tal_shutdown_%s_addon();\n" \
	"\t}\n\n"

#define LC_STRING_ALLEGRO_SHUTDOWN_AUDIO 	"\tif (al_is_audio_installed())\n" \
	"\t{\n" \
	"\t\tal_uninstall_audio();\n" \
	"\t}\n\n"

#define LC_STRING_ALLEGRO_SHUTDOWN_SYSTEM 	"\tif (al_is_system_installed())\n" \
	"\t{\n" \
	"\t\tal_uninstall_system();\n" \
	"\t}\n"

#define LC_STRING_VERIFY_DATA	"\tif (NULL == %s)\n" \
	"\t{\n" \
	"\t\tfprintf(stderr, %s_ERROR_STRING_NULL_POINTER, \"%s\");\n" \
	"\t\treturn%s;\n" \
	"\t}\n\n"

#define LC_STRING_DISPLAY_CREATE "\tdata->m_display = al_create_display(%s_DISPLAY_WIDTH, %s_DISPLAY_HEIGHT);\n" \
	"\tif (NULL == data->m_display)\n" \
	"\t{\n" \
	"\t\tfprintf(stderr, %s_ERROR_STRING_FAILURE, \"create\", \"display\");\n" \
	"\t\treturn -1;\n" \
	"\t}\n\n"

#define LC_STRING_TIMER_CREATE "\tdata->m_timer = al_create_timer(1.0/%s_TIMER_SPEED);\n" \
	"\tif (NULL == data->m_timer)\n" \
	"\t{\n" \
	"\t\tfprintf(stderr, %s_ERROR_STRING_FAILURE, \"create\", \"timer\");\n" \
	"\t\treturn -1;\n" \
	"\t}\n\n"

#define LC_STRING_SET_DISPLAY_OPTION	"\tal_set_new_display_option(%s, %d, %s);\n"

#define LC_STRING_SET_WINDOW_TITLE "\tal_set_new_window_title(%s_TITLE);\n"
#define LC_STRING_DESTROY_OBJECT "\tif (NULL != data->m_%s)\n" \
	"\t{\n" \
	"\t\tal_destroy_%s(data->m_%s);\n" \
	"\t\tdata->m_%s = NULL;\n" \
	"\t}\n\n"

#define LC_STRING_EVENTQUEUE_CREATE "\tdata->m_event_queue = al_create_event_queue();\n" \
	"\tif (NULL == data->m_event_queue)\n" \
	"\t{\n" \
	"\t\tfprintf(stderr, %s_ERROR_STRING_FAILURE, \"create\", \"event queue\");\n" \
	"\t\treturn -1;\n" \
	"\t}\n\n"

#define LC_STRING_EVENTQUEUE_REGISTER_OBJECT "\tal_register_event_source(data->m_event_queue, al_get_%s_event_source(data->m_%s));\n"
#define LC_STRING_EVENTQUEUE_REGISTER_INPUT "\tal_register_event_source(data->m_event_queue, al_get_%s_event_source());\n"


static int32_t lc_output_source_addons(const lc_parse_data_t* data, ALLEGRO_FILE* file)
{
	if (NULL == data || NULL == file)
	{
		return -1;
	}

	for (size_t i = 0; i < LC_ADDON_FLAG_ID_COUNT; i++)
	{
		int32_t flag = 1 << i;

		if (data->m_section.m_addon_flags & flag)
		{
			const char* addon_name = lc_addon_flag_name(flag);
			if (NULL != addon_name)
			{
				const char* addon_string = LC_STRING_ALLEGRO_ADDON_INIT;

				if (strcmp(addon_name, "audio") == 0)
				{
					addon_string = LC_STRING_ALLEGRO_ADDON_INSTALL;
				}

				al_fprintf(file, addon_string, addon_name, data->m_prefix_upper, addon_name);
			}
		}
	}

	return 0;
}

static int32_t lc_output_source_input(const lc_parse_data_t* data, ALLEGRO_FILE* file)
{
	if (NULL == data || NULL == file)
	{
		return -1;
	}

	for (size_t i = 0; i < LC_INPUT_FLAG_ID_COUNT; i++)
	{
		int32_t flag = 1 << i;

		if (data->m_section.m_input_flags & flag)
		{
			const char* input_name = lc_input_flag_name(flag);
			if (NULL != input_name)
			{
				al_fprintf(file, LC_STRING_ALLEGRO_ADDON_INSTALL, input_name, data->m_prefix_upper, input_name);
			}
		}
	}

	return 0;
}

static int32_t lc_output_register_input(const lc_parse_data_t* data, ALLEGRO_FILE* file)
{
	if (NULL == data || NULL == file)
	{
		return -1;
	}
	
	for (size_t i = 0; i < LC_INPUT_FLAG_ID_COUNT; i++)
	{
		int32_t flag = 1 << i;

		if (data->m_section.m_input_flags & flag)
		{
			const char* input_name = lc_input_flag_name(flag);
			if (NULL != input_name)
			{
				al_fprintf(file, LC_STRING_EVENTQUEUE_REGISTER_INPUT, input_name);
			}
		}
	}

	return 0;
}

static int32_t lc_output_display_flags(const lc_parse_data_t* data, ALLEGRO_FILE* file)
{
	if (NULL == data || NULL == file)
	{
		return -1;
	}

	al_fprintf(file, "\tal_set_new_display_flags(");
	if (data->m_section.m_display_flags)
	{
		size_t c = 0;

		for (size_t i = 0; i < LC_DISPLAY_FLAG_ID_COUNT; i++)
		{
			int32_t flag = 1 << i;

			if (data->m_section.m_display_flags & flag)
			{
				const char* display_name = lc_display_flag_name(flag);
				if (NULL != display_name)
				{
					char upper_name[256] = { 0 };
					for (size_t j = 0; j < strlen(display_name) && j < sizeof(upper_name) - 1; j++)
					{
						upper_name[j] = (char)lc_char_upper((int32_t)display_name[j]);
					}
					upper_name[strlen(display_name)] = '\0';

					if (c)
					{
						al_fputc(file, '|');
					}

					al_fprintf(file, "ALLEGRO_%s", upper_name);
					++c;
				}
			}
		}
	}
	al_fprintf(file, ");\n");

	return 0;
}

int32_t lc_output_display_options(const lc_parse_data_t* data, ALLEGRO_FILE* file)
{
	if (NULL == data || NULL == file)
	{
		return -1;
	}

	if (NULL == data->m_section.m_display_options)
	{
		return 0;
	}

	size_t count = ogle_darray_size(data->m_section.m_display_options);
	
	if (0 == count)
	{
		return 0;
	}

	for (size_t i = 0; i < count; i++)
	{
		const lc_display_option_t* option = (const lc_display_option_t*)ogle_darray_get(data->m_section.m_display_options, i);
		char type_string[256] = "ALLEGRO_";
		char importance_string[256] = "ALLEGRO_";
	
		const char* type_name = lc_display_option_type_name(option->m_type);

		if (NULL == type_name)
		{
			return -1;
		}

		const char* importance_name = lc_display_option_importance_name(option->m_importance);

		if (NULL == importance_name)
		{
			return -1;
		}

		memcpy(type_string + strlen("ALLEGRO_"), type_name, strlen(type_name));
		type_string[strlen("ALLEGRO_") + strlen(type_name)] = '\0';
		memcpy(importance_string + strlen("ALLEGRO_"), importance_name, strlen(importance_name));
		importance_string[strlen("ALLEGRO_") + strlen(importance_name)] = '\0';

		lc_capitalize_string(type_string, sizeof(type_string));
		lc_capitalize_string(importance_string, sizeof(importance_string));

		al_fprintf(file, LC_STRING_SET_DISPLAY_OPTION, type_string, option->m_value, importance_string);
	}

	return 0;
}

static int32_t lc_output_display(const lc_parse_data_t* data, ALLEGRO_FILE* file)
{
	if (NULL == data || NULL == file)
	{
		return -1;
	}

	lc_output_display_flags(data, file);
	al_fprintf(file, LC_STRING_SET_WINDOW_TITLE, data->m_prefix_upper);
	lc_output_display_options(data, file);
	al_fprintf(file, LC_STRING_DISPLAY_CREATE, data->m_prefix_upper, data->m_prefix_upper, data->m_prefix_upper);

	return 0;
}

static int32_t lc_output_timer(const lc_parse_data_t* data, ALLEGRO_FILE* file)
{
	if (NULL == data || NULL == file)
	{
		return -1;
	}

	al_fprintf(file, LC_STRING_TIMER_CREATE, data->m_prefix_upper, data->m_prefix_upper, data->m_prefix_upper);

	return 0;
}

static int32_t lc_output_event_queue(const lc_parse_data_t* data, ALLEGRO_FILE* file)
{
	if (NULL == data || NULL == file)
	{
		return -1;
	}

	al_fprintf(file, LC_STRING_EVENTQUEUE_CREATE, data->m_prefix_upper);
	al_fprintf(file, LC_STRING_EVENTQUEUE_REGISTER_OBJECT, "display", "display");
	al_fprintf(file, LC_STRING_EVENTQUEUE_REGISTER_OBJECT, "timer", "timer");
	lc_output_register_input(data, file);

	return 0;
}

static int32_t lc_output_function_initialize(const lc_parse_data_t* data, ALLEGRO_FILE* file)
{
	if (NULL == data || NULL == file)
	{
		return -1;
	}

	al_fprintf(file, LC_STRING_ALLEGRO_INIT, data->m_prefix_upper);

	lc_output_source_input(data, file);
	lc_output_source_addons(data, file);

	lc_output_display(data, file);
	lc_output_timer(data, file);
	lc_output_event_queue(data, file);

	al_fprintf(file, "\n\treturn 0;\n");

	return 0;
}

static int32_t lc_output_function_shutdown_addons(const lc_parse_data_t* data, ALLEGRO_FILE* file)
{
	if (NULL == data || NULL == file)
	{
		return -1;
	}

	al_fprintf(file, LC_STRING_DESTROY_OBJECT, "event_queue", "event_queue", "event_queue", "event_queue");
	al_fprintf(file, LC_STRING_DESTROY_OBJECT, "timer", "timer", "timer", "timer");
	al_fprintf(file, LC_STRING_DESTROY_OBJECT, "display", "display", "display", "display");

	for (size_t i = 0; i < LC_ADDON_FLAG_ID_COUNT; i++)
	{
		int32_t flag = 1 << i;
		if (data->m_section.m_addon_flags & flag)
		{
			const char* addon_name = lc_addon_flag_name(flag);
			if (NULL != addon_name)
			{
				if (strcmp(addon_name, "acodec") == 0)
				{
					continue;
				}
				else if (strcmp(addon_name, "audio") == 0)
				{
					al_fprintf(file, LC_STRING_ALLEGRO_SHUTDOWN_AUDIO);
				}
				else
				{
					al_fprintf(file, LC_STRING_ALLEGRO_SHUTDOWN_ADDON, addon_name, addon_name);
				}
			}
		}
	}

	return 0;
}

static int32_t lc_output_function_shutdown(const lc_parse_data_t* data, ALLEGRO_FILE* file)
{
	if (NULL == data || NULL == file)
	{
		return -1;
	}

	lc_output_function_shutdown_addons(data, file);

	al_fprintf(file, LC_STRING_ALLEGRO_SHUTDOWN_SYSTEM);

	return 0;
}

int32_t lc_output_file_source(const lc_parse_data_t* data)
{
	if (NULL == data)
	{
		return -1;
	}
	ALLEGRO_FILE* file = al_fopen(data->m_output_filename_source, "w");
	if (NULL == file)
	{
		printf("Failed to open output file: %s\n", data->m_output_filename_source);
		return -1;
	}
	char timestamp[64] = { 0 };
	lc_timestamp(timestamp, sizeof(timestamp), LC_STRING_TIMESTAMP_FORMAT);

	al_fprintf(file, LC_STRING_TIMESTAMP, data->m_output_filename_source, timestamp);
	al_fprintf(file, LC_STRING_INCLUDE, data->m_prefix);

	al_fprintf(file, LC_STRING_ERROR, data->m_prefix_upper, data->m_prefix_upper);

	al_fprintf(file, LC_STRING_FUNCTION_INITIALIZE "\n", data->m_prefix, data->m_prefix);
	al_fprintf(file, "{\n");
	al_fprintf(file, LC_STRING_VERIFY_DATA, "data", data->m_prefix_upper, "data", "-1");
	lc_output_function_initialize(data, file);
	al_fprintf(file, "}\n\n");

	al_fprintf(file, LC_STRING_FUNCTION_SHUTDOWN "\n", data->m_prefix, data->m_prefix);
	al_fprintf(file, "{\n");
	al_fprintf(file, LC_STRING_VERIFY_DATA, "data", data->m_prefix_upper, "data", "");
	lc_output_function_shutdown(data, file);
	al_fprintf(file, "}\n");

	al_fclose(file);

	return 0;
}
