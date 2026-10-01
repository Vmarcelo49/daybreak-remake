// Function: FUN_00698490
// Address:  0x00698490
// Source:   batch_decompile (mass dump)
// Hash:     c562ead31ce2d280


undefined4 FUN_00698490(int param_1,undefined4 param_2,int param_3)

{
  undefined4 uVar1;
  int iVar2;
  
  if (param_3 == 0) {
    uVar1 = 0x80004003;
  }
  else {
    iVar2 = FUN_006871b0(param_2,&DAT_006acf84);
    if (iVar2 == 0) {
      uVar1 = FUN_00689280(param_1,param_2,param_3);
    }
    else {
      *(undefined4 *)(param_1 + 0xa0) = 1;
      uVar1 = FUN_0068e090(param_1 + -8,param_3);
    }
  }
  return uVar1;
}

