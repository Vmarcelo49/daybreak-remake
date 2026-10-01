// Function: FUN_00679e00
// Address:  0x00679e00
// Source:   batch_decompile (mass dump)
// Hash:     1830ee76f98591bd


void FUN_00679e00(undefined4 param_1,undefined1 *param_2,int param_3)

{
  undefined1 uVar1;
  
  for (; param_3 != 0; param_3 = param_3 + -1) {
    uVar1 = FUN_0069d720(param_1,8);
    *param_2 = uVar1;
    param_2 = param_2 + 1;
  }
  return;
}

