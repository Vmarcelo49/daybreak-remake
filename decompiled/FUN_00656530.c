// Function: FUN_00656530
// Address:  0x00656530
// Source:   batch_decompile (mass dump)
// Hash:     f0e3b5df90e77e9e


undefined4 __thiscall FUN_00656530(int param_1,uint param_2)

{
  uint uVar1;
  undefined4 uVar2;
  
  *(undefined4 *)(param_1 + 4) = 0;
  *(undefined4 *)(param_1 + 8) = 0;
  *(undefined4 *)(param_1 + 0xc) = 0;
  if (param_2 == 0) {
    uVar2 = 0;
  }
  else {
    uVar1 = FUN_0065a6b0();
    if (uVar1 < param_2) {
      FUN_00656620();
    }
    else {
      uVar2 = FUN_004107e0(param_2);
      *(undefined4 *)(param_1 + 4) = uVar2;
      *(undefined4 *)(param_1 + 8) = *(undefined4 *)(param_1 + 4);
      *(uint *)(param_1 + 0xc) = *(int *)(param_1 + 4) + param_2 * 4;
    }
    uVar2 = 1;
  }
  return uVar2;
}

