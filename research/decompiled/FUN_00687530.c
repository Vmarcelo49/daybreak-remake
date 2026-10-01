// Function: FUN_00687530
// Address:  0x00687530
// Source:   batch_decompile (mass dump)
// Hash:     df5f057dfb37835c


undefined4 FUN_00687530(int param_1,undefined4 param_2,undefined4 *param_3)

{
  undefined4 uVar1;
  
  if (param_3 == (undefined4 *)0x0) {
    uVar1 = 0x80004003;
  }
  else {
    *param_3 = *(undefined4 *)(param_1 + 4);
    uVar1 = 0;
  }
  return uVar1;
}

