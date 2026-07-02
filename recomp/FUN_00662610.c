// ============================================
// Address:  0x00662610
// Original: FUN_00662610
// Status:   unreviewed
// ============================================


void __fastcall FUN_00662610(undefined4 *param_1)

{
  *param_1 = &PTR_FUN_006ab0f8;
  if (param_1[1] != 0) {
    _free((void *)param_1[1]);
    param_1[1] = 0;
  }
  if (param_1[3] != 0) {
    (**(code **)(*(int *)param_1[3] + 8))(param_1[3]);
    param_1[3] = 0;
  }
  if (param_1[4] != 0) {
    _free((void *)param_1[4]);
    param_1[4] = 0;
  }
  if (param_1[5] != 0) {
    _free((void *)param_1[5]);
    param_1[5] = 0;
  }
  if (param_1[7] != 0) {
    _free((void *)param_1[7]);
    param_1[7] = 0;
  }
  if (param_1[8] != 0) {
    (**(code **)(*(int *)param_1[8] + 8))(param_1[8]);
    param_1[8] = 0;
  }
  if (param_1[10] != 0) {
    _free((void *)param_1[10]);
    param_1[10] = 0;
  }
  if (param_1[0xc] != 0) {
    (**(code **)(*(int *)param_1[0xc] + 8))(param_1[0xc]);
    param_1[0xc] = 0;
  }
  if (param_1[0xd] != 0) {
    _free((void *)param_1[0xd]);
    param_1[0xd] = 0;
  }
  if (param_1[0xf] != 0) {
    (**(code **)(*(int *)param_1[0xf] + 8))(param_1[0xf]);
    param_1[0xf] = 0;
  }
  if (param_1[0x10] != 0) {
    _free((void *)param_1[0x10]);
    param_1[0x10] = 0;
  }
  if (param_1[0x11] != 0) {
    _free((void *)param_1[0x11]);
    param_1[0x11] = 0;
  }
  return;
}

