#ifndef _HEADER_GUARD_LCOMPILER_COMMON_H_
#define _HEADER_GUARD_LCOMPILER_COMMON_H_

#include <allegro5/allegro5.h>
#include <libogle.h>
#include <libxml.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include "lc_strings.h"

#define LC_UNUSED(x)			(void)(x)
#define LC_LOG_INFO(...)		fprintf(stderr, __VA_ARGS__); fprintf(stderr, "\n")

/**************************************************************************/

enum LC_ADDON_FLAG_IDS
{
	LC_ADDON_FLAG_ID_AUDIO,
	LC_ADDON_FLAG_ID_ACODEC,
	LC_ADDON_FLAG_ID_COLOR,
	LC_ADDON_FLAG_ID_FONT,
	LC_ADDON_FLAG_ID_IMAGE,
	LC_ADDON_FLAG_ID_MEMFILE,
	LC_ADDON_FLAG_ID_DIALOG,
	LC_ADDON_FLAG_ID_PHYSFS,
	LC_ADDON_FLAG_ID_PRIMITIVES,
	LC_ADDON_FLAG_ID_TTF,
	LC_ADDON_FLAG_ID_COUNT
};

enum LC_INPUT_FLAG_IDS
{
	LC_INPUT_FLAG_ID_KEYBOARD,
	LC_INPUT_FLAG_ID_MOUSE,
	LC_INPUT_FLAG_ID_JOYSTICK,
	LC_INPUT_FLAG_ID_COUNT
};

#if defined(ALLEGRO_UNSTABLE) || defined(ALLEGRO_INTERNAL_UNSTABLE) || defined(ALLEGRO_SRC)
#define LC_DISPLAY_FLAG_ID_COUNT 18
#else
#define LC_DISPLAY_FLAG_ID_COUNT 16
#endif

enum LC_DEFINE_TYPES
{
	LC_DEFINE_TYPE_VALUE,
	LC_DEFINE_TYPE_STRING
};

/**************************************************************************/

typedef struct lc_parse_data_tag_t lc_parse_data_t;
typedef struct lc_string_int_pair_tag_t lc_string_int_pair_t;
typedef struct lc_section_tag_t lc_section_t;
typedef struct lc_define_tag_t lc_define_t;
typedef struct lc_display_option_tag_t lc_display_option_t;
typedef struct lc_parse_context_element_tag_t lc_parse_context_element_t;
typedef struct lc_parse_context_attribute_tag_t lc_parse_context_attribute_t;

/**************************************************************************/

struct lc_define_tag_t
{
	o_stringview_t m_prefix;
	o_stringview_t m_name;
	o_stringview_t m_value;
	int32_t m_type;
};

struct lc_display_option_tag_t
{
	int32_t m_type;
	int32_t m_importance;
	int32_t m_value;
};

struct lc_section_tag_t
{
	lc_define_t* m_defines;
	lc_display_option_t* m_display_options;
	int32_t m_display_flags;
	int32_t m_addon_flags;
	int32_t m_input_flags;
};

struct lc_parse_data_tag_t
{
	char m_executable_name[256];
	char m_current_directory[256];
	char m_directory[256];
	char m_prefix[256];
	char m_prefix_upper[256];
	char m_input_filename[256];
	char m_output_filename_header[256];
	char m_output_filename_source[256];
	lc_section_t m_section;
	void* m_user_data;
};

struct lc_string_int_pair_tag_t
{
	const char* m_string;
	int32_t m_value;
};

struct lc_parse_context_element_tag_t
{
	const char* m_name;
	int32_t(*m_parse_function)(lc_parse_data_t* data, const xml_element_t* xml_element);
};

struct lc_parse_context_attribute_tag_t
{
	const char* m_name;
	int32_t(*m_parse_function)(lc_parse_data_t* data, o_stringview_t prefix, const xml_attribute_t* xml_attribute);
	o_stringview_t m_prefix;
};

// lc_arguments.c
int32_t lc_parse_command_line_arguments(int32_t argc, const char** argv, lc_parse_data_t* parse_data);

// lc_utils.c
bool lc_utils_is_valid_identifier(o_stringview_t view);
int32_t lc_char_upper(int32_t c);
int32_t lc_char_lower(int32_t c);
int32_t lc_timestamp(char* buffer, size_t buffer_size, const char* format);
const char* lc_string_upper(const char* str);

// lc_print.c
void lc_print_string(ALLEGRO_FILE* file, const char* string, int32_t(*func)(int32_t));
void lc_print_stringview(ALLEGRO_FILE* file, o_stringview_t view, int32_t(*func)(int32_t));

