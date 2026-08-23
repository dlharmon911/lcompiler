#include "lc_common.h"

enum LC_ADDON_FLAGS
{
	LC_ADDON_FLAG_NONE = 0X0000,
	LC_ADDON_FLAG_AUDIO = 0X0001,
	LC_ADDON_FLAG_ACODEC = 0X0002,
	LC_ADDON_FLAG_COLOR = 0X0004,
	LC_ADDON_FLAG_FONT = 0X0008,
	LC_ADDON_FLAG_IMAGE = 0X0010,
	LC_ADDON_FLAG_MEMFILE = 0X0020,
	LC_ADDON_FLAG_NATIVEDIALOG = 0X0040,
	LC_ADDON_FLAG_PHYSFS = 0X0080,
	LC_ADDON_FLAG_PRIMITIVES = 0X0100,
	LC_ADDON_FLAG_TTF = 0X0200
};

static const lc_string_int_pair_t LC_ADDON_FLAG_NAMES[LC_ADDON_FLAG_ID_COUNT] =
{
	{ "audio", LC_ADDON_FLAG_AUDIO },
	{ "acodec", LC_ADDON_FLAG_ACODEC },
	{ "color", LC_ADDON_FLAG_COLOR },
	{ "font", LC_ADDON_FLAG_FONT },
	{ "image", LC_ADDON_FLAG_IMAGE },
	{ "memfile", LC_ADDON_FLAG_MEMFILE },
	{ "dialog", LC_ADDON_FLAG_NATIVEDIALOG },
	{ "physfs", LC_ADDON_FLAG_PHYSFS },
	{ "primitives", LC_ADDON_FLAG_PRIMITIVES },
	{ "ttf", LC_ADDON_FLAG_TTF }
};

int32_t lc_addon_flag_parse(o_stringview_t view)
{
	return lc_pair_array_flag_parse(LC_ADDON_FLAG_NAMES, LC_ADDON_FLAG_ID_COUNT, view, '|');
}

const char* lc_addon_flag_name(int32_t flag)
{
	for (size_t i = 0; i < LC_ADDON_FLAG_ID_COUNT; i++)
	{
		if (LC_ADDON_FLAG_NAMES[i].m_value == flag)
		{
			return LC_ADDON_FLAG_NAMES[i].m_string;
		}
	}

	return NULL;
}