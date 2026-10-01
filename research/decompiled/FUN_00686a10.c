// Function: FUN_00686a10
// Address:  0x00686a10
// Source:   batch_decompile (mass dump)
// Hash:     dfe14739cad3e038


undefined4 __thiscall FUN_00686a10(int param_1,int param_2)

{
  int iVar1;
  
  if (param_2 != param_1) {
    FUN_00686fb0(param_1);
    iVar1 = FUN_00686f20(param_1,param_2);
    if (iVar1 < 0) {
      return 0x8007000e;
    }
  }
  return 0;
}

