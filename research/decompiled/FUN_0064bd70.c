// Function: FUN_0064bd70
// Address:  0x0064bd70
// Source:   batch_decompile (mass dump)
// Hash:     cc370b2fe79e9b5a


void __thiscall FUN_0064bd70(int param_1,int param_2)

{
  undefined4 uVar1;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_8;
  
  if (*(char *)(param_1 + param_2 + 0x55c1) != -1) {
    for (local_8 = (int)*(char *)(param_1 + param_2 + 0x55c1); local_8 < 3; local_8 = local_8 + 1) {
      uVar1 = *(undefined4 *)(param_1 + 0x52f8 + local_8 * 4);
      *(undefined4 *)(param_1 + 0x52f8 + local_8 * 4) =
           *(undefined4 *)(param_1 + 0x52fc + local_8 * 4);
      *(undefined4 *)(param_1 + 0x52fc + local_8 * 4) = uVar1;
    }
    for (local_10 = 0; local_10 < 8; local_10 = local_10 + 1) {
      *(undefined1 *)(param_1 + local_10 + 0x55c1) = 0xff;
    }
    for (local_14 = 0; local_14 < 3; local_14 = local_14 + 1) {
      if (-1 < *(int *)(param_1 + 0x52f8 + local_14 * 4)) {
        *(undefined1 *)(param_1 + 0x55c1 + *(int *)(param_1 + 0x52f8 + local_14 * 4)) =
             (undefined1)local_14;
      }
    }
    *(undefined1 *)(param_1 + param_2 + 0x55c1) = 0xff;
    *(undefined4 *)(param_1 + 0x5304) = 0xffffffff;
    FUN_0064bf60();
  }
  return;
}

