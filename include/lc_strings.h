#ifndef _HEADER_GUARD_LCOMPILER_STRINGS_H_
#define _HEADER_GUARD_LCOMPILER_STRINGS_H_

#define LC_STRING_ALLEGRO		"allegro"
#define LC_STRING_ALLEGRO_UPPER "ALLEGRO"

#define LC_STRING_APP_NAME			"Manifest Layout Compiler"
#define LC_STRING_VERSION		"1.0.0"
#define LC_STRING_MANIFEST		"manifest"

#define LC_STRING_DEFAULT_PREFIX		"manifest"
#define LC_STRING_DEFAULT_DIRECTORY	"."
#define LC_STRING_DEFAULT_INPUT_FILE	"manifest.xml"

#define LC_STRING_TIMESTAMP_FORMAT	"%Y-%m-%d %H:%M:%S"
#define LC_STRING_TIMESTAMP		"/*\n" \
								" * File \"%s\" generated from compiled manifest\n." \
								" * %s\n" \
								" * Do not modify this file.\n" \
								" */\n\n"


#define LC_STRING_DATA_TYPEDEF	"typedef struct %s_data_tag_t %s_data_t;\n\n"

#define LC_STRING_DATA_STRUCT	"struct %s_data_tag_t\n" \
								"{\n" \
								"\tALLEGRO_DISPLAY* m_display;\n" \
								"\tALLEGRO_TIMER* m_timer;\n" \
								"\tALLEGRO_EVENT_QUEUE* m_event_queue;\n" \
								"};\n\n"
#define LC_STRING_HEADER_GUARD_START	"#ifndef _HEADER_GUARD_%s_DATA_H_\n" \
										"#define _HEADER_GUARD_%s_DATA_H_\n\n"
#define LC_STRING_HEADER_GUARD_END		"#endif // !_HEADER_GUARD_%s_DATA_H_\n\n"

#define LC_STRING_DECLARE_FUNCTION_INSTALL_ALLEGRO	"int32_t %s_install_allegro(void)"
#define LC_STRING_DECLARE_FUNCTION_UNINSTALL_ALLEGRO	"void %s_uninstall_allegro(void)"
#define LC_STRING_DECLARE_FUNCTION_ZERO_DATA	"void %s_zero_data(%s_data_t* data)"
#define LC_STRING_DECLARE_FUNCTION_INITIALIZE_DATA	"int32_t %s_initialize_data(%s_data_t* data)"
#define LC_STRING_DECLARE_FUNCTION_UNINITIALIZE_DATA	"void %s_uninitialize_data(%s_data_t* data)"

#define LC_STRING_ERROR "const char* %s_ERROR_STRING_FAILURE = \"Failed to %%s %%s.\";\n" \
"const char* %s_ERROR_STRING_NULL_POINTER = \"NULL pointer error: \\\"%%s\\\".\";\n\n"


#define LC_STRING_ALLEGRO_INIT 	"\tif (!al_init())\n" \
	"\t{\n" \
	"\t\tfprintf(stderr, %s_ERROR_STRING_FAILURE, \"initialize\", \"Allegro library\");\n" \
	"\t\treturn -1;\n" \
	"\t}\n\n"

#define LC_STRING_ALLEGRO_ADDON_INSTALL	"\tif (!al_install_%s())\n" \
	"\t{\n" \
	"\t\tfprintf(stderr, %s_ERROR_STRING_FAILURE, \"install\", \"%s\");\n" \
	"\t\treturn -1;\n" \
	"\t}\n\n"

#define LC_STRING_ALLEGRO_ADDON_INIT 	"\tif (!al_init_%s_addon())\n" \
	"\t{\n" \
	"\t\tfprintf(stderr, %s_ERROR_STRING_FAILURE, \"initialize\", \"%s\");\n" \
	"\t\treturn -1;\n" \
	"\t}\n\n"

#define LC_STRING_ALLEGRO_SHUTDOWN_ADDON 	"\tif (al_is_%s_addon_initialized())\n" \
	"\t{\n" \
	"\t\tal_shutdown_%s_addon();\n" \
	"\t}\n\n"

#define LC_STRING_ALLEGRO_SHUTDOWN_INSTALL 	"\tif (al_is_%s_installed())\n" \
	"\t{\n" \
	"\t\tal_uninstall_%s();\n" \
	"\t}\n\n"

#define LC_STRING_ALLEGRO_SHUTDOWN_SYSTEM 	"\tif (al_is_system_installed())\n" \
	"\t{\n" \
	"\t\tal_uninstall_system();\n" \
	"\t}\n"

#define LC_STRING_VERIFY_DATA	"\tif (NULL == %s)\n" \
	"\t{\n" \
	"\t\tfprintf(stderr, %s_ERROR_STRING_NULL_POINTER, \"%s\");\n" \
	"\t\treturn%s;\n" \
	"\t}\n\n"

#define LC_STRING_DISPLAY_CREATE "\tdata->m_display = al_create_display(%s_DISPLAY_WIDTH, %s_DISPLAY_HEIGHT);\n" \
	"\tif (NULL == data->m_display)\n" \
	"\t{\n" \
	"\t\tfprintf(stderr, %s_ERROR_STRING_FAILURE, \"create\", \"display\");\n" \
	"\t\treturn -1;\n" \
	"\t}\n\n"

