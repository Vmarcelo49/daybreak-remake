// Function: FUN_00695bb0
// Address:  0x00695bb0
// Source:   batch_decompile (mass dump)
// Hash:     b33d735ea9b51f44


uint FUN_00695bb0(int param_1,uint *param_2)

{
  uint uVar1;
  
  if (param_2 == (uint *)0x0) {
    uVar1 = 0x80004003;
  }
  else {
    uVar1 = (uint)((~*(uint *)(param_1 + 0x30) & *param_2) != 0);
  }
  return uVar1;
}

