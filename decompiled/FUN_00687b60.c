// Function: FUN_00687b60
// Address:  0x00687b60
// Source:   batch_decompile (mass dump)
// Hash:     2fe23ae5b87445fb


undefined4 FUN_00687b60(int param_1,undefined4 *param_2)

{
  undefined4 uVar1;
  
  if (param_2 == (undefined4 *)0x0) {
    uVar1 = 0x80004003;
  }
  else {
    *param_2 = *(undefined4 *)(param_1 + 0x1c);
    param_2[1] = *(undefined4 *)(param_1 + 0x20);
    param_2[2] = *(undefined4 *)(param_1 + 0x24);
    param_2[3] = *(undefined4 *)(param_1 + 0x28);
    uVar1 = 0;
  }
  return uVar1;
}

