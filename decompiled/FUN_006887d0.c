// Function: FUN_006887d0
// Address:  0x006887d0
// Source:   batch_decompile (mass dump)
// Hash:     c0e2d9d74f5bbd20


undefined4 FUN_006887d0(undefined4 param_1,undefined4 param_2,undefined4 *param_3)

{
  undefined4 uVar1;
  int iVar2;
  
  if (param_3 == (undefined4 *)0x0) {
    uVar1 = 0x80004003;
  }
  else {
    iVar2 = FUN_006871b0(param_2,&LAB_006ad094);
    if ((iVar2 == 0) && (iVar2 = FUN_006871b0(param_2,&DAT_006ad9a8), iVar2 == 0)) {
      *param_3 = 0;
      return 0x80004002;
    }
    uVar1 = FUN_0068e090(param_1,param_3);
  }
  return uVar1;
}

