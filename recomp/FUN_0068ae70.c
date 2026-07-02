// ============================================
// Address:  0x0068ae70
// Original: FUN_0068ae70
// Status:   unreviewed
// ============================================


undefined4 FUN_0068ae70(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = FUN_006871b0(param_2,&LAB_006ad044);
  if (((iVar1 == 0) && (iVar1 = FUN_006871b0(param_2,&LAB_006ad031_3), iVar1 == 0)) &&
     (iVar1 = FUN_006871b0(param_2,&DAT_006ad9a8), iVar1 == 0)) {
    return 0x80004002;
  }
  uVar2 = FUN_0068e090(param_1,param_3);
  return uVar2;
}

