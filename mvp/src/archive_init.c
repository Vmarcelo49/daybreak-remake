/**
 * archive_init.c — Load all daybreakXX.dat archives at startup
 *
 * The original game loads these archives (from strings at 0x006a5598-0x006a55e8):
 *   daybreak00.dat
 *   daybreak02.dat
 *   daybreak04.dat
 *   daybreak05.dat
 *   daybreak06.dat
 *   daybreak07.dat
 *
 * Each archive is independent and contains different file sets.
 * The lookup function searches all loaded archives in order.
 *
 * Translated from the original game's initialization sequence
 * (multiple calls to FUN_00662ed0 — "add package").
 */

#include "engine.h"
#include "dat_archive.h"
#include <stdio.h>

/* The 6 archive files loaded by the original game (order matters) */
static const char *const ARCHIVE_FILES[] = {
    "daybreak00.dat",
    "daybreak02.dat",
    "daybreak04.dat",
    "daybreak05.dat",
    "daybreak06.dat",
    "daybreak07.dat",
};
#define NUM_ARCHIVES (sizeof(ARCHIVE_FILES) / sizeof(ARCHIVE_FILES[0]))

static DatArchive g_archive_handles[NUM_ARCHIVES] = {0};
static int g_num_loaded = 0;

/* ============================================================
 * LoadAllArchives — open all 6 daybreakXX.dat files
 *
 * Returns: number of archives successfully loaded.
 * If 0, archive mode is disabled (textures will fail to load).
 * ============================================================ */

int LoadAllArchives(void)
{
    g_num_loaded = 0;

    for (int i = 0; i < (int)NUM_ARCHIVES; i++) {
        if (DatArchive_Open(&g_archive_handles[i], ARCHIVE_FILES[i])) {
            g_num_loaded++;
            printf("[archive] Loaded %s\n", ARCHIVE_FILES[i]);
        } else {
            printf("[archive] Failed to load %s (will try to continue)\n",
                   ARCHIVE_FILES[i]);
        }
    }

    printf("[archive] %d/%d archives loaded\n", g_num_loaded, (int)NUM_ARCHIVES);
    return g_num_loaded;
}

/* ============================================================
 * ShutdownAllArchives — close all archive handles
 * ============================================================ */

void ShutdownAllArchives(void)
{
    DatArchive_ShutdownAll();
    g_num_loaded = 0;
}

/* ============================================================
 * GetLoadedArchiveCount — for diagnostics
 * ============================================================ */

int GetLoadedArchiveCount(void)
{
    return g_num_loaded;
}
