// Function: FUN_004259a0
// Address:  0x004259a0
// Source:   batch_decompile (mass dump)
// Hash:     380c6c236e12251e


undefined4 __thiscall FUN_004259a0(int param_1,uint param_2)

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
    uVar1 = FUN_00426820();
    if (uVar1 < param_2) {
      FUN_004267c0();
    }
    else {
      uVar2 = FUN_00667580(param_2);
      *(undefined4 *)(param_1 + 4) = uVar2;
      *(undefined4 *)(param_1 + 8) = *(undefined4 *)(param_1 + 4);
      *(uint *)(param_1 + 0xc) = param_2 * 0xc + *(int *)(param_1 + 4);
    }
    uVar2 = 1;
  }
  return uVar2;
}

