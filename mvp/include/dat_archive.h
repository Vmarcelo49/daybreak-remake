/**
 * dat_archive.h — Loader for daybreakXX.dat archive format
 *
 * See dat_archive.c for full format documentation.
 *
 * Usage:
 *   1. DatArchive_Open(&arc, "daybreak00.dat")  — at startup
 *   2. DatArchive_Open(&arc, "daybreak02.dat")  — load more archives
 *   3. void *data = DatArchive_ReadFile(NULL, "data/title/back00.bmp", &size);
 *   4. Use data (XOR-decoded automatically)
 *   5. free(data);
 *   6. DatArchive_ShutdownAll()  — at exit
 */
#ifndef DAYBREAK_DAT_ARCHIVE_H
#define DAYBREAK_DAT_ARCHIVE_H

#include <stdint.h>
#include <stdbool.h>
#include <windows.h>

/* Archive handle — represents one loaded .dat file */
typedef struct DatArchive {
    char      archive_path[MAX_PATH];
    HANDLE    handle;
    uint16_t  num_entries;
    void     *entries;  /* internal: ArchiveEntry[] */
    bool      loaded;
} DatArchive;

/* Resource handle — for streaming reads (mostly unused in MVP) */
typedef struct DatResource {
    HANDLE   handle;
    bool     is_archive;
    uint32_t archive_key;
    uint32_t size;
    uint32_t position;
} DatResource;

/* Archive API */
bool DatArchive_Open(DatArchive *arc, const char *path);
void DatArchive_Close(DatArchive *arc);
void DatArchive_ShutdownAll(void);
bool DatArchive_HasFile(DatArchive *arc, const char *filename);
void *DatArchive_ReadFile(DatArchive *arc, const char *filename, uint32_t *out_size);
void DatArchive_ListFiles(void);

/* Resource API (high-level) */
bool     DatResource_Open(DatResource *res, const char *path);
bool     DatResource_Read(DatResource *res, void *buffer, uint32_t size);
uint32_t DatResource_GetSize(DatResource *res);
void     DatResource_Close(DatResource *res);
void    *DatResource_LoadFile(const char *path, uint32_t *out_size);

#endif /* DAYBREAK_DAT_ARCHIVE_H */
