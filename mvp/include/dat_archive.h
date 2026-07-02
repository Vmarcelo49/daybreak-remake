/**
 * dat_archive.h — Loader for daybreakXX.dat archive format
 *
 * See dat_archive.c for format documentation.
 */
#ifndef DAYBREAK_DAT_ARCHIVE_H
#define DAYBREAK_DAT_ARCHIVE_H

#include <stdint.h>
#include <stdbool.h>
#include <windows.h>

/* Resource handle — wraps either a direct file or an archive entry */
typedef struct DatResource {
    HANDLE  handle;
    bool    is_archive;
    uint32_t archive_key;    /* XOR key for archive entries */
    uint32_t size;           /* Total size in bytes */
    uint32_t position;       /* Current read position (for archive) */
} DatResource;

/* Archive handle — for daybreakXX.dat files (future) */
typedef struct DatArchive {
    HANDLE  handle;
    uint32_t key;
    /* TODO: file table */
} DatArchive;

/* Resource API — matches original FUN_00653540/00653a40/00653760 */
bool     DatResource_Open(DatResource *res, const char *path);
bool     DatResource_Read(DatResource *res, void *buffer, uint32_t size);
uint32_t DatResource_GetSize(DatResource *res);
void     DatResource_Close(DatResource *res);

/* Convenience: load entire file into memory.
 * Returns malloc'd buffer (caller must free) or NULL on failure. */
void    *DatResource_LoadFile(const char *path, uint32_t *out_size);

/* Archive API — for daybreakXX.dat (stub for MVP+3) */
bool DatArchive_Open(DatArchive *arc, const char *path);
void DatArchive_Close(DatArchive *arc);
bool DatArchive_HasFile(DatArchive *arc, const char *filename);
void *DatArchive_ReadFile(DatArchive *arc, const char *filename, uint32_t *out_size);

#endif /* DAYBREAK_DAT_ARCHIVE_H */
