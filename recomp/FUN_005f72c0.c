// ============================================
// Address:  0x005f72c0
// Original: FUN_005f72c0
// Status:   unreviewed
// ============================================


void __thiscall FUN_005f72c0(int param_1,float param_2,float param_3)

{
  undefined1 local_38 [8];
  undefined1 local_30;
  undefined1 local_2f;
  undefined4 local_2c;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  int local_8;
  
  *(float *)(param_1 + 0x6c) = param_3 + *(float *)(param_1 + 0x6c);
  *(float *)(param_1 + 0x5c) = param_2 + *(float *)(param_1 + 0x5c);
  if (180.0 < *(float *)(param_1 + 0x5c)) {
    *(float *)(param_1 + 0x5c) = *(float *)(param_1 + 0x5c) - 360.0;
  }
  if (*(float *)(param_1 + 0x5c) < -180.0) {
    *(float *)(param_1 + 0x5c) = *(float *)(param_1 + 0x5c) + 360.0;
  }
  *(undefined4 *)(param_1 + 0x38) = *(undefined4 *)(&DAT_006cfae0 + *(int *)(param_1 + 8) * 4);
  for (local_8 = 0; local_8 < 4; local_8 = local_8 + 1) {
    if ((*(ushort *)(param_1 + 0x88 + local_8 * 2) & 0x100) != 0) {
      *(int *)(param_1 + 8) = local_8;
    }
  }
  if ((DAT_006cfdb0 == '\x01') && (*(int *)(param_1 + 0x160) != 0)) {
    FUN_005f7860();
    local_30 = *(undefined1 *)(*(int *)(*(int *)(param_1 + 0x11c) + 0x2c) + 8);
    local_2c = *(undefined4 *)(param_1 + 0x160);
    local_2f = *(undefined1 *)(*(int *)(param_1 + 0x38) + 8);
    local_24 = *(undefined4 *)(param_1 + 0x14);
    local_20 = *(undefined4 *)(param_1 + 0x18);
    local_1c = *(undefined4 *)(param_1 + 0x1c);
    local_18 = *(undefined4 *)(param_1 + 0x5c);
    local_14 = *(undefined4 *)(param_1 + 100);
    local_10 = *(undefined4 *)(param_1 + 0x6c);
    local_c = *(undefined4 *)(param_1 + 0x54);
    FUN_00415d30(0,local_38,0,0x88);
  }
  return;
}

