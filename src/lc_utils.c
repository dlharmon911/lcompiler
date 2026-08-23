#include "lc_common.h"

static bool lc_utils_is_identifier_char(int32_t c)
{
	return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || (c == '_');
}

bool lc_utils_is_valid_identifier(o_stringview_t view)
{
	if (ogle_stringview_is_empty(view))
	{
		return false;
	}
	
	for (size_t i = 0; i < view.m_length; i++)
	{
		if (!lc_utils_is_identifier_char(view.m_data[i]))
		{
			return false;
		}
	}

	return true;
}

int32_t lc_char_upper(int32_t c)
{
	if (c >= 'a' && c <= 'z')
	{
		c = c + 'A' - 'a';
	}

	return c;
}

int32_t lc_char_lower(int32_t c)
{
	if (c >= 'A' && c <= 'Z')
	{
		c = c - 'A' + 'a';
	}

	return c;
}

int32_t lc_timestamp(char* buffer, size_t buffer_size, const char* format)
{
	time_t now = time(NULL);
	struct tm local_time;
	localtime_s(&local_time, &now);
	strftime(buffer, buffer_size, format, &local_time);
	return 0;
}

const char* lc_string_upper(const char* str)
{
	static char buffer[256];
	size_t length = strlen(str);
	if (length >= sizeof(buffer))
	{
		length = sizeof(buffer) - 1;
	}
	for (size_t i = 0; i < length; i++)
	{
		buffer[i] = lc_char_upper(str[i]);
	}
	buffer[length] = '\0';
	return buffer;
}

void lc_capitalize_string(char* str, size_t size)
{
	if (NULL == str || size == 0)
	{
		return;
	}

	for (size_t i = 0; i < size && str[i] != '\0'; i++)
	{
		str[i] = lc_char_upper(str[i]);
	}
}
