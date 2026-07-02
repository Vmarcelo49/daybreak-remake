// ============================================
// Address:  0x0065f8b0
// Original: FUN_0065f8b0
// Status:   unreviewed
// ============================================


void __fastcall FUN_0065f8b0(int *param_1)

{
  DWORD local_8;
  
  if ((char)param_1[0x1d] != '\0') {
    *(undefined1 *)(param_1 + 0x1d) = 0;
    if (param_1[0x1f] != 0) {
      local_8 = 0x103;
      while (local_8 == 0x103) {
        GetExitCodeThread((HANDLE)param_1[0x1f],&local_8);
      }
      CloseHandle((HANDLE)param_1[0x1f]);
      CloseHandle((HANDLE)param_1[0x1e]);
      param_1[0x1f] = 0;
      param_1[0x1e] = 0;
    }
    FUN_0065d670();
    param_1[0x1b] = 0;
    FUN_0065d6a0();
    if (*param_1 != 0) {
      (**(code **)(*(int *)*param_1 + 0x38))(*param_1,0);
    }
    if (param_1[1] != 0) {
      (**(code **)(*(int *)param_1[1] + 8))(param_1[1]);
      param_1[1] = 0;
    }
    if (*param_1 != 0) {
      (**(code **)(*(int *)*param_1 + 8))(*param_1);
      *param_1 = 0;
    }
  }
  return;
}

