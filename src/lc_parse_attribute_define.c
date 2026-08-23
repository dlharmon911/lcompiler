#include "lc_common.h"

int32_t lc_parse_attribute_define_value(lc_parse_data_t* data, o_stringview_t prefix, const xml_attribute_t* xml_attribute)
{
	if (NULL == data || NULL == xml_attribute)
	{
		return -1;
	}

	lc_define_t define =
	{
		.m_prefix = prefix,
		.m_type = LC_DEFINE_TYPE_VALUE,
		.m_name = xml_attribute_get_name(xml_attribute),
		.m_value = xml_attribute_get_value(xml_attribute)
	};

	if (lc_section_add_define(&data->m_section, &define) < 0)
	{
		return -1;
	}

	return 0;
}

int32_t lc_parse_attribute_define_string(lc_parse_data_t* data, o_stringview_t prefix, const xml_attribute_t* xml_attribute)
{
	if (NULL == data || NULL == xml_attribute)
	{
		return -1;
	}

	lc_define_t define =
	{
		.m_prefix = prefix,
		.m_type = LC_DEFINE_TYPE_STRING,
		.m_name = xml_attribute_get_name(xml_attribute),
		.m_value = xml_attribute_get_value(xml_attribute)
	};

	if (lc_section_add_define(&data->m_section, &define) < 0)
	{
		return -1;
	}

	return 0;
}