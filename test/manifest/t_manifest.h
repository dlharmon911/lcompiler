/*
 * File "t_manifest.h" generated from compiled manifest
. * 2026-09-01 19:16:34
 * Do not modify this file.
 */

#ifndef _HEADER_GUARD_TEST_DATA_H_
#define _HEADER_GUARD_TEST_DATA_H_

#include <allegro5/allegro5.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
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

typedef struct t_manifest_data_tag_t t_manifest_data_t;

/* SECTION: STRUCT */

struct t_manifest_data_tag_t
{
	ALLEGRO_DISPLAY* m_display;
	ALLEGRO_TIMER* m_timer;
	ALLEGRO_EVENT_QUEUE* m_event_queue;
};

/* SECTION: FUNCTIONS */

/// <summary>
/// Installs the Allegro library, Allegro addons and input devices.
/// </summary>
/// <param name="N/A"></param>
/// <returns>Result of the installation (0 for success, -1 for failure)</returns>
int32_t t_manifest_install_allegro(void);

/// <summary>
/// Uninstalls the Allegro library, Allegro addons and input devices.
/// </summary>
/// <param name="N/A"></param>
/// <returns>N/A</returns>
void t_manifest_uninstall_allegro(void);

/// <summary>
/// Zeros out the manifest data structure.
/// </summary>
/// <param name="data">Pointer to the manifest data structure</param>
/// <returns>N/A</returns>
void t_manifest_zero_data(t_manifest_data_t* data);

/// <summary>
/// Initializes the manifest data structure.
/// </summary>
/// <param name="data">Pointer to the manifest data structure</param>
/// <returns>Result of the initialization (0 for success, -1 for failure)</returns>
int32_t t_manifest_initialize_data(t_manifest_data_t* data);

/// <summary>
/// Uninitializes the manifest data structure.
/// </summary>
/// <param name="data">Pointer to the manifest data structure</param>
/// <returns>N/A</returns>
void t_manifest_uninitialize_data(t_manifest_data_t* data);

#endif // !_HEADER_GUARD_TEST_DATA_H_
