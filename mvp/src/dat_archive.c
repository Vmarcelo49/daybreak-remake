/**
 * dat_archive.c — Loader for daybreakXX.dat archive format
 *
 * The original DaybreakDX.exe supports TWO modes of resource access:
 *   1. Direct file: tries CreateFileA("data/title/title.bmp") first
 *   2. Archive: if direct file fails, searches inside daybreak00-07.dat
 *
 * Archive format (reverse-engineered from FUN_00662f70, FUN_00663030):
 *   - Archive has a header (param_1[1] = key, param_1[2] = entry_size)
 *   - Files inside are XOR-obfuscated: each byte is XORed with ((key >> 1) | 8)
 *   - Each entry has metadata: offset (0x108), size (0x104), name
 *   - SetFilePointer + ReadFile used to access
 *
 * For MVP+3, we implement:
 *   - Direct file loading (primary path — works with loose files in data/)
 *   - Archive loading (secondary path — for original game distribution)
 *
 * Translated from:
 *   - FUN_00653540 (ResourceExists)
 *   - FUN_00653a40 (GetResourceSize)
 *   - FUN_00653760 (ReadResource)
 *   - FUN_00662f70 (ArchiveLookup)
 *   - FUN_00663030 (ArchiveRead — with XOR decode)
 */

#include "engine.h"
#include "dat_archive.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

/* XOR key transformation — from FUN_00663030:
 *   *(byte*)buf[i] ^= ((byte)(key >> 1) | 8)
 * where key is the archive's base key (param_1[1]). */
static uint8_t xor_transform(uint8_t b, uint32_t key)
{
    return b ^ (uint8_t)((key >> 1) | 8);
}

/* ============================================================
 * Public API
 * ============================================================ */

bool DatResource_Open(DatResource *res, const char *path)
{
    memset(res, 0, sizeof(*res));

    /* Try direct file first — matches original FUN_00653540 behavior */
    HANDLE h = CreateFileA(path, GENERIC_READ, FILE_SHARE_READ, NULL,
                            OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (h != INVALID_HANDLE_VALUE) {
        res->handle = h;
        res->is_archive = false;
        res->size = GetFileSize(h, NULL);
        return true;
    }

    /* TODO: implement archive lookup in daybreakXX.dat
     * For MVP+3, we only support direct files.
     * Real game would search daybreak00.dat..daybreak07.dat here. */
    return false;
}

bool DatResource_Read(DatResource *res, void *buffer, uint32_t size)
{
    if (!res || !res->handle) return false;

    DWORD read;
    if (!ReadFile(res->handle, buffer, size, &read, NULL)) {
        return false;
    }
    if (read != size) {
        return false;
    }

    /* If reading from archive, XOR-decode the buffer.
     * For direct files, no transformation needed. */
    if (res->is_archive && res->archive_key != 0) {
        uint8_t *bytes = (uint8_t *)buffer;
        for (uint32_t i = 0; i < size; i++) {
            bytes[i] = xor_transform(bytes[i], res->archive_key);
        }
    }

    return true;
}

uint32_t DatResource_GetSize(DatResource *res)
{
    if (!res || !res->handle) return 0;
    return res->size;
}

void DatResource_Close(DatResource *res)
{
    if (res && res->handle) {
        CloseHandle(res->handle);
        res->handle = NULL;
    }
}

/* ============================================================
 * Convenience: load entire file into memory
 * ============================================================ */

void *DatResource_LoadFile(const char *path, uint32_t *out_size)
{
    DatResource res;
    if (!DatResource_Open(&res, path)) {
        return NULL;
    }

    uint32_t size = DatResource_GetSize(&res);
    if (size == 0) {
        DatResource_Close(&res);
        return NULL;
    }

    void *data = malloc(size);
    if (!data) {
        DatResource_Close(&res);
        return NULL;
    }

    if (!DatResource_Read(&res, data, size)) {
        free(data);
        DatResource_Close(&res);
        return NULL;
    }

    DatResource_Close(&res);
    if (out_size) *out_size = size;
    return data;
}

/* ============================================================
 * Archive enumeration (stub for future — direct files work for now)
 * ============================================================ */

bool DatArchive_Open(DatArchive *arc, const char *path)
{
    /* TODO: implement archive format parsing.
     * Header format (from analysis of FUN_00662f70):
     *   - List of entries, each with:
     *     - offset (at +0x108 of entry struct)
     *     - size (at +0x104 of entry struct)
     *     - name string
     *   - File data XOR-obfuscated with ((key >> 1) | 8)
     *
     * For MVP+3, archives are not needed if files are loose in data/.
     */
    (void)arc;
    (void)path;
    return false;
}

void DatArchive_Close(DatArchive *arc)
{
    (void)arc;
}

bool DatArchive_HasFile(DatArchive *arc, const char *filename)
{
    (void)arc;
    (void)filename;
    return false;
}

void *DatArchive_ReadFile(DatArchive *arc, const char *filename, uint32_t *out_size)
{
    (void)arc;
    (void)filename;
    if (out_size) *out_size = 0;
    return NULL;
}
