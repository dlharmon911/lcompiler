#include "lc_common.h"

static int32_t lc_output_source_addons_install(const lc_parse_data_t* data, ALLEGRO_FILE* file)
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

				if (strcmp(addon_name, LC_STRING_ADDON_AUDIO) == 0)
				{
					addon_string = LC_STRING_ALLEGRO_ADDON_INSTALL;
				}

				al_fprintf(file, addon_string, addon_name, data->m_prefix_upper, addon_name);
			}
		}
	}

	return 0;
}

static int32_t lc_output_source_addons_shutdown(const lc_parse_data_t* data, ALLEGRO_FILE* file)
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
				if (strcmp(addon_name, LC_STRING_ADDON_ACODEC) == 0)
				{
					continue;
				}
				else if (strcmp(addon_name, LC_STRING_ADDON_AUDIO) == 0)
				{
					al_fprintf(file, LC_STRING_ALLEGRO_SHUTDOWN_INSTALL, LC_STRING_ADDON_AUDIO, LC_STRING_ADDON_AUDIO);
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

static int32_t lc_output_source_input_install(const lc_parse_data_t* data, ALLEGRO_FILE* file)
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

static int32_t lc_output_source_input_shutdown(const lc_parse_data_t* data, ALLEGRO_FILE* file)
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
				al_fprintf(file, LC_STRING_ALLEGRO_SHUTDOWN_INSTALL, input_name, input_name);
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

static int32_t lc_output_display_options(const lc_parse_data_t* data, ALLEGRO_FILE* file)
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
		char type_string[256] = { 0 };
		char importance_string[256] = { 0 };
	
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

		sprintf_s(type_string, sizeof(type_string), "%s_%s", LC_STRING_ALLEGRO_UPPER, type_name);
		sprintf_s(importance_string, sizeof(importance_string), "%s_%s", LC_STRING_ALLEGRO_UPPER, importance_name);

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
	al_fprintf(file, LC_STRING_EVENTQUEUE_REGISTER_OBJECT, LC_STRING_DISPLAY, LC_STRING_DISPLAY);
	al_fprintf(file, LC_STRING_EVENTQUEUE_REGISTER_OBJECT, LC_STRING_TIMER, LC_STRING_TIMER);
	lc_output_register_input(data, file);
	al_fputc(file, '\n');

	return 0;
}

static int32_t lc_output_function_install_allegro(const lc_parse_data_t* data, ALLEGRO_FILE* file)
{
	if (NULL == data || NULL == file)
	{
		return -1;
	}

	al_fprintf(file, LC_STRING_ALLEGRO_INIT, data->m_prefix_upper);

	lc_output_source_input_install(data, file);
	lc_output_source_addons_install(data, file);

	al_fprintf(file, "\treturn 0;\n");

	return 0;
}

static int32_t lc_output_function_uninstall_allegro(const lc_parse_data_t* data, ALLEGRO_FILE* file)
{
	if (NULL == data || NULL == file)
	{
		return -1;
	}

	lc_output_source_addons_shutdown(data, file);
	lc_output_source_input_shutdown(data, file);
	al_fprintf(file, LC_STRING_ALLEGRO_SHUTDOWN_SYSTEM);

	return 0;
}

static int32_t lc_output_function_zero_data(const lc_parse_data_t* data, ALLEGRO_FILE* file)
{
	if (NULL == data || NULL == file)
	{
		return -1;
	}
	al_fprintf(file, LC_STRING_ZERO_OBJECT, LC_STRING_DISPLAY);
	al_fprintf(file, LC_STRING_ZERO_OBJECT, LC_STRING_TIMER);
	al_fprintf(file, LC_STRING_ZERO_OBJECT, LC_STRING_EVENT_QUEUE);
	return 0;
}

static int32_t lc_output_function_initialize_data(const lc_parse_data_t* data, ALLEGRO_FILE* file)
{
	if (NULL == data || NULL == file)
	{
		return -1;
	}
	lc_output_display(data, file);
	lc_output_timer(data, file);
	lc_output_event_queue(data, file);

	al_fprintf(file, "\treturn 0;\n");

	return 0;
}

static int32_t lc_output_function_uninitialize_data(const lc_parse_data_t* data, ALLEGRO_FILE* file)
{
	if (NULL == data || NULL == file)
	{
		return -1;
	}

	al_fprintf(file, LC_STRING_DESTROY_OBJECT, LC_STRING_EVENT_QUEUE, LC_STRING_EVENT_QUEUE, LC_STRING_EVENT_QUEUE, LC_STRING_EVENT_QUEUE);
	al_fputc(file, '\n');
	al_fprintf(file, LC_STRING_DESTROY_OBJECT, LC_STRING_TIMER, LC_STRING_TIMER, LC_STRING_TIMER, LC_STRING_TIMER);
	al_fputc(file, '\n');
	al_fprintf(file, LC_STRING_DESTROY_OBJECT, LC_STRING_DISPLAY, LC_STRING_DISPLAY, LC_STRING_DISPLAY, LC_STRING_DISPLAY);

	return 0;
}

int32_t lc_output_file_source(const lc_parse_data_t* data)
{
	if (NULL == data)
	{
		return -1;
	}
	ALLEGRO_FILE* file = al_fopen(data->m_output_filename_source, "wb");
	if (NULL == file)
	{
		printf("Failed to open output file: %s\n", data->m_output_filename_source);
		return -1;
	}
	char timestamp[64] = { 0 };
	lc_timestamp(timestamp, sizeof(timestamp), LC_STRING_TIMESTAMP_FORMAT);

	al_fprintf(file, LC_STRING_TIMESTAMP, data->m_output_filename_source, timestamp);
	al_fprintf(file, LC_STRING_INCLUDE, data->m_char);

	al_fprintf(file, LC_STRING_ERROR, data->m_prefix_upper, data->m_prefix_upper);

	al_fprintf(file, ""LC_STRING_DECLARE_FUNCTION_INSTALL_ALLEGRO "\n", data->m_char);
	al_fprintf(file, "{\n");
	lc_output_function_install_allegro(data, file);
	al_fprintf(file, "}\n\n");

	al_fprintf(file, ""LC_STRING_DECLARE_FUNCTION_UNINSTALL_ALLEGRO "\n", data->m_char);
	al_fprintf(file, "{\n");
	lc_output_function_uninstall_allegro(data, file);
	al_fprintf(file, "}\n\n");

	al_fprintf(file, LC_STRING_DECLARE_FUNCTION_ZERO_DATA "\n", data->m_char, data->m_char);
	al_fprintf(file, "{\n");
	al_fprintf(file, LC_STRING_VERIFY_DATA, "data", data->m_prefix_upper, "data", "");
	lc_output_function_zero_data(data, file);
	al_fprintf(file, "}\n\n");

	al_fprintf(file, LC_STRING_DECLARE_FUNCTION_INITIALIZE_DATA "\n", data->m_char, data->m_char);
	al_fprintf(file, "{\n");
	al_fprintf(file, LC_STRING_VERIFY_DATA, "data", data->m_prefix_upper, "data", " -1");
	lc_output_function_initialize_data(data, file);
	al_fprintf(file, "}\n\n");

	al_fprintf(file, LC_STRING_DECLARE_FUNCTION_UNINITIALIZE_DATA "\n", data->m_char, data->m_char);
	al_fprintf(file, "{\n");
	al_fprintf(file, LC_STRING_VERIFY_DATA, "data", data->m_prefix_upper, "data", "");
	lc_output_function_uninitialize_data(data, file);
	al_fprintf(file, "}\n");

	al_fclose(file);

	return 0;
}
