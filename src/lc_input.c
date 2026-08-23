#include "lc_common.h"

enum LC_INPUT_FLAGS
{
	LC_INPUT_FLAG_NONE = 0X0000,
	LC_INPUT_FLAG_KEYBOARD = 0X0001,
	LC_INPUT_FLAG_MOUSE = 0X0002,
	LC_INPUT_FLAG_JOYSTICK = 0X0004
};

static const lc_string_int_pair_t LC_INPUT_FLAG_NAMES[LC_INPUT_FLAG_ID_COUNT] =
{
	{ "keyboard", LC_INPUT_FLAG_KEYBOARD },
	{ "mouse", LC_INPUT_FLAG_MOUSE },
	{ "joystick", LC_INPUT_FLAG_JOYSTICK }		
};

int32_t lc_input_flag_parse(o_stringview_t view)
{
	return lc_pair_array_flag_parse(LC_INPUT_FLAG_NAMES, LC_INPUT_FLAG_ID_COUNT, view, '|');
}

const char* lc_input_flag_name(int32_t flag)
{
	for (size_t i = 0; i < LC_INPUT_FLAG_ID_COUNT; i++)
	{
		if (LC_INPUT_FLAG_NAMES[i].m_value == flag)
		{
			return LC_INPUT_FLAG_NAMES[i].m_string;
		}
	}

	return NULL;
}
