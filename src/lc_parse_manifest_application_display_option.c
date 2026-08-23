#include "lc_common.h"

const lc_parse_context_attribute_t g_display_option_parse_attributes[] =
{
	{.m_name = "type",
	.m_parse_function = lc_parse_display_option_type,
	.m_prefix = {.m_data = LC_STRING_DISPLAY, .m_length = sizeof(LC_STRING_DISPLAY) - 1}
	},
	{ .m_name = "value",
	.m_parse_function = lc_parse_display_option_value,
	.m_prefix = {.m_data = LC_STRING_DISPLAY, .m_length = sizeof(LC_STRING_DISPLAY) - 1}
	},
	{.m_name = "importance",
	.m_parse_function = lc_parse_display_option_importance,
	.m_prefix = {.m_data = LC_STRING_DISPLAY, .m_length = sizeof(LC_STRING_DISPLAY) - 1}
	}
};

int32_t lc_parse_display_option(lc_parse_data_t* data, const xml_element_t* xml_element)
{
	int32_t result = 0;
	if (NULL == data || NULL == xml_element)
	{
		return -1;
	}

	lc_display_option_t option = { 0 };

	data->m_user_data = &option;

	result = lc_parse_element_context(
		data,
		xml_element,
		NULL,
		0,
		g_display_option_parse_attributes,
		sizeof(g_display_option_parse_attributes) / sizeof(g_display_option_parse_attributes[0])
	);

	data->m_user_data = NULL;

	if (result < 0)
	{
		return -1;
	}

	if (!lc_section_add_display_option(&data->m_section, &option))
	{
		return -1;
	}

	return result;
}

int32_t lc_parse_display_option_type(lc_parse_data_t* data, o_stringview_t prefix, const xml_attribute_t* xml_attribute)
{
	if (NULL == data || NULL == xml_attribute)
	{
		return -1;
	}

	o_stringview_t value = xml_attribute_get_value(xml_attribute);

	lc_display_option_t* option = (lc_display_option_t*)data->m_user_data;

	option->m_type = lc_display_option_type_parse(value);
	
	if (option->m_type < 0)
	{
		return -1;
	}

	return 0;
}

int32_t lc_parse_display_option_value(lc_parse_data_t* data, o_stringview_t prefix, const xml_attribute_t* xml_attribute)
{
	if (NULL == data || NULL == xml_attribute)
	{
		return -1;
	}
	o_stringview_t value = xml_attribute_get_value(xml_attribute);
	lc_display_option_t* option = (lc_display_option_t*)data->m_user_data;
	int32_t int_value = 0;
	if (sscanf_s(value.m_data, "%d", &int_value) != 1)
	{
		return -1;
	}
	option->m_value = int_value;
	return 0;
}

int32_t lc_parse_display_option_importance(lc_parse_data_t* data, o_stringview_t prefix, const xml_attribute_t* xml_attribute)
{
	if (NULL == data || NULL == xml_attribute)
	{
		return -1;
	}

	o_stringview_t value = xml_attribute_get_value(xml_attribute);

	lc_display_option_t* option = (lc_display_option_t*)data->m_user_data;

	option->m_importance = lc_display_option_importance_parse(value);

	if (option->m_importance < 0)
	{
		return -1;
	}

	return 0;
}