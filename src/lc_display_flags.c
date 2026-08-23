#include "lc_common.h"

static const lc_string_int_pair_t DISPLAY_FLAG_NAMES[LC_DISPLAY_FLAG_ID_COUNT] =
{
	{ "windowed", ALLEGRO_WINDOWED },
	{ "fullscreen", ALLEGRO_FULLSCREEN },
	{ "opengl", ALLEGRO_OPENGL },
	{ "direct3d_internal", ALLEGRO_DIRECT3D_INTERNAL },
	{ "resizable", ALLEGRO_RESIZABLE },
	{ "frameless", ALLEGRO_FRAMELESS },
	{ "noframe", ALLEGRO_NOFRAME },
	{ "expose_events", ALLEGRO_GENERATE_EXPOSE_EVENTS },
	{ "opengl_3_0", ALLEGRO_OPENGL_3_0 },
	{ "opengl_forward_compatible", ALLEGRO_OPENGL_FORWARD_COMPATIBLE },
	{ "fullscreen_window", ALLEGRO_FULLSCREEN_WINDOW },
	{ "minimized", ALLEGRO_MINIMIZED }, 
	{ "programmable_pipeline", ALLEGRO_PROGRAMMABLE_PIPELINE },
	{ "gtk_toplevel_internal", ALLEGRO_GTK_TOPLEVEL_INTERNAL },
	{ "maximized", ALLEGRO_MAXIMIZED },
	{ "opengl_es_profile", ALLEGRO_OPENGL_ES_PROFILE },
#if defined(ALLEGRO_UNSTABLE) || defined(ALLEGRO_INTERNAL_UNSTABLE) || defined(ALLEGRO_SRC)
	{ "opengl_core_profile", ALLEGRO_OPENGL_CORE_PROFILE },
	{ "drag_and_drop", ALLEGRO_DRAG_AND_DROP },
#endif
};

int32_t lc_display_flag_parse(o_stringview_t view)
{
	return lc_pair_array_flag_parse(DISPLAY_FLAG_NAMES, LC_DISPLAY_FLAG_ID_COUNT, view, '|');
}

const char* lc_display_flag_name(int32_t flag)
{
	for (size_t i = 0; i < LC_DISPLAY_FLAG_ID_COUNT; i++)
	{
		if (DISPLAY_FLAG_NAMES[i].m_value == flag)
		{
			return DISPLAY_FLAG_NAMES[i].m_string;
		}
	}

	return NULL;
}
