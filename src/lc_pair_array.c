#include "lc_common.h"

int32_t lc_pair_array_flag_parse(const lc_string_int_pair_t* pair_array, size_t count, o_stringview_t view, char delimiter)
{
	if (ogle_stringview_is_empty(view))
	{
		return -1;
	}

	int32_t result = 0;

	while (view.m_length > 0)
	{
		o_stringview_t token = { 0 };
		bool found = false;

		view = ogle_stringview_tokenize(view, delimiter, &token);

		if (ogle_stringview_is_empty(token))
		{
			return -1;
		}

		for (size_t i = 0; i < count; ++i)
		{
			if (ogle_stringview_equals_cstr(token, pair_array[i].m_string))
			{
				result |= pair_array[i].m_value;
				found = true;
				break;
			}
		}

		if (!found)
		{
			return -1;
		}
	}

	return result;
}
