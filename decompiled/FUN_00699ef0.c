// Function: FUN_00699ef0
// Address:  0x00699ef0
// Source:   batch_decompile (mass dump)
// Hash:     69659b630cde0de7


undefined4 __thiscall FUN_00699ef0(undefined4 param_1,undefined4 *param_2)

{
  undefined4 uVar1;
  
  if (param_2 == (undefined4 *)0x0) {
    uVar1 = 0x80004003;
  }
  else {
    uVar1 = FUN_00699000(param_1);
    *param_2 = uVar1;
    uVar1 = 0;
  }
  return uVar1;
}

