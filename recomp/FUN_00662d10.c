// ============================================
// Address:  0x00662d10
// Original: FUN_00662d10
// Status:   unreviewed
// ============================================


undefined4 __thiscall FUN_00662d10(int *param_1,LPCSTR param_2)

{
  HANDLE pvVar1;
  undefined4 uVar2;
  undefined1 local_138 [276];
  void *local_24;
  byte local_1d;
  void *local_1c;
  ushort local_18 [3];
  char local_11;
  uint local_10;
  DWORD local_c;
  void *local_8;
  
  if (*param_1 != 0) {
    CloseHandle((HANDLE)*param_1);
  }
  pvVar1 = CreateFileA(param_2,0x80000000,1,(LPSECURITY_ATTRIBUTES)0x0,3,0x80,(HANDLE)0x0);
  *param_1 = (int)pvVar1;
  if (*param_1 == -1) {
    *param_1 = 0;
    uVar2 = 0;
  }
  else {
    ReadFile((HANDLE)*param_1,local_18,2,&local_c,(LPOVERLAPPED)0x0);
    local_24 = operator_new((uint)local_18[0] * 0x10c);
    local_1c = local_24;
    local_8 = local_24;
    ReadFile((HANDLE)*param_1,local_24,(uint)local_18[0] * 0x10c,&local_c,(LPOVERLAPPED)0x0);
    local_1d = 100;
    local_11 = 'd';
    for (local_10 = 0; local_10 < (uint)local_18[0] * 0x10c; local_10 = local_10 + 1) {
      *(byte *)((int)local_8 + local_10) = *(byte *)((int)local_8 + local_10) ^ local_1d;
      local_1d = local_1d + local_11;
      local_11 = local_11 + 'M';
    }
    for (local_10 = 0; local_10 < local_18[0]; local_10 = local_10 + 1) {
      uVar2 = FUN_006631b0((void *)(local_10 * 0x10c + (int)local_1c),
                           *(undefined4 *)((int)local_1c + local_10 * 0x10c + 0x104),
                           *(undefined4 *)((int)local_1c + local_10 * 0x10c + 0x108));
      FUN_00663270(local_138,uVar2);
    }
    _free(local_8);
    uVar2 = 1;
  }
  return uVar2;
}

