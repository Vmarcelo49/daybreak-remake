// ============================================
// Address:  0x00660050
// Original: FUN_00660050
// Status:   unreviewed
// ============================================


void __fastcall FUN_00660050(int *param_1)

{
  DWORD local_c;
  int local_8;
  
  for (local_8 = 1; local_8 < 8; local_8 = local_8 + 1) {
    FUN_00660310(local_8);
  }
  *(undefined1 *)(param_1 + 0x1a) = 0;
  FUN_006605f0();
  if (param_1[0x1c] != 0) {
    local_c = 0x103;
    while (local_c == 0x103) {
      GetExitCodeThread((HANDLE)param_1[0x1c],&local_c);
    }
    CloseHandle((HANDLE)param_1[0x1c]);
    CloseHandle((HANDLE)param_1[0x1b]);
    param_1[0x1c] = 0;
    param_1[0x1b] = 0;
  }
  FUN_0065d670();
  param_1[0x19] = 0;
  FUN_0065d6a0();
  if (param_1[1] != 0) {
    (**(code **)(*(int *)param_1[1] + 0x20))(param_1[1]);
  }
  if (param_1[1] != 0) {
    (**(code **)(*(int *)param_1[1] + 8))(param_1[1]);
    param_1[1] = 0;
  }
  if (*param_1 != 0) {
    FUN_006605f0();
    (**(code **)(*(int *)*param_1 + 0x5c))(*param_1,1);
  }
  if (*param_1 != 0) {
    (**(code **)(*(int *)*param_1 + 8))(*param_1);
    *param_1 = 0;
  }
  _memset(param_1 + 10,0,0x20);
  return;
}