#define LC_STRING_TIMER_CREATE "\tdata->m_timer = al_create_timer(1.0/%s_TIMER_SPEED);\n" \
	"\tif (NULL == data->m_timer)\n" \
	"\t{\n" \
	"\t\tfprintf(stderr, %s_ERROR_STRING_FAILURE, \"create\", \"timer\");\n" \
	"\t\treturn -1;\n" \
	"\t}\n\n"

#define LC_STRING_SET_DISPLAY_OPTION	"\tal_set_new_display_option(%s, %d, %s);\n"

#define LC_STRING_SET_WINDOW_TITLE "\tal_set_new_window_title(%s_TITLE);\n"
#define LC_STRING_DESTROY_OBJECT "\tif (NULL != data->m_%s)\n" \
	"\t{\n" \
	"\t\tal_destroy_%s(data->m_%s);\n" \
	"\t\tdata->m_%s = NULL;\n" \
	"\t}\n\n"

#define LC_STRING_EVENTQUEUE_CREATE "\tdata->m_event_queue = al_create_event_queue();\n" \
	"\tif (NULL == data->m_event_queue)\n" \
	"\t{\n" \
	"\t\tfprintf(stderr, %s_ERROR_STRING_FAILURE, \"create\", \"event queue\");\n" \
	"\t\treturn -1;\n" \
	"\t}\n\n"

#define LC_STRING_EVENTQUEUE_REGISTER_OBJECT "\tal_register_event_source(data->m_event_queue, al_get_%s_event_source(data->m_%s));\n"
#define LC_STRING_EVENTQUEUE_REGISTER_INPUT "\tal_register_event_source(data->m_event_queue, al_get_%s_event_source());\n"

#define LC_STRING_ZERO_OBJECT	"\tdata->m_%s = NULL;\n"

#define LC_STRING_COMMENT_INSTALL_ALLEGRO	"/// <summary>\n" \
	"/// Installs the Allegro library, Allegro addons and input devices.\n" \
	"/// </summary>\n" \
	"/// <param name=\"N/A\"></param>\n" \
	"/// <returns>Result of the installation (0 for success, -1 for failure)</returns>\n"

#define LC_STRING_COMMENT_UNINSTALL_ALLEGRO	"/// <summary>\n" \
	"/// Uninstalls the Allegro library, Allegro addons and input devices.\n" \
	"/// </summary>\n" \
	"/// <param name=\"N/A\"></param>\n" \
	"/// <returns>N/A</returns>\n"

#define LC_STRING_COMMENT_ZERO_DATA	"/// <summary>\n" \
	"/// Zeros out the manifest data structure.\n" \
	"/// </summary>\n" \
	"/// <param name=\"data\">Pointer to the manifest data structure</param>\n" \
	"/// <returns>N/A</returns>\n"

#define LC_STRING_COMMENT_INITIALIZE_DATA	"/// <summary>\n" \
	"/// Initializes the manifest data structure.\n" \
	"/// </summary>\n" \
	"/// <param name=\"data\">Pointer to the manifest data structure</param>\n" \
	"/// <returns>Result of the initialization (0 for success, -1 for failure)</returns>\n"

#define LC_STRING_COMMENT_UNINITIALIZE_DATA	"/// <summary>\n" \
	"/// Uninitializes the manifest data structure.\n" \
	"/// </summary>\n" \
	"/// <param name=\"data\">Pointer to the manifest data structure</param>\n" \
	"/// <returns>N/A</returns>\n"


#define LC_STRING_INCLUDE	"#include \"%s.h\"\n\n"
#define LC_STRING_ALLEGRO_INCLUDE	"#include <allegro5/allegro5.h>\n"
#define LC_STRING_ALLEGRO_ADDON_INCLUDE		"#include <allegro5/allegro_%s.h>\n"
#define LC_STRING_DEFAULT_INCLUDE	"#include <stdio.h>\n" \
									"#include <stdlib.h>\n" \
									"#include <string.h>\n" \
									"#include <stdint.h>\n" \
									"#include <stdbool.h>\n\n"

#define LC_STRING_DEFINE			"#define "
#define LC_STRING_HEADER_SECTION	"/* SECTION: %s */\n\n"
#define LC_STRING_SECTION_DEFINES	"DEFINES"
#define LC_STRING_SECTION_TYPEDEF	"TYPEDEF"
#define LC_STRING_SECTION_STRUCT	"STRUCT"
#define LC_STRING_SECTION_FUNCTIONS	"FUNCTIONS"

#define LC_STRING_DISPLAY "display"
#define LC_STRING_TIMER "timer"
#define LC_STRING_EVENT_QUEUE "event_queue"
#define LC_STRING_TITLE "title"


#define LC_STRING_ADDON_AUDIO "audio"
#define LC_STRING_ADDON_ACODEC "acodec"
#define LC_STRING_ADDON_COLOR "color"
#define LC_STRING_ADDON_FONT "font"
#define LC_STRING_ADDON_IMAGE "image"
#define LC_STRING_ADDON_MEMFILE "memfile"
#define LC_STRING_ADDON_DIALOG "dialog"
#define LC_STRING_ADDON_PHYSFS "physfs"
#define LC_STRING_ADDON_PRIMITIVES "primitives"
#define LC_STRING_ADDON_TTF "ttf"

#define LC_STRING_INPUT_KEYBOARD "keyboard"
#define LC_STRING_INPUT_MOUSE "mouse"
#define LC_STRING_INPUT_JOYSTICK "joystick"

#endif // !_HEADER_GUARD_LCOMPILER_STRINGS_H_
