/*
 * File "manifest.h" generated from compiled manifest
. * 2026-08-22 21:04:55
 * Do not modify this file.
 */

#ifndef _HEADER_GUARD_sual Studio 18_DATA_H_
#define _HEADER_GUARD_sual Studio 18_DATA_H_

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

#define sual Studio 18_VERSION 1.0
#define sual Studio 18_TITLE "Test"
#define sual Studio 18_DISPLAY_WIDTH 800
#define sual Studio 18_DISPLAY_HEIGHT 600
#define sual Studio 18_TIMER_SPEED 60.0

/* SECTION: TYPEDEF */

typedef struct manifest_data_tag_t manifest_data_t;

/* SECTION: STRUCT */

struct manifest_data_tag_t
{
	ALLEGRO_DISPLAY* m_display;
	ALLEGRO_TIMER* m_timer;
	ALLEGRO_EVENT_QUEUE* m_event_queue;
};

/* SECTION: FUNCTIONS */

int32_t manifest_initialize(manifest_data_t* data);
void manifest_shutdown(manifest_data_t* data);

#endif // !_HEADER_GUARD_sual Studio 18_DATA_H_

