#include "lc_common.h"

const lc_parse_context_attribute_t g_display_parse_attributes[] =
{
	{ .m_name = "width",
		.m_parse_function = lc_parse_attribute_define_value,
		.m_prefix = {.m_data = LC_STRING_DISPLAY, .m_length = sizeof(LC_STRING_DISPLAY) - 1} },
	{.m_name = "height",
		.m_parse_function = lc_parse_attribute_define_value,
		.m_prefix = {.m_data = LC_STRING_DISPLAY, .m_length = sizeof(LC_STRING_DISPLAY) - 1} },
		{.m_name = "flags",
		.m_parse_function = lc_parse_display_flags,
		.m_prefix = {.m_data = LC_STRING_DISPLAY, .m_length = sizeof(LC_STRING_DISPLAY) - 1} }
};

const lc_parse_context_element_t g_display_parse_elements[] =
{
	{.m_name = "option", .m_parse_function = lc_parse_display_option }
};

int32_t lc_parse_manifest_element_application_display(lc_parse_data_t* data, const xml_element_t* xml_element)
{
	if (NULL == data || NULL == xml_element)
	{
		return -1;
	}

	return lc_parse_element_context(
		data,
		xml_element,
		g_display_parse_elements,
		sizeof(g_display_parse_elements) / sizeof(g_display_parse_elements[0]),
		g_display_parse_attributes,
		sizeof(g_display_parse_attributes) / sizeof(g_display_parse_attributes[0])
	);
}
