#include "lc_common.h"

int32_t lc_parse_display_flags(lc_parse_data_t* data, o_stringview_t prefix, const xml_attribute_t* xml_attribute)
{
	if (NULL == data || NULL == xml_attribute)
	{
		return -1;
	}

	o_stringview_t name = xml_attribute_get_name(xml_attribute);
	o_stringview_t value = xml_attribute_get_value(xml_attribute);

	int32_t display_flag = lc_display_flag_parse(value);

	if (display_flag < 0)
	{
		return -1;
	}

	data->m_section.m_display_flags = display_flag;

	return 0;
}
