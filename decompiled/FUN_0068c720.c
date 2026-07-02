// Function: FUN_0068c720
// Address:  0x0068c720
// Source:   batch_decompile (mass dump)
// Hash:     23f5e707d6e603de


void FUN_0068c720(int param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  int local_8;
  
  iVar1 = FUN_006871b0(param_2,&LAB_006ad024);
  if ((iVar1 == 0) &&
     ((iVar1 = FUN_006871b0(param_2,&LAB_006ad011_3), iVar1 == 0 || (*(int *)(param_1 + 0x5c) == 0))
     )) {
    FUN_0068df80(param_1,param_2,param_3);
    return;
  }
  if (param_1 == 0) {
    local_8 = 0;
  }
  else {
    local_8 = param_1 + 0xc;
  }
  FUN_0068e090(local_8,param_3);
  return;
}

