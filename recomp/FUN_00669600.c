// ============================================
// Address:  0x00669600
// Original: FUN_00669600
// Status:   unreviewed
// ============================================


void __thiscall FUN_00669600(LPCVOID param_1,LPCSTR param_2)

{
  DWORD local_c;
  HANDLE local_8;
  
  local_8 = CreateFileA(param_2,0x40000000,0,(LPSECURITY_ATTRIBUTES)0x0,4,0x80,(HANDLE)0x0);
  if (local_8 != (HANDLE)0xffffffff) {
    WriteFile(local_8,param_1,0x12,&local_c,(LPOVERLAPPED)0x0);
    WriteFile(local_8,(LPCVOID)((int)param_1 + 0x18),4,&local_c,(LPOVERLAPPED)0x0);
    WriteFile(local_8,*(LPCVOID *)((int)param_1 + 0x14),*(DWORD *)((int)param_1 + 0x18),&local_c,
              (LPOVERLAPPED)0x0);
    CloseHandle(local_8);
  }
  return;
}

