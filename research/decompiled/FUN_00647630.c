// Function: FUN_00647630
// Address:  0x00647630
// Source:   batch_decompile (mass dump)
// Hash:     11704be3b2f70fb2


undefined4 * __thiscall FUN_00647630(undefined4 *param_1,undefined4 *param_2)

{
  undefined4 uVar1;
  undefined4 uVar2;
  
  uVar1 = *param_1;
  uVar2 = param_1[1];
  FUN_004280c0();
  *param_2 = uVar1;
  param_2[1] = uVar2;
  return param_2;
}

