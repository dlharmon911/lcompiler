#include "lc_common.h"


static void lc_main_erase_files(lc_parse_data_t* data)
{
	if (NULL == data)
	{
		return;
	}

	if (al_filename_exists(data->m_output_filename_header))
	{
		al_remove_filename(data->m_output_filename_header);
	}

	if (al_filename_exists(data->m_output_filename_source))
	{
		al_remove_filename(data->m_output_filename_source);
	}

	if (al_filename_exists(data->m_directory))
	{
		al_remove_filename(data->m_directory);
	}
}

static void lc_main_zero_data(lc_parse_data_t* data, const char* executable_name)
{
	if (NULL == data || NULL == executable_name)
	{
		return;
	}

	strcpy_s(data->m_current_directory, sizeof(data->m_current_directory), al_get_current_directory());
	strcpy_s(data->m_executable_name, sizeof(data->m_executable_name), executable_name);
	strcpy_s(data->m_prefix, sizeof(data->m_prefix), LC_STRING_DEFAULT_PREFIX);
	strcpy_s(data->m_directory, sizeof(data->m_directory), LC_STRING_DEFAULT_DIRECTORY);
	strcpy_s(data->m_input_filename, sizeof(data->m_input_filename), LC_STRING_DEFAULT_INPUT_FILE);
	strcpy_s(data->m_output_filename_header, sizeof(data->m_output_filename_header), LC_STRING_DEFAULT_PREFIX ".h");
	strcpy_s(data->m_output_filename_source, sizeof(data->m_output_filename_source), LC_STRING_DEFAULT_PREFIX ".c");
	data->m_user_data = NULL;
}

static void lc_main_cleanup(lc_parse_data_t* data)
{
	if (NULL == data)
	{
		return;
	}

	lc_section_clear(&data->m_section);
	al_free(data);
}

static int32_t lc_main_process(int32_t argc, char** argv, lc_parse_data_t* data, xml_document_t** xml_doc)
{
	// Load the XML document
	if (xml_document_load_from_file(data->m_input_filename, xml_doc) < 0)
	{
		printf("Failed to load XML document: %s\n", data->m_input_filename);
		return -1;
	}

	const xml_element_t* root_element = xml_document_get_root_element_const(*xml_doc);

	if (NULL == root_element)
	{
		printf("Failed to get root element from XML document: %s\n", data->m_input_filename);
		return -1;
	}

	o_stringview_t name = xml_element_get_name(root_element);
	if (!ogle_stringview_equals_cstr(name, LC_STRING_MANIFEST))
	{
		printf("Root element is not a manifest: %s\n", data->m_input_filename);
		return -1;
	}


	if (lc_parse_manifest(data, root_element) < 0)
	{
		printf("Failed to parse manifest from XML document: %s\n", data->m_input_filename);
		return -1;
	}

	return 0;
}

static void lc_output_data(const lc_parse_data_t* data)
{
	if (NULL == data)
	{
		return;
	}

	fprintf(stderr, "Executable Name: %s\n", data->m_executable_name);
	fprintf(stderr, "Current Directory: %s\n", data->m_current_directory);
	fprintf(stderr, "Directory: %s\n", data->m_directory);
	fprintf(stderr, "Prefix: %s\n", data->m_prefix);
	fprintf(stderr, "Prefix Upper: %s\n", data->m_prefix_upper);
	fprintf(stderr, "Input Filename: %s\n", data->m_input_filename);
	fprintf(stderr, "Output Filename Header: %s\n", data->m_output_filename_header);
	fprintf(stderr, "Output Filename Source: %s\n", data->m_output_filename_source);
}

int32_t main(int32_t argc, char** argv)
{
	int32_t result = 0;
	lc_parse_data_t* data = NULL;
	xml_document_t* xml_doc = NULL;

	fprintf(stderr, "%s\n", LC_STRING_APP_NAME);
	fprintf(stderr, "Version: %s\n", LC_STRING_VERSION);

	if (!al_init())
	{
		fprintf(stderr, "Failed to initialize Allegro\n");
		return -1;
	}

	data = (lc_parse_data_t*)al_malloc(sizeof(lc_parse_data_t));
	if (NULL == data)
	{
		fprintf(stderr, "Failed to allocate memory for parse data\n");
		return -1;
	}
	lc_main_zero_data(data, argv[0]);

	result = lc_parse_command_line_arguments(argc - 1, argv + 1, data);
	if (result < 0)
	{
		// Command line arguments were invalid, print usage information and exit with error code.
		fprintf(stderr, "Usage: %s <file>\n", data->m_executable_name);
		return -1;
	}

	if (result > 0)
	{
		// Command line arguments were parsed successfully, but no further action is needed (e.g., help or version info was displayed).
		return 0;
	}

	sprintf_s(data->m_output_filename_header, sizeof(data->m_output_filename_header), "%s.h", data->m_prefix);
	sprintf_s(data->m_output_filename_source, sizeof(data->m_output_filename_source), "%s.c", data->m_prefix);

	result = lc_main_process(argc, argv, data, &xml_doc);

	if (0 == result)
	{
		result = lc_output_files(data);
	}

	if (xml_doc)
	{
		xml_document_destroy(xml_doc);
		xml_doc = NULL;
	}

	lc_main_cleanup(data);

	if (result < 0)
	{
		lc_main_erase_files(data);
	}

	al_change_directory(data->m_current_directory);

	return result;
}
