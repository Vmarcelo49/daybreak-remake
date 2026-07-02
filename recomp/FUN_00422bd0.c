// ============================================
// Address:  0x00422bd0
// Original: FUN_00422bd0
// Status:   unreviewed
// ============================================


undefined1 __thiscall
FUN_00422bd0(int param_1,short param_2,short param_3,short param_4,char param_5,float param_6,
            undefined4 param_7,undefined4 param_8)

{
  undefined1 uVar1;
  int iVar2;
  undefined1 local_28 [8];
  undefined4 local_20;
  undefined4 local_1c;
  undefined1 local_18 [12];
  int local_c;
  short local_8;
  
  if (*(int *)(param_1 + 0xaed0) == 0) {
    uVar1 = 0;
  }
  else {
    if (DAT_006cfdb0 == '\x01') {
      FUN_00424000();
      local_20 = *(undefined4 *)(param_1 + 8);
      local_1c = *(undefined4 *)(*(int *)(param_1 + 0xaed0) + 8);
      FUN_00415d30(0,local_28,0,8);
    }
    *(int *)(*(int *)(param_1 + 0xaed0) + 0x7b0) = *(int *)(*(int *)(param_1 + 0xaed0) + 0x7b0) + 1;
    *(int *)(*(int *)(param_1 + 0xaed0) + 0x7b4) = *(int *)(*(int *)(param_1 + 0xaed0) + 0x7b4) + 1;
    if (param_5 == '\0') {
      local_c = 100;
      iVar2 = 0;
    }
    else {
      iVar2 = *(int *)(*(int *)(param_1 + 0xaed0) + 0x7b0);
      if (iVar2 == 1) {
        local_c = 100;
      }
      else if (iVar2 == 2) {
        local_c = 0x46;
      }
      else if (iVar2 == 3) {
        local_c = 0x32;
      }
      else {
        local_c = 0x21;
      }
    }
    *(undefined1 *)(*(int *)(param_1 + 0xaed0) + 0xaecc) = 0;
    local_8 = FUN_00639160(*(undefined4 *)(param_1 + 0xaed0),param_1,(param_4 * local_c) / 100,
                           CONCAT22((short)((uint)iVar2 >> 0x10),param_3),0);
    if (local_8 == 0x1f7) {
      FUN_00421080(0x1f7);
    }
    else if (local_8 < 0) {
      FUN_00421080((int)param_2);
    }
    else {
      FUN_00421080((int)param_3);
    }
    *(undefined4 *)(*(int *)(param_1 + 0xaed0) + 0x878) = param_7;
    *(undefined4 *)(*(int *)(param_1 + 0xaed0) + 0x87c) = param_8;
    FUN_00423750(*(float *)(*(int *)(param_1 + 0xaed0) + 0x14) - *(float *)(param_1 + 0x14),0,
                 *(float *)(*(int *)(param_1 + 0xaed0) + 0x1c) - *(float *)(param_1 + 0x1c));
    *(undefined4 *)(*(int *)(param_1 + 0xaed0) + 0x14) = *(undefined4 *)(param_1 + 0x14);
    *(undefined4 *)(*(int *)(param_1 + 0xaed0) + 0x1c) = *(undefined4 *)(param_1 + 0x1c);
    FUN_0042cb50(local_18);
    FUN_0042dd90();
    *(float *)(*(int *)(param_1 + 0xaed0) + 100) =
         ((*(float *)(param_1 + 0x5c) + *(float *)(param_1 + 100)) -
         *(float *)(*(int *)(param_1 + 0xaed0) + 0x5c)) + param_6;
    while (*(float *)(*(int *)(param_1 + 0xaed0) + 100) < -180.0) {
      *(float *)(*(int *)(param_1 + 0xaed0) + 100) =
           *(float *)(*(int *)(param_1 + 0xaed0) + 100) + 360.0;
    }
    while (180.0 < *(float *)(*(int *)(param_1 + 0xaed0) + 100)) {
      *(float *)(*(int *)(param_1 + 0xaed0) + 100) =
           *(float *)(*(int *)(param_1 + 0xaed0) + 100) - 360.0;
    }
    *(undefined4 *)(*(int *)(param_1 + 0xaed0) + 0xaed0) = 0;
    *(undefined4 *)(param_1 + 0xaed0) = 0;
    uVar1 = *(undefined1 *)(param_1 + 0xaeca);
  }
  return uVar1;
}

