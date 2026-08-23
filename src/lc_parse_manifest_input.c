#include "lc_common.h"

#define LC_PARSE_MANIFEST_INPUT_ATTRIBUTE_TYPE "type"

const lc_parse_context_attribute_t lc_parse_manifest_input_element_attributes[] =
{
	{	.m_name = LC_PARSE_MANIFEST_INPUT_ATTRIBUTE_TYPE, 
		.m_parse_function = lc_parse_manifest_input_element_attribute,
		.m_prefix = {.m_data = NULL, .m_length = 0} }
};

int32_t lc_parse_manifest_input_element_attribute(lc_parse_data_t* data, o_stringview_t prefix, const xml_attribute_t* attribute)
{
	if (NULL == data || NULL == attribute)
	{
		return -1;
	}

	o_stringview_t name = xml_attribute_get_name(attribute);
	o_stringview_t value = xml_attribute_get_value(attribute);

	if (!ogle_stringview_equals_cstr(name, LC_PARSE_MANIFEST_INPUT_ATTRIBUTE_TYPE))
	{
		return -1;
	}

	int32_t input_flag = lc_input_flag_parse(value);

	if (input_flag < 0)
	{
		return -1;
	}

	data->m_section.m_input_flags = input_flag;

	return 0;
}


int32_t lc_parse_manifest_element_input(lc_parse_data_t* data, const xml_element_t* xml_element)
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
		lc_parse_manifest_input_element_attributes,
		sizeof(lc_parse_manifest_input_element_attributes) / sizeof(lc_parse_manifest_input_element_attributes[0]));
}
