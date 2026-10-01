// Function: FUN_00695b80
// Address:  0x00695b80
// Source:   batch_decompile (mass dump)
// Hash:     c7bfd1db56fc14d7


undefined4 FUN_00695b80(int param_1,undefined4 *param_2)

{
  undefined4 uVar1;
  
  if (param_2 == (undefined4 *)0x0) {
    uVar1 = 0x80004003;
  }
  else {
    *param_2 = *(undefined4 *)(param_1 + 0x30);
    uVar1 = 0;
  }
  return uVar1;
}

