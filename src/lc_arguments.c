#include "lc_common.h"

enum LC_ARGUMENT_TYPES
{
	LC_ARGUEMENT_TYPE_SINGLE_COMMAND_ONLY,
	LC_ARGUEMENT_TYPE_TEXT,
	LC_ARGUEMENT_TYPE_NUMBER,
	LC_ARGUEMENT_TYPE_BOOLEAN,
	LC_ARGUEMENT_TYPE_COUNT,
};

typedef struct lc_argument_tag_t lc_argument_t;
typedef int32_t(*lc_argument_callback_t)(o_stringview_t value, lc_parse_data_t* parse_data);

struct lc_argument_tag_t
{
	const char* m_command;
	const lc_argument_callback_t m_callback;
	int32_t m_type;
};

int32_t lc_argument_version(o_stringview_t value, lc_parse_data_t* parse_data);
int32_t lc_argument_help(o_stringview_t value, lc_parse_data_t* parse_data);
int32_t lc_argument_output(o_stringview_t value, lc_parse_data_t* parse_data);
int32_t lc_argument_directory(o_stringview_t value, lc_parse_data_t* parse_data);

static const lc_argument_t lc_arguments[] =
{
	{ "--help", lc_argument_help, LC_ARGUEMENT_TYPE_SINGLE_COMMAND_ONLY },
	{ "-h", lc_argument_help, LC_ARGUEMENT_TYPE_SINGLE_COMMAND_ONLY },
	{ "--version", lc_argument_version, LC_ARGUEMENT_TYPE_SINGLE_COMMAND_ONLY },
	{ "-v", lc_argument_version, LC_ARGUEMENT_TYPE_SINGLE_COMMAND_ONLY },
	{ "--output", lc_argument_output, LC_ARGUEMENT_TYPE_TEXT },
	{ "-o", lc_argument_output, LC_ARGUEMENT_TYPE_TEXT },
	{ "--directory", lc_argument_directory, LC_ARGUEMENT_TYPE_TEXT },
	{ "-d", lc_argument_directory, LC_ARGUEMENT_TYPE_TEXT },
};

int32_t lc_parse_command_line_arguments(int32_t argc, const char** argv, lc_parse_data_t* parse_data)
{
	int32_t result = 0;

	if (argc <= 0 || NULL == argv)
	{
		fprintf(stderr, "Invalid command line arguments\n");
		return -1;
	}

	while (argc > 0)
	{
		o_stringview_t view = ogle_stringview_cstr(argv[0]);

		for (size_t j = 0; j < sizeof(lc_arguments) / sizeof(lc_arguments[0]); j++)
		{
			const lc_argument_t* argument = &lc_arguments[j];
			o_stringview_t command_view = ogle_stringview_cstr(argument->m_command);

			if (ogle_stringview_equals(view, command_view))
			{
				if (argument->m_type == LC_ARGUEMENT_TYPE_SINGLE_COMMAND_ONLY)
				{
					result = argument->m_callback(ogle_stringview_empty(), parse_data);
				}
				else if (argument->m_type == LC_ARGUEMENT_TYPE_TEXT)
				{
					if (argc < 2)
					{
						return -1;
					}
					o_stringview_t value_view = ogle_stringview_cstr(argv[1]);
					result = argument->m_callback(value_view, parse_data);
					--argc;
					++argv;
				}
				else
				{
					fprintf(stderr, "Unknown argument type for command: %s\n", argument->m_command);
					return -1;
				}

				if (0 != result)
				{
					return result;
				}
			}
		}

		--argc;
		++argv;
	}

	return 0;
}

int32_t lc_argument_help(o_stringview_t value, lc_parse_data_t* parse_data)
{
	LC_UNUSED(value);
	LC_UNUSED(parse_data);

	LC_LOG_INFO("Usage: %s [options] <file>", parse_data->m_executable_name);
	LC_LOG_INFO("Options:");
	LC_LOG_INFO("\t-h, --help      Show this help message");
	LC_LOG_INFO("\t-v, --version   Show version information");
	LC_LOG_INFO("\t-o, --output     Specify output file (uses as prefix)");
	LC_LOG_INFO("\t-d, --directory  Specify output directory");
	
	return 1;
}

int32_t lc_argument_version(o_stringview_t value, lc_parse_data_t* parse_data)
{
	LC_UNUSED(value);
	LC_UNUSED(parse_data);

	fprintf(stderr, "%s\n", LC_STRING_APP_NAME);
	fprintf(stderr, "Version: %s\n", LC_STRING_VERSION);

	return 1;
}

int32_t lc_argument_output(o_stringview_t value, lc_parse_data_t* parse_data)
{
	if (ogle_stringview_is_empty(value) || NULL == parse_data)
	{
		return -1;
	}

	if (!lc_utils_is_valid_identifier(value))
	{
		LC_LOG_INFO("Invalid output filename: %.*s", (int32_t)value.m_length, value.m_data);
		return -1;
	}

	strcpy_s(parse_data->m_prefix, sizeof(parse_data->m_prefix), value.m_data);

	return 0;
}

int32_t lc_argument_directory(o_stringview_t value, lc_parse_data_t* parse_data)
{
	if (ogle_stringview_is_empty(value) || NULL == parse_data)
	{
		return -1;
	}

	char buffer[512] = { 0 };
	sprintf_s(buffer, sizeof(buffer), ".%c%.*s", ALLEGRO_NATIVE_PATH_SEP, (int32_t)value.m_length, value.m_data);

	memcpy(parse_data->m_directory, buffer, strlen(buffer) + 1);

	return 0;
}
