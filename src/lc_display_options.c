#include "lc_common.h"

enum DISPLAY_OPTION_IDS
{
	DISPLAY_OPTION_ID_RED_SIZE,
	DISPLAY_OPTION_ID_GREEN_SIZE,
	DISPLAY_OPTION_ID_BLUE_SIZE,
	DISPLAY_OPTION_ID_ALPHA_SIZE,
	DISPLAY_OPTION_ID_COLOR_SIZE,
	DISPLAY_OPTION_ID_RED_SHIFT,
	DISPLAY_OPTION_ID_GREEN_SHIFT,
	DISPLAY_OPTION_ID_BLUE_SHIFT,
	DISPLAY_OPTION_ID_ALPHA_SHIFT,
	DISPLAY_OPTION_ID_ACC_RED_SIZE,
	DISPLAY_OPTION_ID_ACC_GREEN_SIZE,
	DISPLAY_OPTION_ID_ACC_BLUE_SIZE,
	DISPLAY_OPTION_ID_ACC_ALPHA_SIZE,
	DISPLAY_OPTION_ID_STEREO,
	DISPLAY_OPTION_ID_AUX_BUFFERS,
	DISPLAY_OPTION_ID_DEPTH_SIZE,
	DISPLAY_OPTION_ID_STENCIL_SIZE,
	DISPLAY_OPTION_ID_SAMPLE_BUFFERS,
	DISPLAY_OPTION_ID_SAMPLES,
	DISPLAY_OPTION_ID_RENDER_METHOD,
	DISPLAY_OPTION_ID_FLOAT_COLOR,
	DISPLAY_OPTION_ID_FLOAT_DEPTH,
	DISPLAY_OPTION_ID_SINGLE_BUFFER,
	DISPLAY_OPTION_ID_SWAP_METHOD,
	DISPLAY_OPTION_ID_COMPATIBLE_DISPLAY,
	DISPLAY_OPTION_ID_UPDATE_DISPLAY_REGION,
	DISPLAY_OPTION_ID_VSYNC,
	DISPLAY_OPTION_ID_MAX_BITMAP_SIZE,
	DISPLAY_OPTION_ID_SUPPORT_NPOT_BITMAP,
	DISPLAY_OPTION_ID_CAN_DRAW_INTO_BITMAP,
	DISPLAY_OPTION_ID_SUPPORT_SEPARATE_ALPHA,
	DISPLAY_OPTION_ID_COUNT
};

enum DISPLAY_OPTION_IMPORTANCE
{
	DISPLAY_OPTION_IMPORTANCE_REQUIRE,
	DISPLAY_OPTION_IMPORTANCE_SUGGEST,
	DISPLAY_OPTION_IMPORTANCE_DONTCARE,
	DISPLAY_OPTION_IMPORTANCE_COUNT
};

static const lc_string_int_pair_t DISPLAY_OPTION_NAMES[DISPLAY_OPTION_ID_COUNT] =
{
	{ "red_size", ALLEGRO_RED_SIZE },
	{ "green_size", ALLEGRO_GREEN_SIZE },
	{ "blue_size", ALLEGRO_BLUE_SIZE },
	{ "alpha_size", ALLEGRO_ALPHA_SIZE },
	{ "color_size", ALLEGRO_COLOR_SIZE },
	{ "red_shift", ALLEGRO_RED_SHIFT },
	{ "green_shift", ALLEGRO_GREEN_SHIFT },
	{ "blue_shift", ALLEGRO_BLUE_SHIFT },
	{ "alpha_shift", ALLEGRO_ALPHA_SHIFT },
	{ "acc_red_size", ALLEGRO_ACC_RED_SIZE },
	{ "acc_green_size", ALLEGRO_ACC_GREEN_SIZE },
	{ "acc_blue_size", ALLEGRO_ACC_BLUE_SIZE },
	{ "acc_alpha_size", ALLEGRO_ACC_ALPHA_SIZE },
	{ "stereo", ALLEGRO_STEREO },
	{ "aux_buffers", ALLEGRO_AUX_BUFFERS },
	{ "depth_size", ALLEGRO_DEPTH_SIZE },
	{ "stencil_size", ALLEGRO_STENCIL_SIZE },
	{ "sample_buffers", ALLEGRO_SAMPLE_BUFFERS },
	{ "samples", ALLEGRO_SAMPLES },
	{ "render_method", ALLEGRO_RENDER_METHOD },
	{ "float_color", ALLEGRO_FLOAT_COLOR },
	{ "float_depth", ALLEGRO_FLOAT_DEPTH },
	{ "single_buffer", ALLEGRO_SINGLE_BUFFER },
	{ "swap_method", ALLEGRO_SWAP_METHOD },
	{ "compatible_display", ALLEGRO_COMPATIBLE_DISPLAY },
	{ "update_display_region", ALLEGRO_UPDATE_DISPLAY_REGION },
	{ "vsync", ALLEGRO_VSYNC },
	{ "max_bitmap_size", ALLEGRO_MAX_BITMAP_SIZE },
	{ "support_npot_bitmap", ALLEGRO_SUPPORT_NPOT_BITMAP },
	{ "can_draw_into_bitmap", ALLEGRO_CAN_DRAW_INTO_BITMAP },
	{ "support_separate_alpha", ALLEGRO_SUPPORT_SEPARATE_ALPHA }
};

static const lc_string_int_pair_t DISPLAY_OPTION_IMPORTANCE_NAMES[DISPLAY_OPTION_IMPORTANCE_COUNT] =
{
	{ "require", ALLEGRO_REQUIRE },
	{ "suggest", ALLEGRO_SUGGEST },
	{ "dontcare", ALLEGRO_DONTCARE }
};

int32_t lc_display_option_type_parse(o_stringview_t view)
{
	for (size_t i = 0; i < DISPLAY_OPTION_ID_COUNT; i++)
	{
		if (ogle_stringview_equals_cstr(view, DISPLAY_OPTION_NAMES[i].m_string))
		{
			return DISPLAY_OPTION_NAMES[i].m_value;
		}
	}

	return -1;
}


int32_t lc_display_option_importance_parse(o_stringview_t view)
{
	for (size_t i = 0; i < DISPLAY_OPTION_IMPORTANCE_COUNT; i++)
	{
		if (ogle_stringview_equals_cstr(view, DISPLAY_OPTION_IMPORTANCE_NAMES[i].m_string))
		{
			return DISPLAY_OPTION_IMPORTANCE_NAMES[i].m_value;
		}
	}

	return -1;
}

const char* lc_display_option_type_name(int32_t type)
{
	for (size_t i = 0; i < DISPLAY_OPTION_ID_COUNT; i++)
	{
		if (DISPLAY_OPTION_NAMES[i].m_value == type)
		{
			return DISPLAY_OPTION_NAMES[i].m_string;
		}
	}

	return NULL;
}

const char* lc_display_option_importance_name(int32_t importance)
{
	for (size_t i = 0; i < DISPLAY_OPTION_IMPORTANCE_COUNT; i++)
	{
		if (DISPLAY_OPTION_IMPORTANCE_NAMES[i].m_value == importance)
		{
			return DISPLAY_OPTION_IMPORTANCE_NAMES[i].m_string;
		}
	}

	return NULL;
}