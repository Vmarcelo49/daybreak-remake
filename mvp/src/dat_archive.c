/**
 * dat_archive.c — Real loader for daybreakXX.dat archive format
 *
 * REVERSE-ENGINEERED FORMAT (from FUN_00662d10, FUN_00663030, FUN_00662ed0):
 *
 * File layout:
 *   Offset  Size      Field
 *   0x00    2         num_entries (uint16 LE)
 *   0x02    N * 0x10c entry_table (XOR-encoded)
 *   0x02 + N * 0x10c  *  file_data (XOR-encoded per-file)
 *
 * Each entry (0x10c = 268 bytes):
 *   Offset  Size  Field
 *   0x00    0x104 filename (null-terminated string, max 260 chars)
 *   0x104   4     file_size (uint32 LE)
 *   0x108   4     file_offset (uint32 LE, from start of .dat file)
 *
 * Entry table XOR (from FUN_00662d10):
 *   key = 100 (initial)
 *   inc = 100 (initial)
 *   for each byte in entry_table:
 *       byte ^= key
 *       key = (key + inc) & 0xFF
 *       inc = (inc + 77) & 0xFF  // 'M' = 77
 *   So keys evolve: 100, 200, 24, 224, 48, ... (mod 256)
 *
 * File data XOR (from FUN_00663030):
 *   key = file_offset_of_this_file
 *   for each byte:
 *       byte ^= (byte)((key >> 1) | 8)
 *   Key is the SAME for all bytes in a single file (constant per file).
 *
 * Multiple archives:
 *   The game loads daybreak00.dat, daybreak02.dat, daybreak04.dat,
 *   daybreak05.dat, daybreak06.dat, daybreak07.dat.
 *   Each is independent — file lookups search across all loaded archives.
 *
 * Translated from:
 *   - FUN_00662d10 (archive open + parse)
 *   - FUN_00662ed0 (add package to global registry)
 *   - FUN_00663030 (read file from archive with XOR decode)
 *   - FUN_006631b0 (create entry struct)
 *   - FUN_00663270 (insert entry into hash map)
 *   - FUN_00662f70 (lookup file by name)
 */

#include "dat_archive.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#define ARCHIVE_ENTRY_SIZE  0x10c   /* 268 bytes per entry */
#define ARCHIVE_FILENAME_OFFSET  0x00
#define ARCHIVE_FILESIZE_OFFSET  0x104
#define ARCHIVE_FILEOFFSET_OFFSET  0x108
#define ARCHIVE_FILENAME_MAXLEN  0x104  /* 260 chars + null */

/* Maximum number of simultaneously loaded archives */
#define MAX_ARCHIVES 16

/* ============================================================
 * Global archive registry (matches original game's singletons)
 * ============================================================ */

typedef struct ArchiveEntry {
    char     filename[ARCHIVE_FILENAME_MAXLEN];
    uint32_t file_size;
    uint32_t file_offset;
} ArchiveEntry;

typedef struct LoadedArchive {
    char      archive_path[MAX_PATH];
    HANDLE    handle;            /* file handle to .dat */
    uint16_t  num_entries;
    ArchiveEntry *entries;       /* malloc'd array of num_entries */
    bool      loaded;
} LoadedArchive;

static LoadedArchive g_archives[MAX_ARCHIVES] = {0};
static int g_num_archives_loaded = 0;

/* ============================================================
 * XOR decode for entry table (from FUN_00662d10)
 *
 *   key = 100; inc = 100;
 *   for each byte:
 *       byte ^= key
 *       key = (key + inc) & 0xFF
 *       inc = (inc + 77) & 0xFF
 * ============================================================ */

static void decode_entry_table(uint8_t *data, size_t size)
{
    uint8_t key = 100;   /* 'd' */
    uint8_t inc = 100;   /* 'd' */
    for (size_t i = 0; i < size; i++) {
        data[i] ^= key;
        key = (uint8_t)((key + inc) & 0xFF);
        inc = (uint8_t)((inc + 77) & 0xFF);  /* 'M' = 77 */
    }
}

/* ============================================================
 * XOR decode for file data (from FUN_00663030)
 *
 *   key = file_offset
 *   for each byte:
 *       byte ^= (byte)((key >> 1) | 8)
 *   Key is CONSTANT per file (same for all bytes).
 * ============================================================ */

static void decode_file_data(uint8_t *data, size_t size, uint32_t file_offset)
{
    uint8_t key = (uint8_t)((file_offset >> 1) | 8);
    for (size_t i = 0; i < size; i++) {
        data[i] ^= key;
    }
}

