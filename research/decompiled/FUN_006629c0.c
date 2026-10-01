// Function: FUN_006629c0
// Address:  0x006629c0
// Source:   batch_decompile (mass dump)
// Hash:     ca21164c77076b5e


void FUN_006629c0(LPCSTR param_1)

{
  char cVar1;
  undefined2 uVar2;
  int iVar3;
  undefined4 uVar4;
  undefined4 *puVar5;
  LPCSTR lpFileName;
  DWORD dwDesiredAccess;
  DWORD dwShareMode;
  LPSECURITY_ATTRIBUTES lpSecurityAttributes;
  DWORD dwCreationDisposition;
  DWORD dwFlagsAndAttributes;
  HANDLE hTemplateFile;
  undefined4 extraout_var;
  undefined1 local_68 [4];
  void *local_64;
  void *local_60;
  undefined1 local_5c [4];
  undefined1 local_58 [4];
  undefined2 *local_54;
  undefined1 local_50 [4];
  undefined2 *local_4c;
  uint local_48;
  LPVOID local_44;
  byte local_3d;
  DWORD local_3c;
  byte local_35;
  uint local_34;
  uint local_30;
  undefined2 *local_2c;
  undefined4 local_28;
  char local_21;
  uint local_20;
  DWORD local_1c;
  HANDLE local_18;
  HANDLE local_14;
  undefined2 *local_10;
  DWORD local_c;
  undefined4 local_8;
  
  local_18 = CreateFileA(param_1,0x40000000,0,(LPSECURITY_ATTRIBUTES)0x0,2,0x80,(HANDLE)0x0);
  if (local_18 != (HANDLE)0xffffffff) {
    uVar4 = extraout_var;
    SetFilePointer(local_18,0,(PLONG)0x0,0);
    FUN_00663240(&local_8);
    FUN_00654620(&local_28);
    iVar3 = FUN_00699fc0(uVar4);
    local_30 = iVar3 * 0x10c + 2;
    local_4c = operator_new(local_30);
    local_10 = local_4c + 1;
    local_2c = local_4c;
    uVar2 = FUN_00699fc0();
    *local_2c = uVar2;
    local_34 = local_30;
    local_20 = 0;
    while (cVar1 = const_iterator__operator__(&local_28), cVar1 != '\0') {
      iVar3 = FUN_00663510();
      *(uint *)(iVar3 + 0x108) = local_34;
      *(uint *)(local_10 + local_20 * 0x86 + 0x84) = local_34;
      iVar3 = FUN_00663510();
      *(undefined4 *)(local_10 + local_20 * 0x86 + 0x82) = *(undefined4 *)(iVar3 + 0x104);
      uVar4 = FUN_00663510();
      FUN_0066b860(local_10 + local_20 * 0x86,uVar4);
      iVar3 = FUN_00663510();
      uVar4 = FUN_00663510(*(undefined4 *)(iVar3 + 0x104));
      _printf("%s / %d \n",uVar4);
      iVar3 = FUN_00663510();
      local_34 = local_34 + *(int *)(iVar3 + 0x104);
      FUN_00663530(local_50,0);
      local_20 = local_20 + 1;
    }
    local_35 = 100;
    local_21 = 'd';
    for (local_20 = 2; local_20 < local_30; local_20 = local_20 + 1) {
      *(byte *)((int)local_2c + local_20) = *(byte *)((int)local_2c + local_20) ^ local_35;
      local_35 = local_35 + local_21;
      local_21 = local_21 + 'M';
    }
    WriteFile(local_18,local_2c,local_30,&local_1c,(LPOVERLAPPED)0x0);
    local_54 = local_2c;
    _free(local_2c);
    puVar5 = (undefined4 *)FUN_00663240(local_58);
    local_8 = *puVar5;
    puVar5 = (undefined4 *)FUN_00654620(local_5c);
    local_28 = *puVar5;
    while (cVar1 = const_iterator__operator__(&local_28), cVar1 != '\0') {
      hTemplateFile = (HANDLE)0x0;
      dwFlagsAndAttributes = 0x80;
      dwCreationDisposition = 3;
      lpSecurityAttributes = (LPSECURITY_ATTRIBUTES)0x0;
      dwShareMode = 0;
      dwDesiredAccess = 0x80000000;
      lpFileName = (LPCSTR)FUN_00663510();
      local_14 = CreateFileA(lpFileName,dwDesiredAccess,dwShareMode,lpSecurityAttributes,
                             dwCreationDisposition,dwFlagsAndAttributes,hTemplateFile);
      if (local_14 != (HANDLE)0xffffffff) {
        local_3c = GetFileSize(local_14,(LPDWORD)0x0);
        local_60 = operator_new(local_3c);
        local_44 = local_60;
        iVar3 = FUN_00663510();
        local_3d = (byte)(*(uint *)(iVar3 + 0x108) >> 1) | 8;
        ReadFile(local_14,local_44,local_3c,&local_c,(LPOVERLAPPED)0x0);
        for (local_48 = 0; local_48 < local_3c; local_48 = local_48 + 1) {
          *(byte *)((int)local_44 + local_48) = *(byte *)((int)local_44 + local_48) ^ local_3d;
        }
        WriteFile(local_18,local_44,local_3c,&local_1c,(LPOVERLAPPED)0x0);
        CloseHandle(local_14);
        local_64 = local_44;
        _free(local_44);
      }
      FUN_00663530(local_68,0);
    }
    CloseHandle(local_18);
  }
  return;
}

