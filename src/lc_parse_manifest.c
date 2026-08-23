#include "lc_common.h"

#define LC_STRING_MANIFEST_ELEMENT_ADDON "addon"
#define LC_STRING_MANIFEST_ELEMENT_INPUT "input"
#define LC_STRING_MANIFEST_ELEMENT_APPLICATION "application"
#define LC_STRING_MANIFEST_ATTRIBUTE_VERSION "version"

const lc_parse_context_element_t g_manifest_parse_contexts[] =
{
	{ LC_STRING_MANIFEST_ELEMENT_ADDON, lc_parse_manifest_element_addon},
	{ LC_STRING_MANIFEST_ELEMENT_INPUT, lc_parse_manifest_element_input },
	{ LC_STRING_MANIFEST_ELEMENT_APPLICATION, lc_parse_manifest_element_application }
};

const lc_parse_context_attribute_t g_manifest_parse_attributes[] =
{
	{	.m_name = LC_STRING_MANIFEST_ATTRIBUTE_VERSION, 
		.m_parse_function = lc_parse_attribute_define_value,
		.m_prefix = {.m_data = NULL, .m_length = 0} }
};

int32_t lc_parse_manifest(lc_parse_data_t* data, const xml_element_t* xml_element)
{
	if (NULL == data || NULL == xml_element)
	{
		return -1;
	}

	return lc_parse_element_context(
		data, 
		xml_element, 
		g_manifest_parse_contexts, 
		sizeof(g_manifest_parse_contexts) / sizeof(g_manifest_parse_contexts[0]), 
		g_manifest_parse_attributes, 
		sizeof(g_manifest_parse_attributes) / sizeof(g_manifest_parse_attributes[0]));
}
