// Function: FUN_006937e0
// Address:  0x006937e0
// Source:   batch_decompile (mass dump)
// Hash:     30e62978208158d8


undefined4 __thiscall FUN_006937e0(undefined4 *param_1,int param_2)

{
  undefined4 uVar1;
  int iVar2;
  
  if (param_2 == 0) {
    uVar1 = 0;
  }
  else {
    iVar2 = FUN_0068de10(param_1,param_2);
    if (iVar2 == 0) {
      uVar1 = FUN_0068dc80();
      *param_1 = uVar1;
    }
    else {
      uVar1 = FUN_0068dc80();
      FUN_006940b0(uVar1);
    }
    iVar2 = FUN_0068dc80();
    if (iVar2 == 0) {
      uVar1 = FUN_0068de10();
      param_1[1] = uVar1;
    }
    else {
      uVar1 = FUN_0068de10();
      FUN_00687260(uVar1);
    }
    uVar1 = FUN_00699fc0();
    FUN_00694170(param_2);
    param_1[2] = param_1[2] + -1;
  }
  return uVar1;
}

