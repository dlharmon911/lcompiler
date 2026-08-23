#include "lc_common.h"

const lc_parse_context_attribute_t g_timer_parse_attributes[] =
{
	{
		.m_name = "speed",
		.m_parse_function = lc_parse_attribute_define_value,
		.m_prefix = {.m_data = LC_STRING_TIMER, .m_length = sizeof(LC_STRING_TIMER) - 1}
	}
};

int32_t lc_parse_manifest_element_application_timer(lc_parse_data_t* data, const xml_element_t* xml_element)
{
	if (NULL == data || NULL == xml_element)
	{
		return -1;
	}

	return lc_parse_element_context(
		data,
		xml_element,
		NULL,
		0,
		g_timer_parse_attributes,
		sizeof(g_timer_parse_attributes) / sizeof(g_timer_parse_attributes[0])
	);
}