// lc_pair_array.c
int32_t lc_pair_array_flag_parse(const lc_string_int_pair_t* pair_array, size_t count, o_stringview_t view, char delimiter);

int32_t lc_parse_manifest(lc_parse_data_t* data, const xml_element_t* xml_element);
int32_t lc_parse_manifest_element_addon(lc_parse_data_t* data, const xml_element_t* xml_element);
int32_t lc_parse_manifest_addon_element_attribute(lc_parse_data_t* data, o_stringview_t prefix, const xml_attribute_t* xml_attribute);
int32_t lc_parse_manifest_input_element_attribute(lc_parse_data_t* data, o_stringview_t prefix, const xml_attribute_t* xml_attribute);
int32_t lc_parse_manifest_element_input(lc_parse_data_t* data, const xml_element_t* xml_element);
int32_t lc_parse_manifest_element_application(lc_parse_data_t* data, const xml_element_t* xml_element);
int32_t lc_parse_manifest_element_application_display(lc_parse_data_t* data, const xml_element_t* xml_element);
int32_t lc_parse_display_flags(lc_parse_data_t* data, o_stringview_t prefix, const xml_attribute_t* xml_attribute);
int32_t lc_parse_display_option(lc_parse_data_t* data, const xml_element_t* xml_element);
int32_t lc_parse_display_option_type(lc_parse_data_t* data, o_stringview_t prefix, const xml_attribute_t* xml_attribute);
int32_t lc_parse_display_option_value(lc_parse_data_t* data, o_stringview_t prefix, const xml_attribute_t* xml_attribute);
int32_t lc_parse_display_option_importance(lc_parse_data_t* data, o_stringview_t prefix, const xml_attribute_t* xml_attribute);
int32_t lc_parse_manifest_element_application_timer(lc_parse_data_t* data, const xml_element_t* xml_element);
int32_t lc_parse_manifest_element_application_event_queue(lc_parse_data_t* data, const xml_element_t* xml_element);

int32_t lc_parse_attribute_define_value(lc_parse_data_t* data, o_stringview_t prefix, const xml_attribute_t* xml_attribute);
int32_t lc_parse_attribute_define_string(lc_parse_data_t* data, o_stringview_t prefix, const xml_attribute_t* xml_attribute);




int32_t lc_parse_children_context(lc_parse_data_t* data, const xml_child_t* children, const lc_parse_context_element_t* context, size_t size);
int32_t lc_parse_child_element_context(lc_parse_data_t* data, const xml_element_t* element, const lc_parse_context_element_t* context, size_t size);
int32_t lc_parse_attribute_context(lc_parse_data_t* data, const xml_attribute_t* attribute, const lc_parse_context_attribute_t* context, size_t size);
int32_t lc_parse_attributes_context(lc_parse_data_t* data, const xml_attribute_t* attributes, const lc_parse_context_attribute_t* context, size_t size);

int32_t lc_parse_element_context(lc_parse_data_t* data, const xml_element_t* element, const lc_parse_context_element_t* element_context, size_t element_size, const lc_parse_context_attribute_t* attribute_context, size_t attribute_size);


int32_t lc_output_files(const lc_parse_data_t* data);
int32_t lc_output_file_header(const lc_parse_data_t* data);
int32_t lc_output_file_source(const lc_parse_data_t* data);

int32_t lc_addon_flag_parse(o_stringview_t view);
const char* lc_addon_flag_name(int32_t flag);

int32_t lc_input_flag_parse(o_stringview_t view);
const char* lc_input_flag_name(int32_t flag);

int32_t lc_display_flag_parse(o_stringview_t view);
const char* lc_display_flag_name(int32_t flag);

int32_t lc_display_option_type_parse(o_stringview_t view);
int32_t lc_display_option_importance_parse(o_stringview_t view);
const char* lc_display_option_type_name(int32_t type);
const char* lc_display_option_importance_name(int32_t importance);

void lc_capitalize_string(char* str, size_t size);

void lc_section_zero(lc_section_t* section);
void lc_section_clear(lc_section_t* section);
bool lc_section_add_define(lc_section_t* section, const lc_define_t* define);
bool lc_section_add_display_option(lc_section_t* section, const lc_display_option_t* display_option);
bool lc_section_add_display_option_value(lc_section_t* section, int32_t id, int32_t importance, int32_t value);

#endif // !_HEADER_GUARD_LCOMPILER_COMMON_H_

