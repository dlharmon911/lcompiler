#include "lc_common.h"

const lc_parse_context_element_t g_manifest_application_parse_contexts[] =
{
	{ LC_STRING_DISPLAY, lc_parse_manifest_element_application_display },
	{ LC_STRING_TIMER, lc_parse_manifest_element_application_timer }
};

const lc_parse_context_attribute_t g_manifest_application_parse_attributes[] =
{
	{	.m_name = LC_STRING_TITLE, 
		.m_parse_function = lc_parse_attribute_define_string,
		.m_prefix = {.m_data = NULL, .m_length = 0} }
};

int32_t lc_parse_manifest_element_application(lc_parse_data_t* data, const xml_element_t* xml_element)
{
	if (NULL == data || NULL == xml_element)
	{
		return -1;
	}

	if (xml_element_has_attributes(xml_element))
	{
		const xml_attribute_t* attributes = xml_element_get_attribute_const(xml_element, 0);

		if (NULL == attributes)
		{
			return -1;
		}

		if (lc_parse_attributes_context(data, attributes, g_manifest_application_parse_attributes, sizeof(g_manifest_application_parse_attributes) / sizeof(g_manifest_application_parse_attributes[0])) < 0)
		{
			return -1;
		}
	}

	if (!xml_element_has_children(xml_element))
	{
		return 0;
	}

	const xml_child_t* children = xml_element_get_child_const(xml_element, 0);

	if (NULL == children)
	{
		return -1;
	}

	if (lc_parse_children_context(data, children, g_manifest_application_parse_contexts, sizeof(g_manifest_application_parse_contexts) / sizeof(g_manifest_application_parse_contexts[0])) < 0)
	{
		return -1;
	}

	return 0;
}
