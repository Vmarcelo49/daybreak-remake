// ============================================
// Address:  0x00422950
// Original: FUN_00422950
// Status:   unreviewed
// ============================================


undefined4 __thiscall FUN_00422950(int param_1,short param_2,undefined1 param_3,int param_4)

{
  undefined4 uVar1;
  undefined1 local_2c [8];
  undefined4 local_24;
  undefined4 local_20;
  undefined1 local_1c;
  undefined1 local_18 [8];
  undefined4 local_10;
  undefined4 local_c;
  undefined1 local_8;
  
  if (param_4 != 0) {
    FUN_00423530(param_4);
  }
  if (*(int *)(param_1 + 0xaed0) == 0) {
    if (*(int *)(*(int *)(param_1 + 0x308) + 0xaed0) == 0) {
      if (DAT_006cfdb0 == '\x01') {
        FUN_00423f30();
        local_24 = *(undefined4 *)(param_1 + 8);
        local_20 = *(undefined4 *)(*(int *)(param_1 + 0x308) + 8);
        local_1c = param_3;
        FUN_00415d30(0,local_2c,0,8);
      }
      *(undefined4 *)(param_1 + 0xaed0) = *(undefined4 *)(param_1 + 0x308);
      FUN_00421080((int)param_2);
      *(undefined1 *)(*(int *)(param_1 + 0xaed0) + 0xaecc) = 1;
      *(int *)(*(int *)(param_1 + 0xaed0) + 0xaed0) = param_1;
      *(undefined1 *)(param_1 + 0xaed8) = param_3;
      uVar1 = 1;
    }
    else {
      uVar1 = 0;
    }
  }
  else {
    if (DAT_006cfdb0 == '\x01') {
      FUN_00423f30();
      local_10 = *(undefined4 *)(param_1 + 8);
      local_c = *(undefined4 *)(*(int *)(param_1 + 0xaed0) + 8);
      local_8 = param_3;
      FUN_00415d30(0,local_18,0,8);
    }
    FUN_00421080((int)param_2);
    *(undefined1 *)(param_1 + 0xaed8) = param_3;
    uVar1 = 1;
  }
  return uVar1;
}

