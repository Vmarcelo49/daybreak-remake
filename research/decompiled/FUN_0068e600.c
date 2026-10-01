// Function: FUN_0068e600
// Address:  0x0068e600
// Source:   batch_decompile (mass dump)
// Hash:     da90d7352bd802c9


void FUN_0068e600(int *param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  
  iVar1 = FUN_006871b0(param_2,&LAB_006ad101_3);
  if ((iVar1 == 0) && (iVar1 = FUN_006871b0(param_2,&DAT_006acfe4), iVar1 == 0)) {
    FUN_00687810(param_1,param_2,param_3);
    return;
  }
  (**(code **)(*param_1 + 0x24))(param_2,param_3);
  return;
}

