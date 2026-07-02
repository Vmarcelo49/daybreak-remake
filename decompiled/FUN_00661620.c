// Function: FUN_00661620
// Address:  0x00661620
// Source:   batch_decompile (mass dump)
// Hash:     cec7f0de8b974476


undefined4 FUN_00661620(byte param_1)

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

