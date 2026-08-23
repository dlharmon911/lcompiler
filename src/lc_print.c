#include "lc_common.h"

void lc_print_string(ALLEGRO_FILE* file, const char* string, int32_t(*func)(int32_t))
{
	if (NULL == file)
	{
		return;
	}

	if (NULL == string)
	{
		return;
	}

	if (NULL == func)
	{
		return;
	}

	o_stringview_t view = ogle_stringview_cstr(string);

	lc_print_stringview(file, view, func);
}

void lc_print_stringview(ALLEGRO_FILE* file, o_stringview_t view, int32_t(*func)(int32_t))
{
	if (NULL == file)
	{
		return;
	}

	if (ogle_stringview_is_empty(view))
	{
		return;
	}

	if (NULL == func)
	{
		return;
	}

	while (view.m_length)
	{
		al_fputc(file, func(*view.m_data));

		++view.m_data;
		--view.m_length;
	}
}