// Function: FUN_0065e400
// Address:  0x0065e400
// Source:   batch_decompile (mass dump)
// Hash:     dc0f8fa356db2ec7


undefined4 FUN_0065e400(byte param_1)

{
  undefined4 uVar1;
  
  if (param_1 < 0x81) {
    uVar1 = 0;
  }
  else if (param_1 < 0xa0) {
    uVar1 = 1;
  }
  else if (param_1 < 0xe0) {
    uVar1 = 0;
  }
  else if (param_1 < 0xff) {
    uVar1 = 1;
  }
  else {
    uVar1 = 0;
  }
  return uVar1;
}

