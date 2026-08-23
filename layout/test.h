/*
 * File "test.h" generated from compiled manifest
. * 2026-08-23 08:31:57
 * Do not modify this file.
 */

#ifndef _HEADER_GUARD_TEST_DATA_H_
#define _HEADER_GUARD_TEST_DATA_H_

#include <allegro5/allegro5.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

/* SECTION: DEFINES */

#define TEST_VERSION 1.0
#define TEST_TITLE "Test"
#define TEST_DISPLAY_WIDTH 800
#define TEST_DISPLAY_HEIGHT 600
#define TEST_TIMER_SPEED 60.0

/* SECTION: TYPEDEF */

typedef struct test_data_tag_t test_data_t;

/* SECTION: STRUCT */

struct test_data_tag_t
{
	ALLEGRO_DISPLAY* m_display;
	ALLEGRO_TIMER* m_timer;
	ALLEGRO_EVENT_QUEUE* m_event_queue;
};

/* SECTION: FUNCTIONS */

int32_t test_install_allegro(void);
int32_t test_uninstall_allegro(void);
int32_t test_initialize_data(test_data_t* data);
void test_uninitialize_data((null)_data_t* data);

#endif // !_HEADER_GUARD_TEST_DATA_H_

