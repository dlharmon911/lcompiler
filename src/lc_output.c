#include "lc_common.h"

int32_t lc_output_files(const lc_parse_data_t* data)
{
	if (NULL == data)
	{
		return -1;
	}

	if (!al_make_directory(data->m_directory))
	{
		printf("Failed to create output directory: %s\n", data->m_directory);
		return -1;
	}
	al_change_directory(data->m_directory);

	if (lc_output_file_header(data) != 0)
	{
		return -1;
	}

	if (lc_output_file_source(data) != 0)
	{
		return -1;
	}

	return 0;
}