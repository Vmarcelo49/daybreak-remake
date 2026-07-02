// ============================================
// Address:  0x00691d90
// Original: FUN_00691d90
// Status:   unreviewed
// ============================================


bool __thiscall FUN_00691d90(HANDLE *param_1,uint param_2)

{
  DWORD DVar1;
  DWORD local_38;
  tagMSG local_2c;
  DWORD local_10;
  uint local_c;
  DWORD local_8;
  
  local_c = param_2;
  if (param_2 != 0xffffffff) {
    local_10 = timeGetTime();
  }
  do {
    local_8 = MsgWaitForMultipleObjects(1,param_1,0,local_c,0x40);
    if (local_8 == 1) {
      PeekMessageA(&local_2c,(HWND)0x0,0,0,0);
      if (local_c != 0xffffffff) {
        DVar1 = timeGetTime();
        if (DVar1 - local_10 < param_2) {
          local_38 = param_2 - (DVar1 - local_10);
        }
        else {
          local_38 = 0;
        }
        local_c = local_38;
      }
    }
  } while (local_8 == 1);
  return local_8 == 0;
}

