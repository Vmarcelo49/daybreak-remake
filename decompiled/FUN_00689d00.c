// Function: FUN_00689d00
// Address:  0x00689d00
// Source:   batch_decompile (mass dump)
// Hash:     86e48842756e06fc


undefined4 FUN_00689d00(int param_1,undefined4 *param_2)

{
  undefined4 uVar1;
  
  if (param_2 == (undefined4 *)0x0) {
    uVar1 = 0x80004003;
  }
  else {
    *param_2 = *(undefined4 *)(param_1 + 0x10);
    uVar1 = 0;
  }
  return uVar1;
}

