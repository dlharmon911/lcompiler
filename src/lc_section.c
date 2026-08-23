#include "lc_common.h"

void lc_section_zero(lc_section_t* section)
{
	if (NULL == section)
	{
		return;
	}

	section->m_defines = NULL;
	section->m_display_options = NULL;
	section->m_display_flags = 0;
	section->m_addon_flags = 0;
	section->m_input_flags = 0;
}

void lc_section_clear(lc_section_t* section)
{
	if (NULL == section)
	{
		return;
	}

	if (section->m_defines)
	{
		ogle_darray_destroy(&section->m_defines);
	}

	if (section->m_display_options)
	{
		ogle_darray_destroy(&section->m_display_options);
	}

	lc_section_zero(section);
}

bool lc_section_add_define(lc_section_t* section, const lc_define_t* define)
{
	if (NULL == section || NULL == define)
	{
		return false;
	}

	if (NULL == section->m_defines && 
		NULL == (section->m_defines = (lc_define_t*)ogle_darray_create(sizeof(lc_define_t))))
	{
		return false;
	}

	return ogle_darray_push_back(&section->m_defines, define);
}

bool lc_section_add_display_option(lc_section_t* section, const lc_display_option_t* display_option)
{
	if (NULL == section || NULL == display_option)
	{
		return false;
	}
	if (NULL == section->m_display_options && NULL == (section->m_display_options = (lc_display_option_t*)ogle_darray_create(sizeof(lc_display_option_t))))
	{
		return false;
	}

	return ogle_darray_push_back(&section->m_display_options, display_option);
}

bool lc_section_add_display_option_value(lc_section_t* section, int32_t id, int32_t importance, int32_t value)
{
	if (NULL == section)
	{
		return false;
	}

	lc_display_option_t display_option = { id, importance, value };

	return lc_section_add_display_option(section, &display_option);
}
