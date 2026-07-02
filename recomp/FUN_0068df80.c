// ============================================
// Address:  0x0068df80
// Original: FUN_0068df80
// Status:   unreviewed
// ============================================


undefined4 FUN_0068df80(undefined4 param_1,undefined4 param_2,undefined4 *param_3)

{
  undefined4 uVar1;
  int iVar2;
  
  if (param_3 == (undefined4 *)0x0) {
    uVar1 = 0x80004003;
  }
  else {
    iVar2 = FUN_006871b0(param_2,&DAT_006ad9a8);
    if (iVar2 == 0) {
      *param_3 = 0;
      uVar1 = 0x80004002;
    }
    else {
      FUN_0068e090(param_1,param_3);
      uVar1 = 0;
    }
  }
  return uVar1;
}

