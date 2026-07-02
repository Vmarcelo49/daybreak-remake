// Function: FUN_0068c920
// Address:  0x0068c920
// Source:   batch_decompile (mass dump)
// Hash:     670366e14cefffbd


undefined4 FUN_0068c920(int param_1,undefined4 *param_2)

{
  undefined4 uVar1;
  int local_10;
  
  if (param_2 == (undefined4 *)0x0) {
    uVar1 = 0x80004003;
  }
  else {
    if (param_1 == 0xc) {
      local_10 = 0;
    }
    else {
      local_10 = param_1 + 4;
    }
    FUN_0068d950(local_10);
    param_2[1] = *(undefined4 *)(param_1 + 0x34);
    *param_2 = *(undefined4 *)(param_1 + 0x2c);
    param_2[2] = *(undefined4 *)(param_1 + 0x38);
    param_2[3] = *(undefined4 *)(param_1 + 0x3c);
    FUN_0068d9a0();
    uVar1 = 0;
  }
  return uVar1;
}