/* ============================================================
 * DatArchive_Open — open and parse a .dat archive
 *
 * Translated from FUN_00662d10.
 * Returns: true on success, false on failure.
 * ============================================================ */

bool DatArchive_Open(DatArchive *arc, const char *path)
{
    if (!arc || !path) return false;
    if (g_num_archives_loaded >= MAX_ARCHIVES) {
        return false;  /* too many archives */
    }

    memset(arc, 0, sizeof(*arc));
    strncpy(arc->archive_path, path, MAX_PATH - 1);

    /* 1. Open the .dat file */
    HANDLE h = CreateFileA(path, GENERIC_READ, FILE_SHARE_READ, NULL,
                            OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (h == INVALID_HANDLE_VALUE) {
        return false;
    }
    arc->handle = h;

    /* 2. Read num_entries (uint16 LE) */
    uint16_t num_entries = 0;
    DWORD read;
    if (!ReadFile(h, &num_entries, 2, &read, NULL) || read != 2) {
        CloseHandle(h);
        arc->handle = NULL;
        return false;
    }
    arc->num_entries = num_entries;

    /* 3. Read entry table (num_entries * 0x10c bytes) */
    size_t table_size = (size_t)num_entries * ARCHIVE_ENTRY_SIZE;
    uint8_t *table = malloc(table_size);
    if (!table) {
        CloseHandle(h);
        arc->handle = NULL;
        return false;
    }

    if (!ReadFile(h, table, (DWORD)table_size, &read, NULL) || read != table_size) {
        free(table);
        CloseHandle(h);
        arc->handle = NULL;
        return false;
    }

    /* 4. XOR-decode the entry table */
    decode_entry_table(table, table_size);

    /* 5. Parse entries into our struct */
    arc->entries = malloc(num_entries * sizeof(ArchiveEntry));
    if (!arc->entries) {
        free(table);
        CloseHandle(h);
        arc->handle = NULL;
        return false;
    }

    for (uint16_t i = 0; i < num_entries; i++) {
        uint8_t *entry = table + (size_t)i * ARCHIVE_ENTRY_SIZE;
        ArchiveEntry *e = &arc->entries[i];

        /* Filename (null-terminated) */
        memcpy(e->filename, entry + ARCHIVE_FILENAME_OFFSET, ARCHIVE_FILENAME_MAXLEN);
        e->filename[ARCHIVE_FILENAME_MAXLEN - 1] = '\0';

        /* File size (uint32 LE at offset 0x104) */
        e->file_size = *(uint32_t *)(entry + ARCHIVE_FILESIZE_OFFSET);

        /* File offset (uint32 LE at offset 0x108) */
        e->file_offset = *(uint32_t *)(entry + ARCHIVE_FILEOFFSET_OFFSET);
    }

    free(table);

    /* 6. Register in global list (so lookup can find it) */
    if (g_num_archives_loaded < MAX_ARCHIVES) {
        LoadedArchive *slot = &g_archives[g_num_archives_loaded++];
        slot->handle = h;
        slot->num_entries = num_entries;
        slot->entries = arc->entries;
        slot->loaded = true;
        strncpy(slot->archive_path, path, MAX_PATH - 1);
    }

    arc->loaded = true;
    return true;
}

/* ============================================================
 * DatArchive_Close — close archive handle (entries stay registered)
 *
 * Note: original game keeps entries in a global hash map even after
 * closing the file handle. For MVP we do the same — once loaded,
 * file metadata stays in memory.
 * ============================================================ */

void DatArchive_Close(DatArchive *arc)
{
    if (!arc || !arc->loaded) return;
    /* Don't close handle here — keep it for random access reads.
     * Handle is closed in DatArchive_ShutdownAll(). */
    (void)arc;
}

/* ============================================================
 * DatArchive_ShutdownAll — close all archives and free memory
 * ============================================================ */

void DatArchive_ShutdownAll(void)
{
    for (int i = 0; i < g_num_archives_loaded; i++) {
        LoadedArchive *slot = &g_archives[i];
        if (slot->handle && slot->handle != INVALID_HANDLE_VALUE) {
            CloseHandle(slot->handle);
        }
        if (slot->entries) {
            free(slot->entries);
        }
        slot->loaded = false;
        slot->handle = NULL;
        slot->entries = NULL;
    }
    g_num_archives_loaded = 0;
}

/* ============================================================
 * DatArchive_HasFile — check if any loaded archive contains the file
 *
 * Searches all registered archives in order.
 * ============================================================ */

bool DatArchive_HasFile(DatArchive *arc, const char *filename)
{
    (void)arc;  /* arc is now mostly historical — we search global registry */
    if (!filename) return false;

    for (int i = 0; i < g_num_archives_loaded; i++) {
        LoadedArchive *a = &g_archives[i];
        if (!a->loaded) continue;
        for (uint16_t j = 0; j < a->num_entries; j++) {
            if (_stricmp(a->entries[j].filename, filename) == 0) {
                return true;
            }
        }
    }
    return false;
}

/* ============================================================
 * DatArchive_ReadFile — read a file from any loaded archive
 *
 * Translated from FUN_00663030 (ArchiveRead).
 * Returns: malloc'd buffer with decoded file data, or NULL.
 * Caller must free() the buffer.
 * ============================================================ */

void *DatArchive_ReadFile(DatArchive *arc, const char *filename, uint32_t *out_size)
{
    (void)arc;
    if (!filename) return NULL;

    /* 1. Find the file in any loaded archive */
    LoadedArchive *found_archive = NULL;
    ArchiveEntry *found_entry = NULL;

    for (int i = 0; i < g_num_archives_loaded; i++) {
        LoadedArchive *a = &g_archives[i];
        if (!a->loaded) continue;
        for (uint16_t j = 0; j < a->num_entries; j++) {
            if (_stricmp(a->entries[j].filename, filename) == 0) {
                found_archive = a;
                found_entry = &a->entries[j];
                break;
            }
        }
        if (found_entry) break;
    }

    if (!found_entry) {
        if (out_size) *out_size = 0;
        return NULL;
    }

    /* 2. Seek to file offset in the .dat */
    DWORD new_pos = SetFilePointer(found_archive->handle,
                                    (LONG)found_entry->file_offset,
                                    NULL, FILE_BEGIN);
    if (new_pos == INVALID_SET_FILE_POINTER) {
        if (out_size) *out_size = 0;
        return NULL;
    }

    /* 3. Read the raw (encoded) file data */
    uint8_t *data = malloc(found_entry->file_size);
    if (!data) {
        if (out_size) *out_size = 0;
        return NULL;
    }

    DWORD read;
    if (!ReadFile(found_archive->handle, data, found_entry->file_size, &read, NULL)
        || read != found_entry->file_size) {
        free(data);
        if (out_size) *out_size = 0;
        return NULL;
    }

    /* 4. XOR-decode the file data
     * Key = (file_offset >> 1) | 8, constant per file. */
    decode_file_data(data, found_entry->file_size, found_entry->file_offset);

    if (out_size) *out_size = found_entry->file_size;
    return data;
}

/* ============================================================
 * DatArchive_ListFiles — list all files in all loaded archives
 *
 * For debugging / verification.
 * ============================================================ */

void DatArchive_ListFiles(void)
{
    printf("=== Loaded archives: %d ===\n", g_num_archives_loaded);
    for (int i = 0; i < g_num_archives_loaded; i++) {
        LoadedArchive *a = &g_archives[i];
        printf("Archive %d: %s (%u entries)\n",
               i, a->archive_path, a->num_entries);
        for (uint16_t j = 0; j < a->num_entries && j < 10; j++) {
            printf("  [%u] %s (size=%u, offset=%u)\n",
                   j, a->entries[j].filename,
                   a->entries[j].file_size,
                   a->entries[j].file_offset);
        }
        if (a->num_entries > 10) {
            printf("  ... and %u more\n", a->num_entries - 10);
        }
    }
}

/* ============================================================
 * DatResource API — high-level resource access
 *
 * Tries archive first (since direct file mode is not easily
 * activated in the original game per user feedback).
 * ============================================================ */

bool DatResource_Open(DatResource *res, const char *path)
{
    memset(res, 0, sizeof(*res));

    /* Look up in archives only (matches original game behavior) */
    if (DatArchive_HasFile(NULL, path)) {
        res->is_archive = true;
        /* We don't actually open a handle — we'll use DatArchive_ReadFile */
        res->handle = NULL;
        res->size = 0;  /* will be set on read */
        return true;
    }

    return false;
}

bool DatResource_Read(DatResource *res, void *buffer, uint32_t size)
{
    if (!res || !res->is_archive) return false;
    /* Not implemented for archive mode — use DatResource_LoadFile instead */
    (void)buffer;
    (void)size;
    return false;
}

uint32_t DatResource_GetSize(DatResource *res)
{
    if (!res) return 0;
    return res->size;
}

void DatResource_Close(DatResource *res)
{
    if (res) {
        res->handle = NULL;
        res->is_archive = false;
    }
}

/* ============================================================
 * DatResource_LoadFile — convenience: load entire file from archive
 * ============================================================ */

void *DatResource_LoadFile(const char *path, uint32_t *out_size)
{
    return DatArchive_ReadFile(NULL, path, out_size);
}
