// ============================================
// Address:  0x0066ecbc
// Original: __unlock_file
// Status:   unreviewed
// ============================================


/* Library Function - Single Match
    __unlock_file
   
   Libraries: Visual Studio 2003 Release, Visual Studio 2005 Release */

void __cdecl __unlock_file(FILE *_File)

{
  if (((FILE *)0x6b79d7 < _File) && (_File < (FILE *)0x6b7c39)) {
    FUN_0066e7a7(((int)&_File[-0x35bcf]._base >> 5) + 0x10);
    return;
  }
  LeaveCriticalSection((LPCRITICAL_SECTION)(_File + 1));
  return;
}

