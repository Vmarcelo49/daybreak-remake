// ============================================
// Address:  0x0066eceb
// Original: __unlock_file2
// Status:   unreviewed
// ============================================


/* Library Function - Single Match
    __unlock_file2
   
   Library: Visual Studio 2003 Release */

void __cdecl __unlock_file2(int _Index,void *_File)

{
  if (_Index < 0x14) {
    FUN_0066e7a7(_Index + 0x10);
    return;
  }
  LeaveCriticalSection((LPCRITICAL_SECTION)((int)_File + 0x20));
  return;
}

