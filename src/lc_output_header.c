#include "lc_common.h"

static int32_t lc_output_defines(const lc_parse_data_t* data, ALLEGRO_FILE* file)
{
	if (NULL == data || NULL == file)
	{
		return -1;
	}
	
	if (NULL == data->m_section.m_defines)
	{
		return 0;
	}

	size_t define_count = ogle_darray_size(data->m_section.m_defines);

	for (size_t i = 0; i < define_count; i++)
	{
		const lc_define_t* define = &data->m_section.m_defines[i];

		al_fprintf(file, LC_STRING_DEFINE);

		al_fprintf(file, "%s_", data->m_prefix_upper);

		if (!ogle_stringview_is_empty(define->m_prefix))
		{
			for (size_t j = 0; j < define->m_prefix.m_length; j++)
			{
				al_fputc(file, (char)lc_char_upper((int32_t)define->m_prefix.m_data[j]));
			}
			al_fputc(file, '_');
		}

		for (size_t j = 0; j < define->m_name.m_length; j++)
		{
			al_fputc(file, (char)lc_char_upper((int32_t)define->m_name.m_data[j]));
		}

		al_fputc(file, ' ');
		
		if (define->m_type == LC_DEFINE_TYPE_STRING)
		{
			al_fputc(file, '"');
		}

		al_fprintf(file, "%.*s", (int32_t)define->m_value.m_length, define->m_value.m_data);

		if (define->m_type == LC_DEFINE_TYPE_STRING)
		{
			al_fputc(file, '"');
		}
		al_fputc(file, '\n');
	}

	al_fputc(file, '\n');

	return 0;
}

static int32_t lc_output_addons(const lc_parse_data_t* data, ALLEGRO_FILE* file)
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
				al_fprintf(file, LC_STRING_ALLEGRO_ADDON_INCLUDE, addon_name);
			}
		}
	}

	return 0;
}

int32_t lc_output_file_header(const lc_parse_data_t* data)
{
	if (NULL == data)
	{
		return -1;
	}
	ALLEGRO_FILE* file = al_fopen(data->m_output_filename_header, "wb");
	if (NULL == file)
	{
		printf("Failed to open output file: %s\n", data->m_output_filename_header);
		return -1;
	}

	char timestamp[64] = { 0 };
	lc_timestamp(timestamp, sizeof(timestamp), LC_STRING_TIMESTAMP_FORMAT);

	al_fprintf(file, LC_STRING_TIMESTAMP, data->m_output_filename_header, timestamp);
	al_fprintf(file, LC_STRING_HEADER_GUARD_START, data->m_prefix_upper, data->m_prefix_upper);
	al_fprintf(file, LC_STRING_ALLEGRO_INCLUDE);
	lc_output_addons(data, file);
	al_fprintf(file, LC_STRING_DEFAULT_INCLUDE);
	al_fprintf(file, LC_STRING_HEADER_SECTION, LC_STRING_SECTION_DEFINES);
	lc_output_defines(data, file);
	al_fprintf(file, LC_STRING_HEADER_SECTION, LC_STRING_SECTION_TYPEDEF);
	al_fprintf(file, LC_STRING_DATA_TYPEDEF, data->m_char, data->m_char);
	al_fprintf(file, LC_STRING_HEADER_SECTION, LC_STRING_SECTION_STRUCT);
	al_fprintf(file, LC_STRING_DATA_STRUCT, data->m_char);
	al_fprintf(file, LC_STRING_HEADER_SECTION, LC_STRING_SECTION_FUNCTIONS);

	al_fprintf(file, LC_STRING_COMMENT_INSTALL_ALLEGRO);
	al_fprintf(file, LC_STRING_DECLARE_FUNCTION_INSTALL_ALLEGRO ";\n", data->m_char, data->m_char);
	al_fputc(file, '\n');
	al_fprintf(file, LC_STRING_COMMENT_UNINSTALL_ALLEGRO);
	al_fprintf(file, LC_STRING_DECLARE_FUNCTION_UNINSTALL_ALLEGRO ";\n", data->m_char, data->m_char);
	al_fputc(file, '\n');
	al_fprintf(file, LC_STRING_COMMENT_ZERO_DATA);
	al_fprintf(file, LC_STRING_DECLARE_FUNCTION_ZERO_DATA ";\n", data->m_char, data->m_char);
	al_fputc(file, '\n');
	al_fprintf(file, LC_STRING_COMMENT_INITIALIZE_DATA);
	al_fprintf(file, LC_STRING_DECLARE_FUNCTION_INITIALIZE_DATA ";\n", data->m_char, data->m_char);
	al_fputc(file, '\n');
	al_fprintf(file, LC_STRING_COMMENT_UNINITIALIZE_DATA);
	al_fprintf(file, LC_STRING_DECLARE_FUNCTION_UNINITIALIZE_DATA ";\n", data->m_char, data->m_char);
	al_fputc(file, '\n');
	al_fprintf(file, LC_STRING_HEADER_GUARD_END, data->m_prefix_upper);
	al_fclose(file);
	return 0;
}
