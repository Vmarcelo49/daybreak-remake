// ============================================
// Address:  0x0066ec6a
// Original: __lock_file
// Status:   unreviewed
// ============================================

/* Library Function - Single Match
    __lock_file

   Library: Visual Studio 2003 Release */

void __cdecl __lock_file(FILE *_File)

{
    if (((FILE *)0x6b79d7 < _File) && (_File < (FILE *)0x6b7c39))
    {
        __lock(((int)&_File[-0x35bcf]._base >> 5) + 0x10);
        return;
    }
    EnterCriticalSection((LPCRITICAL_SECTION)(_File + 1));
    return;
}
