// Function: FUN_00696260
// Address:  0x00696260
// Source:   batch_decompile (mass dump)
// Hash:     a94494261452a509


undefined4 FUN_00696260(undefined4 param_1,undefined4 *param_2)

{
  undefined4 uVar1;
  
  if (param_2 == (undefined4 *)0x0) {
    uVar1 = 0x80004003;
  }
  else {
    *param_2 = 0xffffffff;
    uVar1 = 0;
  }
  return uVar1;
}

