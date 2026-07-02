// Function: FUN_00694a90
// Address:  0x00694a90
// Source:   batch_decompile (mass dump)
// Hash:     92f224deef76fafd


undefined4 FUN_00694a90(int param_1,undefined4 param_2,undefined4 *param_3)

{
  undefined4 uVar1;
  int iVar2;
  
  if (param_3 == (undefined4 *)0x0) {
    uVar1 = 0x80004003;
  }
  else {
    *param_3 = 0;
    iVar2 = FUN_006871b0(param_2,&DAT_006acfe4);
    if (iVar2 == 0) {
      uVar1 = FUN_006948e0(param_1,param_2,param_3);
    }
    else {
      uVar1 = FUN_0068e090(param_1 + -8,param_3);
    }
  }
  return uVar1;
}

