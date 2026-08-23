#include "lc_common.h"

int32_t lc_parse_attribute_context(lc_parse_data_t* data, const xml_attribute_t* attribute, const lc_parse_context_attribute_t* context, size_t size)
{
	if (NULL == data || NULL == attribute || NULL == context)
	{
		return -1;
	}

	o_stringview_t name = xml_attribute_get_name(attribute);

	for (size_t i = 0; i < size; ++i)
	{
		const lc_parse_context_attribute_t* ctx = &context[i];
		if (ogle_stringview_equals_cstr(name, ctx->m_name))
		{
			return ctx->m_parse_function(data, ctx->m_prefix, attribute);
		}
	}

	return -1;
}

int32_t lc_parse_attributes_context(lc_parse_data_t* data, const xml_attribute_t* attributes, const lc_parse_context_attribute_t* context, size_t size)
{
	if (NULL == data)
	{
		return -1;
	}

	if (NULL == attributes)
	{
		return -1;
	}

	size_t count = ogle_darray_size(attributes);

	for (size_t i = 0; i < count; ++i)
	{
		const xml_attribute_t* attribute = ogle_darray_get_const(attributes, i);

		if (lc_parse_attribute_context(data, attribute, context, size) < 0)
		{
			return -1;
		}
	}

	return 0;
}

int32_t lc_parse_child_element_context(lc_parse_data_t* data, const xml_element_t* element, const lc_parse_context_element_t* context, size_t size)
{
	if (NULL == data || NULL == element || NULL == context)
	{
		return -1;
	}

	o_stringview_t name = xml_element_get_name(element);

	for (size_t i = 0; i < size; ++i)
	{
		const lc_parse_context_element_t* ctx = &context[i];
		if (ogle_stringview_equals_cstr(name, ctx->m_name))
		{
			return ctx->m_parse_function(data, element);
		}
	}

	return -1;
}

int32_t lc_parse_children_context(lc_parse_data_t* data, const xml_child_t* children, const lc_parse_context_element_t* context, size_t size)
{
	if (NULL == data || NULL == children)
	{
		return -1;
	}

	size_t count = ogle_darray_size(children);

	for (size_t i = 0; i < count; ++i)
	{
		const xml_child_t* child = ogle_darray_get_const(children, i);
		if (NULL == child)
		{
			return -1;
		}

		if (xml_child_get_type(child) != XML_ELEMENT_CHILD_TYPE_ELEMENT)
		{
			continue;
		}

		const xml_element_t* element = xml_child_get_element_const(child);

		if (NULL == element)
		{
			return -1;
		}

		if (lc_parse_child_element_context(data, element, context, size) < 0)
		{
			return -1;
		}
	}

	return 0;
}

int32_t lc_parse_element_context(lc_parse_data_t* data, const xml_element_t* element, const lc_parse_context_element_t* element_context, size_t element_size, const lc_parse_context_attribute_t* attribute_context, size_t attribute_size)
{
	if (NULL == data || NULL == element)
	{
		return -1;
	}


	if (attribute_context && xml_element_has_attributes(element))
	{
		const xml_attribute_t* attributes = xml_element_get_attribute_const(element, 0);
		if (NULL == attributes)
		{
			return -1;
		}
		if (lc_parse_attributes_context(data, attributes, attribute_context, attribute_size) < 0)
		{
			return -1;
		}
	}
	
	if (element_context && xml_element_has_children(element))
	{
		const xml_child_t* children = xml_element_get_child_const(element, 0);

		if (NULL == children)
		{
			return -1;
		}

		if (lc_parse_children_context(data, children, element_context, element_size) < 0)
		{
			return -1;
		}
	}
	
	return 0;
}
